/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#include <pebble.h>
#include "speedo.h"
#include "speedoui.h"
#include "connection.h"

static void init() {
    init_main_window();
    init_app_message();
}

static void deinit() {
    deinit_main_window();
}
    
int main() {
    init();
    app_event_loop();
    deinit();
}