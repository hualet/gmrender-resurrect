#include "logging.h"
#include "upnp_connmgr.h"
#include "output_module.h"
#include "output_dmovie.h"
#include "dbus_dmovie.h"

static GDBusConnection *connection;
static DBusDmovie *dbus_dmovie_proxy;

static void output_dmovie_set_next_uri(const char *uri) {
	Log_info("output dmovie", "output_dmovie_set_next_uri '%s'", uri);
}

static void output_dmovie_set_uri(const char *uri,
				     output_update_meta_cb_t meta_cb) {
	Log_info("output dmovie", "output_dmovie_set_uri '%s'", uri);
	dbus_dmovie__call_set_uri_sync(
		dbus_dmovie_proxy,
		uri,
		NULL,
		NULL);
}

static int output_dmovie_play(output_transition_cb_t callback) {
	Log_info("output dmovie", "output_dmovie_play");
	dbus_dmovie__call_play_sync (
	    dbus_dmovie_proxy,
	    NULL,
	    NULL);

	return 0;
}

static int output_dmovie_stop(void) {
	Log_info("output dmovie", "output_dmovie_stop");
	dbus_dmovie__call_stop_sync (
	    dbus_dmovie_proxy,
	    NULL,
	    NULL);

	return 0;
}

static int output_dmovie_pause(void) {
	Log_info("output dmovie", "output_dmovie_pause");
	dbus_dmovie__call_pause_sync (
	    dbus_dmovie_proxy,
	    NULL,
	    NULL);

	return 0;
}

static int output_dmovie_seek(gint64 position_nanos) {
	Log_info("output dmovie", "output_dmovie_seek '%d'", position_nanos);
	dbus_dmovie__call_seek_sync (
	    dbus_dmovie_proxy,
	    position_nanos,
	    NULL,
	    NULL);

	return 0;
}

static int output_dmovie_add_options(GOptionContext *ctx) {
	Log_info("output dmovie", "output_dmovie_add_options");
	return 0;
}

static int output_dmovie_get_position(gint64 *track_duration,
	gint64 *track_pos) {
	Log_info("output dmovie", "output_dmovie_get_position");

	*track_duration = dbus_dmovie__get_duration(dbus_dmovie_proxy);
	*track_pos = dbus_dmovie__get_position(dbus_dmovie_proxy);

	return 0;
}

static int output_dmovie_get_volume(float *v) {
	Log_info("output dmovie", "output_dmovie_get_volume");

	*v = dbus_dmovie__get_volume(dbus_dmovie_proxy);

	return 0;
}

static int output_dmovie_set_volume(float value) {
	Log_info("output dmovie", "output_dmovie_set_uri '%f'", value);

	dbus_dmovie__set_volume(dbus_dmovie_proxy, value);

	return 0;
}

static int output_dmovie_get_mute(int *m) {
	Log_info("output dmovie", "output_dmovie_get_mute");

	*m = dbus_dmovie__get_mute(dbus_dmovie_proxy);

	return 0;
}

static int output_dmovie_set_mute(int m) {
	Log_info("output dmovie", "output_dmovie_set_mute '%d'", m);

	dbus_dmovie__set_mute(dbus_dmovie_proxy, m);

	return 0;
}

static int output_dmovie_init(void) {
	Log_info("output dmovie", "output_dmovie_init");
	connection = g_bus_get_sync (
					G_BUS_TYPE_SESSION,
					NULL,
					NULL);
	dbus_dmovie_proxy = dbus_dmovie__proxy_new_sync (
							connection,
							G_DBUS_PROXY_FLAGS_NONE,
							"com.deepin.DeepinMovie",
							"/com/deepin/DeepinMovie",
							NULL,
							NULL);
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
