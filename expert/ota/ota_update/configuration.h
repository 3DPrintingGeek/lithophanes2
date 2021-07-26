#define HOST "ESP32Foto"
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR-WIFI-PASSPHRASE"

#define WEBSERVER_PORT 80

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        12 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define LED_COLS 16
#define LED_ROWS 7
#define NUMPIXELS LED_COLS* LED_ROWS// Popular NeoPixel ring size

#define DELAYVAL 10 // Time (in milliseconds) to pause between pixels
