/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#include <pebble.h>
#include "connection.h"
#include "speedoui.h"

static void inbox_received_callback(DictionaryIterator*, void*);
static void inbox_dropped_callback(AppMessageResult, void*);
static void outbox_failed_callback(DictionaryIterator*, AppMessageResult, void*);
static void outbox_sent_callback(DictionaryIterator*, void*);

void init_app_message() {
    // Register callbacks
    app_message_register_inbox_received(inbox_received_callback);
    app_message_register_inbox_dropped(inbox_dropped_callback);
    app_message_register_outbox_failed(outbox_failed_callback);
    app_message_register_outbox_sent(outbox_sent_callback);
 
    // Open AppMessage
    app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
    // Read first item
    Tuple *t = dict_read_first(iterator);
    
    // For all items
    while (t != NULL) {
        // Which key was received?
        switch (t->key) {
            case KEY_LOC_LATITUDE:
                update_latitude_layer((int)t->value->int32);
                break;
            case KEY_LOC_LONGITUDE:
                update_longitude_layer((int)t->value->int32);
                break;
            case KEY_LOC_ALTITUDE:
                update_altitude_layer((int)t->value->int32);
                break;
            case KEY_LOC_ACCURACY:
                APP_LOG(APP_LOG_LEVEL_DEBUG, "[SPEEDO.c] ACCURACY -> %d", (int)t->value->int32);
                break;
            case KEY_LOC_HEADING:
                update_heading_layer((int)t->value->int32);
                break;
            case KEY_LOC_SPEED:
                update_speed_layer((int)t->value->int32);
                break;
            default:
                APP_LOG(APP_LOG_LEVEL_ERROR, "[SPEEDO.c] Key %d not recognized!", (int)t->key);
                break;
        }
        
        // Look for the next item
        t = dict_read_next(iterator);
    }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "[SPEEDO.c] Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "[SPEEDO.c] Outbox sent failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
    APP_LOG(APP_LOG_LEVEL_INFO, "[SPEEDO.c] Outbox sent success!");
}
