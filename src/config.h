/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */
#ifndef CONFIG_H
#define CONFIG_H
    
#define RELEASE false
    
#if RELEASE
    #define DEBUG false
#else
    #define DEBUG true
#endif // RELEASE
    
#endif // CONFIG_H
