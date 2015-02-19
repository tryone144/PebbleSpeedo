/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#include <pebble.h>
#include "speedoui.h"

static Window *s_main_window;

static void main_window_load(Window*);
static void main_window_unload(Window*);

void init_main_window() {
    s_main_window = window_create();

    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
    });
    
    window_stack_push(s_main_window, true);
}

void deinit_main_window() {
    window_destroy(s_main_window);
}

static void main_window_load(Window *window) {
    
}

static void main_window_unload(Window *window) {
    
}
