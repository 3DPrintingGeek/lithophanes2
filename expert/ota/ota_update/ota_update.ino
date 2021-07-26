#include "configuration.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "time.h"
const char* host = HOST;
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
WebServer server(WEBSERVER_PORT);
/* Style */
String style =
  "<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
  "input{background:#f1f1f1;border:0;padding:0 15px}body{background:#3498db;font-family:sans-serif;font-size:14px;color:#777}"
  "#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
  "#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:10px}"
  "form{background:#fff;max-width:258px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
  ".btn{background:#3498db;color:#fff;cursor:pointer}</style>";
/* Login page */
String loginIndex =
  "<form name=loginForm>"
  "<h1>ESP32 Login</h1>"
  "<input name=userid placeholder='User ID'> "
  "<input name=pwd placeholder=Password type=Password> "
  "<input type=submit onclick=check(this.form) class=btn value=Login></form>"
  "<script>"
  "function check(form) {"
  "if(form.userid.value=='admin' && form.pwd.value=='admin')"
  "{window.open('/serverIndex')}"
  "else"
  "{alert('Error Password or Username')}"
  "}"
  "</script>" + style;
/* Server Index Page */
String serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
  "<label id='file-input' for='file'>   Choose file...</label>"
  "<input type='submit' class=btn value='Update'>"
  "<br><br>"
  "<div id='prg'></div>"
  "<br><div id='prgbar'><div id='bar'></div></div><br></form>"
  "<script>"
  "function sub(obj){"
  "var fileName = obj.value.split('\\\\');"
  "document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
  "};"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  "$.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "$('#bar').css('width',Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!') "
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>" + style;

// Own definitions
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const uint8_t PROGMEM gamma8[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

// LED matrix 16x7 pixel RGB values
int colors[][3] = {{ 255, 235, 193},
  { 64, 64, 255},
  { 150, 150, 255},
  { 64, 64, 255},
  { 128, 128, 255},
  { 64, 64, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255,  150, 150},
  { 255,  150, 150},
  { 255,  150, 150},
  { 255, 128, 128},
  { 255, 255, 255},

  { 255, 255, 255},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 235, 193},
  { 255, 235, 193},

  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},

  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 247, 144},
  { 255, 247, 144},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},

  { 0, 255, 0},
  { 255, 235, 193},
  { 255, 255, 255},
  { 255, 247, 144},
  { 255, 247, 144},
  { 255, 255, 255},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 255, 255},
  { 150, 150, 150},
  { 150, 150, 150},

  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 255, 255, 255},
  { 150, 150, 150},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 0, 255, 0},
  { 0, 255, 0},

  { 255,  150, 150},
  { 255, 182, 182},
  { 255, 182, 182},
  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 0, 0, 0}
};

int led_shown = 0;

// Settings for NTP time server
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
byte sec; byte minute; byte hour; byte day; byte month; int year;

// Timer interrupt
volatile int count;    // Trigger
int totalInterrupts;
hw_timer_t * timer = NULL;
int last_program = 0;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  sec = timeinfo.tm_sec;
  minute = timeinfo.tm_min;
  hour = timeinfo.tm_hour;
  Serial.println(hour);
  Serial.println(minute);
  Serial.println(sec);
}

// Code with critica section
/*
  void IRAM_ATTR onTime() {
   portENTER_CRITICAL_ISR(&timerMux);
   count++;
   portEXIT_CRITICAL_ISR(&timerMux);
  }
*/

// Code without critical section
void IRAM_ATTR onTime() {
  count++;
}


/* setup function */
void setup(void) {
  Serial.begin(115200);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  /*return index page which is stored in serverIndex */
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", loginIndex);
  });
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.begin();

  // Own setup code
  // Configure the Prescaler at 80 the quarter of the ESP32 is cadence at 80Mhz
  // 80000000 / 80 = 1000000 tics / seconde
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTime, true);
  // Sets an alarm to sound every 5 minutes
  timerAlarmWrite(timer, 300000000, true);        // 300000000
  timerAlarmEnable(timer);

  strip.begin();
  strip.setBrightness(40); // 1/3 brightness

}

// Own routines

void color_photo() {
  for (int j = 0; j < LED_COLS; j++) {
    for (int k = 0; k < LED_ROWS; k++) {
      strip.setPixelColor(j * LED_ROWS + k, pgm_read_byte(&gamma8[colors[j * LED_ROWS + k][0]]),
                          pgm_read_byte(&gamma8[colors[j * LED_ROWS + k][1]]),
                          pgm_read_byte(&gamma8[colors[j * LED_ROWS + k][2]]));
    }
  }
  strip.show();
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i * 1 + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void loop(void) {
  server.handleClient();
  int program = count % 2;
  switch (program)
  {
    case 0:
      color_photo();
      strip.show();
      led_shown = 1;
      break;
    case 1:
      rainbow(60);
      break;
    default:
      break;
  }
}
