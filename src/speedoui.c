/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#include <pebble.h>
#include <math.h>
#include "speedoui.h"

static Window *s_main_window;

static TextLayer *s_speed_layer;
static TextLayer *s_heading_layer;
static TextLayer *s_altitude_layer;

static GFont s_bold_font;
static GFont s_normal_font;
static GFont s_small_font;

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
    // Load Font
    s_bold_font = fonts_load_custom_font(resource_get_handle(SPEEDOUI_FONT_LARGE));
    s_normal_font = fonts_load_custom_font(resource_get_handle(SPEEDOUI_FONT_NORMAL));
    s_small_font = fonts_load_custom_font(resource_get_handle(SPEEDOUI_FONT_SMALL));

    // Create speed TextLayer
    s_speed_layer = speedoui_text_layer_create(
        GRect(4, 42, 136, 54),
        s_bold_font,
        GColorBlack,
        GColorClear,
        GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_speed_layer));
    
    // Create heading TextLayer
    s_heading_layer = speedoui_text_layer_create(
        GRect(4, 112, 62, 32),
        s_normal_font,
        GColorBlack,
        GColorClear,
        GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_heading_layer));
    
    // Create heading TextLayer
    s_altitude_layer = speedoui_text_layer_create(
        GRect(78, 112, 62, 32),
        s_normal_font,
        GColorBlack,
        GColorClear,
        GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_altitude_layer));

    // Init TextLayer with default values
    update_speed_layer(0);
    update_heading_layer(0);
    update_altitude_layer(0);
}

static void main_window_unload(Window *window) {    
    // Free TextLayer
    text_layer_destroy(s_speed_layer);
    text_layer_destroy(s_heading_layer);
    text_layer_destroy(s_altitude_layer);
    
    // Unload Font
    fonts_unload_custom_font(s_bold_font);
    fonts_unload_custom_font(s_normal_font);
    fonts_unload_custom_font(s_small_font);
}

void update_speed_layer(int val) {
    static char buf[5];
    if (val == -1) {
        val = 0;
    }
    snprintf(buf, 5, "%d", val);
    text_layer_set_text(s_speed_layer, buf);
}

void update_heading_layer(int val) {
    static char buf[5];
    if (val == -1) {
        val = 0;
    }
    snprintf(buf, 5, "%d", val);
    text_layer_set_text(s_heading_layer, buf);
}

void update_altitude_layer(int val) {
    static char buf[5];
    if (val == -1) {
        val = 0;
    }
    snprintf(buf, 5, "%d", val);
    text_layer_set_text(s_altitude_layer, buf);
}

TextLayer* speedoui_text_layer_create(struct GRect rect, GFont font, int fgcolor, int bgcolor, int align) {
    TextLayer *layer = text_layer_create(rect);
    text_layer_set_background_color(layer, bgcolor);
    text_layer_set_text_color(layer, fgcolor);
    text_layer_set_font(layer, font);
    text_layer_set_text_alignment(layer, align);
    return layer;
}
