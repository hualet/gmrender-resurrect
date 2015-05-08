#include <glib.h>

#include "logging.h"
#include "upnp_connmgr.h"
#include "output_module.h"
#include "output_dmovie.h"

static void output_dmovie_set_next_uri(const char *uri) {
	Log_info("output dmovie", "output_dmovie_set_next_uri '%s'", uri);
}

static void output_dmovie_set_uri(const char *uri,
				     output_update_meta_cb_t meta_cb) {
	Log_info("output dmovie", "output_dmovie_set_uri '%s'", uri);

	char* args[] = {"deepin-movie", uri, NULL};
	GError* err = NULL;

	int result = g_spawn_async (NULL,
               args,
               NULL,
               G_SPAWN_SEARCH_PATH,
               NULL,
               NULL,
               NULL,
               &err);

	if (err) {
		Log_info("output dmovie", err->message);
		g_clear_error(&err);
	}
}

static int output_dmovie_play(output_transition_cb_t callback) {
	Log_info("output dmovie", "output_dmovie_play");

	return 0;
}

static int output_dmovie_stop(void) {
	Log_info("output dmovie", "output_dmovie_stop");
	return 0;
}

static int output_dmovie_pause(void) {
	Log_info("output dmovie", "output_dmovie_pause");
	return 0;
}

static int output_dmovie_seek(gint64 position_nanos) {
	Log_info("output dmovie", "output_dmovie_seek '%d'", position_nanos);
	return 0;
}

static int output_dmovie_add_options(GOptionContext *ctx) {
	Log_info("output dmovie", "output_dmovie_add_options");
	return 0;
}

static int output_dmovie_get_position(gint64 *track_duration,
	gint64 *track_pos) {
	Log_info("output dmovie", "output_dmovie_get_position");

	*track_duration = 0;
	*track_pos = 0;

	return 0;
}

static int output_dmovie_get_volume(float *v) {
	Log_info("output dmovie", "output_dmovie_get_volume");

	*v = 1.0;

	return 0;
}

static int output_dmovie_set_volume(float value) {
	Log_info("output dmovie", "output_dmovie_set_uri '%f'", value);

	return -1;
}

static int output_dmovie_get_mute(int *m) {
	Log_info("output dmovie", "output_dmovie_get_mute");

	*m = 0;

	return 0;
}

static int output_dmovie_set_mute(int m) {
	Log_info("output dmovie", "output_dmovie_set_mute '%d'", m);

	return 0;
}

static int output_dmovie_init(void) {
	Log_info("output dmovie", "output_dmovie_init");

	// this is necessary because some control points will check mimetypes
	// first before playing, and deepin-movie is supposed to support every
	// mimetype actually.
	register_mime_type("*/*");

	return 0;
}

struct output_module dmovie_output = {
    .shortname = "DMovie",
	.description = "Video player by Deepin team.",
	.init        = output_dmovie_init,
	.add_options = output_dmovie_add_options,
	.set_uri     = output_dmovie_set_uri,
	.set_next_uri= output_dmovie_set_next_uri,
	.play        = output_dmovie_play,
	.stop        = output_dmovie_stop,
	.pause       = output_dmovie_pause,
	.seek        = output_dmovie_seek,
	.get_position = output_dmovie_get_position,
	.get_volume  = output_dmovie_get_volume,
	.set_volume  = output_dmovie_set_volume,
	.get_mute  = output_dmovie_get_mute,
	.set_mute  = output_dmovie_set_mute,
};
