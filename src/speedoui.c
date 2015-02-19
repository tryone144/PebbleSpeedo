/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#include <pebble.h>
#include <math.h>
#include "speedoui.h"

static Window *s_main_window;

static TextLayer *s_speed_layer;

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
    // Create speed TextLayer
    s_speed_layer = text_layer_create(GRect(2, 2, 42, 42));
    text_layer_set_background_color(s_speed_layer, GColorClear);
    text_layer_set_text_color(s_speed_layer, GColorBlack);
    text_layer_set_font(s_speed_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
    text_layer_set_text_alignment(s_speed_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_speed_layer));
    
    // Init TextLayer with default values
    update_speed_layer(0);
}

static void main_window_unload(Window *window) {
    text_layer_destroy(s_speed_layer);
}

void update_speed_layer(int speed) {
    static char buf[5];
    if (speed != -1) {
        snprintf(buf, 5, "%d", speed);
        text_layer_set_text(s_speed_layer, buf);
    }
}

void update_heading_layer(int heading) {
    
}
