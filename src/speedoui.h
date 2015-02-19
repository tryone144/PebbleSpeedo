/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#ifndef SPEEDOUI_H
#define SPEEDOUI_H
    
extern void init_main_window();
extern void deinit_main_window();

extern void update_speed_layer(int);
extern void update_heading_layer(int);

#endif // SPEEDOUI_H
