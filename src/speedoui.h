/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#ifndef SPEEDOUI_H
#define SPEEDOUI_H

#define SPEEDOUI_FONT_LARGE     RESOURCE_ID_FONT_UBUNTU_MONO_BOLD_52
#define SPEEDOUI_FONT_NORMAL    RESOURCE_ID_FONT_UBUNTU_MONO_REGULAR_32
#define SPEEDOUI_FONT_SMALL     RESOURCE_ID_FONT_UBUNTU_MONO_REGULAR_14
#define SPEEDOUI_FONT_TINY      RESOURCE_ID_FONT_UBUNTU_MONO_REGULAR_11

extern void init_main_window();
extern void deinit_main_window();

extern void update_speed_layer(int);
extern void update_heading_layer(int);
extern void update_altitude_layer(int);
extern void update_latitude_layer(int);
extern void update_longitude_layer(int);

#endif // SPEEDOUI_H
