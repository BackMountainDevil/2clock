/*
 * lib: RTCLib_by_NeiroN, Adafruit_SSD1306, Adafruit_GFX
 * Refer:
 * 1. http://www.taichi-maker.com/homepage/reference-index/display-reference-index/arduino-oled-application/
 * 2. https://blog.jmaker.com.tw/arduino-ssd1306-oled/
 */
#include <RTClib.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Init rtc object
//   DS1302 rtc(ce_pin, sck_pin, io_pin);
// ce_pin  (RST): default 4
// sck_pin (CLK): default 5
// io_pin  (DAT): default 6
DS1302 rtc;

// buffer for DateTime.tostr
char buf[20];

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  testdrawstyles();    // 測試文字
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  // get time and print
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  } else {
      DateTime now = rtc.now();
      Serial.println(now.tostr(buf));
  }
  delay(3000);
}

void testdrawstyles(void) {
  display.clearDisplay();
  display.setTextSize(2);             // 設定文字大小
  display.setTextColor(1);        // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0,0);             // 設定起始座標
  display.println("Hi My Love");        // 要顯示的字串
  display.println(F("   --Mifen"));
  display.display();                  // 要有這行才會把文字顯示出來
}
