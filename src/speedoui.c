/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#include <pebble.h>
#include <math.h>
#include "speedoui.h"

static GFont s_bold_font;
static GFont s_normal_font;
static GFont s_small_font;
static GFont s_tiny_font;
static GBitmap *s_background_bitmap;

static Window *s_main_window;
static BitmapLayer *s_background_layer;

static TextLayer *s_speed_layer;
static TextLayer *s_heading_layer;
static TextLayer *s_altitude_layer;
static TextLayer *s_latitude_layer;
static TextLayer *s_longitude_layer;

static TextLayer *s_label_speed_layer;
static TextLayer *s_label_speed_unit_layer;
static TextLayer *s_label_heading_layer;
static TextLayer *s_label_altitude_layer;

static void main_window_load(Window*);
static void main_window_unload(Window*);

static void speedoui_init_label_text_layer();
static void speedoui_deinit_label_text_layer();

static TextLayer* speedoui_text_layer_create(struct GRect, GFont, int, int, int);

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
    // Load Font / Bitmap
    s_bold_font = fonts_load_custom_font(resource_get_handle(SPEEDOUI_FONT_LARGE));
    s_normal_font = fonts_load_custom_font(resource_get_handle(SPEEDOUI_FONT_NORMAL));
    s_small_font = fonts_load_custom_font(resource_get_handle(SPEEDOUI_FONT_SMALL));
    s_tiny_font = fonts_load_custom_font(resource_get_handle(SPEEDOUI_FONT_TINY));
    s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);

    // Create background BitmapLayer
    s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 152));
    bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));

    // Create label TextLayer
    speedoui_init_label_text_layer(window);
    
    // Create speed TextLayer
    s_speed_layer = speedoui_text_layer_create(
        GRect(6, 40, 96, 54),
        s_bold_font,
        GColorBlack,
        GColorClear,
        GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_speed_layer));
    
    // Create heading TextLayer
    s_heading_layer = speedoui_text_layer_create(
        GRect(4, 112, 62, 32),
        s_normal_font,
        GColorWhite,
        GColorClear,
        GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_heading_layer));
    
    // Create altitude TextLayer
    s_altitude_layer = speedoui_text_layer_create(
        GRect(78, 112, 62, 32),
        s_normal_font,
        GColorWhite,
        GColorClear,
        GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_altitude_layer));

    // Create latitude TextLayer
    s_latitude_layer = speedoui_text_layer_create(
        GRect(4, 2, 96, 14),
        s_small_font,
        GColorWhite,
        GColorClear,
        GTextAlignmentLeft);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_latitude_layer));

    // Create longitude TextLayer
    s_longitude_layer = speedoui_text_layer_create(
        GRect(4, 18, 96, 34),
        s_small_font,
        GColorWhite,
        GColorClear,
        GTextAlignmentLeft);
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_longitude_layer));

    // Init TextLayer with default values
    update_speed_layer(0);
    update_heading_layer(-1);
    update_altitude_layer(-1);
    update_latitude_layer(-1);
    update_longitude_layer(-1);
}

static void main_window_unload(Window *window) {    
    // Destroy TextLayer
    text_layer_destroy(s_speed_layer);
    text_layer_destroy(s_heading_layer);
    text_layer_destroy(s_altitude_layer);
    
    // Destroy label TextLayer
    speedoui_deinit_label_text_layer(window);
    
    // Destroy BitmapLayer
    bitmap_layer_destroy(s_background_layer);

    // Unload Font / Bitmap
    fonts_unload_custom_font(s_bold_font);
    fonts_unload_custom_font(s_normal_font);
    fonts_unload_custom_font(s_small_font);
    fonts_unload_custom_font(s_tiny_font);
    gbitmap_destroy(s_background_bitmap);
}

static void speedoui_init_label_text_layer(Window *window) {
    // Create speed label TextLayer
    s_label_speed_layer = speedoui_text_layer_create(
        GRect(6, 42, 36, 12),
        s_tiny_font,
        GColorBlack,
        GColorClear,
        GTextAlignmentLeft);
    text_layer_set_text(s_label_speed_layer, "Speed");
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_label_speed_layer));

    // Create speed unit label TextLayer
    s_label_speed_unit_layer = speedoui_text_layer_create(
        GRect(104, 82, 30, 12),
        s_tiny_font,
        GColorBlack,
        GColorClear,
        GTextAlignmentRight);
    text_layer_set_text(s_label_speed_unit_layer, "km/h");
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_label_speed_unit_layer));
    
    // Create heading label TextLayer
    s_label_heading_layer = speedoui_text_layer_create(
        GRect(4, 104, 36, 12),
        s_tiny_font,
        GColorWhite,
        GColorClear,
        GTextAlignmentLeft);
    text_layer_set_text(s_label_heading_layer, "Head.");
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_label_heading_layer));

    // Create altitude label TextLayer
    s_label_altitude_layer = speedoui_text_layer_create(
        GRect(76, 104, 36, 12),
        s_tiny_font,
        GColorWhite,
        GColorClear,
        GTextAlignmentLeft);
    text_layer_set_text(s_label_altitude_layer, "Alt.");
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_label_altitude_layer));
}

static void speedoui_deinit_label_text_layer(Window *window) {
    // Free TextLayer
    text_layer_destroy(s_label_speed_layer);
    text_layer_destroy(s_label_speed_unit_layer);
    text_layer_destroy(s_label_heading_layer);
    text_layer_destroy(s_label_altitude_layer);
}

static TextLayer* speedoui_text_layer_create(struct GRect rect, GFont font, int fgcolor, int bgcolor, int align) {
    TextLayer *layer = text_layer_create(rect);
    text_layer_set_background_color(layer, bgcolor);
    text_layer_set_text_color(layer, fgcolor);
    text_layer_set_font(layer, font);
    text_layer_set_text_alignment(layer, align);
    return layer;
}

void update_speed_layer(int val) {
    static char buf[4];
    snprintf(buf, 4, "%d", val);
    text_layer_set_text(s_speed_layer, buf);
}

void update_heading_layer(int val) {
    static char buf[4];
    snprintf(buf, 4, "%d", val);
    text_layer_set_text(s_heading_layer, buf);
}

void update_altitude_layer(int val) {
    static char buf[4];
    snprintf(buf, 4, "%d", val);
    text_layer_set_text(s_altitude_layer, buf);
}

void update_latitude_layer(int val) {
    static char buf[14];
    if (val != -1) {
        snprintf(buf, 14, "Lat. N %2d.%02d", val / 100, abs(val) % 100);
    } else {
        snprintf(buf, 14, "Lat. -1");
    }
    text_layer_set_text(s_latitude_layer, buf);
}

void update_longitude_layer(int val) {
    static char buf[14];
    if (val != -1) {
        snprintf(buf, 14, "Lon. E %2d.%02d", val / 100, abs(val) % 100);
    } else {
        snprintf(buf, 14, "Lon. -1");
    }
    text_layer_set_text(s_longitude_layer, buf);
}
