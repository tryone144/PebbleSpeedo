/*
 * SPEEDOMETER for pebble
 * (c) 2015 Bernd Busse
 */

// Geolocation Listener ID
var watchID;

// Geolocation Options for realtime applications
var locationOptions = {
  enableHighAccuracy: true, 
  maximumAge: 1000, 
  timeout: 5000
};

// Success Callback
function locationSuccess(pos) {
    console.log('[SPEEDO.js] Location update!');
    
    var loc = pos.coords;
    console.log(JSON.stringify(loc));

    // Assemble dictionary using our keys
    var locationData = {
        "KEY_LOC_LATITUDE": loc.latitude ? (loc.latitude*100)|0 : -1,
        "KEY_LOC_LONGITUDE": loc.longitude ? (loc.longitude*100)|0 : -1,
        "KEY_LOC_ALTITUDE": loc.altitude ? loc.altitude|0 : -1,
        "KEY_LOC_ACCURACY": loc.accuracy ? loc.accuracy|0 : -1,
        "KEY_LOC_HEADING": loc.heading ? loc.heading|0 : -1,
        "KEY_LOC_SPEED": loc.speed ? loc.speed|0 : -1
    };

    // Send to Pebble
    Pebble.sendAppMessage(locationData, function(e) {
        console.log("[SPEEDO.js] Location data sent to Pebble successfully!");
    }, function(e) {
        console.log("[SPEEDO.js] Error sending location data to Pebble!");
    } );
}

// Error Callback
function locationError(err) {
    console.log('[SPEEDO.js] location error (' + err.code + '): ' + err.message);
}

Pebble.addEventListener('ready', function(e) {
    console.log("[SPEEDO.js] PebbleKit JS ready!");
    // Get location updates
    watchID = navigator.geolocation.watchPosition(locationSuccess, locationError, locationOptions);
} );

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage', function(e) {
    var dict = e.payload;
/*
    if (dict.KEY_GET_LOCATION) {
        console.log("[SPEEDO.js] Request location data!");
        getLocation();
    }
*/
});
