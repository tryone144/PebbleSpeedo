/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#ifndef CONNECTION_H
#define CONNECTION_H

// Location KEYS
#define KEY_LOC_LATITUDE 0
#define KEY_LOC_LONGITUDE 1
#define KEY_LOC_ALTITUDE 2
#define KEY_LOC_ACCURACY 3
#define KEY_LOC_HEADING 4
#define KEY_LOC_SPEED 5

// Request KEYS
#define KEY_START_LOCATION 16
#define KEY_STOP_LOCATION 17

extern void init_app_message();

#endif // CONNECTION_H
