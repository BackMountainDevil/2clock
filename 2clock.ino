/*
 * lib: RTCLib_by_NeiroN, Adafruit_SSD1306, Adafruit_GFX
 */
#include <RTClib.h>

// Init rtc object
//   DS1302 rtc(ce_pin, sck_pin, io_pin);
// ce_pin  (RST): default 4
// sck_pin (CLK): default 5
// io_pin  (DAT): default 6
DS1302 rtc;

// buffer for DateTime.tostr
char buf[20];

void setup() {
  Serial.begin(9600);
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

//    Serial.println("rest time");
//    rtc.adjust(DateTime(__DATE__, __TIME__)); 
}

void loop() {
  // get time and print
  DateTime now = rtc.now();
  Serial.println(now.tostr(buf));

  delay(3000);
}
