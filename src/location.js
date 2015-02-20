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
    
    var location = pos.coords;
    console.log(JSON.stringify(location));

    // Convert values
    var latitude = location.latitude ? Math.round(location.latitude * 100) | 0 : -1; // Latitude in Decimal Degrees (negative means south) -> Keep prec. 2
    var longitude = location.longitude ? Math.round(location.longitude * 100) | 0 : -1; // Longitude in Decimal Degrees (negative means east) -> Keep prec. 2
    var altitude = location.altitude ? Math.round(location.altitude) | 0 : -1; // Altitude in Meters above WGS84 Elipsoid
    var accuracy = location.accuracy ? Math.round(location.accuracy) | 0 : -1; // Coordinates Accuracy in Meters
    var heading = location.heading ? Math.round(location.heading) | 0: -1; // Heading in Degrees relative to True North
    var speed = location.speed ? Math.round(location.speed * 3.6) | 0: -1; // Speed in Kilometers per Second
    
    // Assemble dictionary using our keys
    var locDict = {
        "KEY_LOC_LATITUDE": latitude,
        "KEY_LOC_LONGITUDE": longitude,
        "KEY_LOC_ALTITUDE": altitude,
        "KEY_LOC_ACCURACY": accuracy,
        "KEY_LOC_HEADING": heading,
        "KEY_LOC_SPEED": speed
    };

    // Send to Pebble
    Pebble.sendAppMessage(locDict, function(e) {
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
