/*
 * lib: RTCLib_by_NeiroN, Adafruit_SSD1306, Adafruit_GFX
 * Refer:
 * 1.
 * http://www.taichi-maker.com/homepage/reference-index/display-reference-index/arduino-oled-application/
 * 2. https://blog.jmaker.com.tw/arduino-ssd1306-oled/
 * 3.
 * http://www.taichi-maker.com/homepage/reference-index/arduino-library-index/install-arduino-library/
 * 4. https://github.com/BackMountainDevil/Arduino-ST7789-Library
 */
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <RTClib.h>
#include <SPI.h>
#include <Wire.h>

// Init rtc object
//   DS1302 rtc(ce_pin, sck_pin, io_pin);
// ce_pin  (RST): default 4
// sck_pin (CLK): default 5
// io_pin  (DAT): default 6
DS1302 rtc;
unsigned int timeDelta = 0; // 时间误差修正参数，单位为秒，不关心这个设置为0即可

// buffer for DateTime.tostr
char buf[20];

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS                                                         \
  0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*
 * 1.3'' TFT Screen
 */
Arduino_ST7789 tft = Arduino_ST7789(8, 9, 11, 13); // DC RST MOSI SCLK

void setup() {
  Serial.begin(9600);
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

//  Serial.println("rest time");
//  DateTime time_fix = DateTime(__DATE__, __TIME__) + TimeDelta(timeDelta);
//  rtc.adjust(time_fix);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  testdrawstyles(); // 測試文字
  delay(2000);      // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();

  tft.init(240, 240);              // 初始化屏幕（宽度，高度）
  tft.fillScreen(BLACK);           // 填充黑色背景
  drawtext("Hi,My Love", MAGENTA); // 显示文字
  delay(1000);
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
    display.clearDisplay();          // 清除屏幕显示内容
    display.setCursor(0, 0);         // 设置显示坐标原点
    display.println(now.tostr(buf)); // 设置显示内容为时间
    display.display();               // 输出显示效果

    tft.fillScreen(BLACK);
    drawtext(now.tostr(buf), MAGENTA); // 显示时间到TFT屏幕上
  }
  delay(1000);
}

void testdrawstyles(void) {
  display.clearDisplay();
  display.setTextSize(2); // 設定文字大小
  display.setTextColor(1); // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0, 0);       // 設定起始座標
  display.println("Hi My Love"); // 要顯示的字串
  display.println(F("   --Mifen"));
  display.display(); // 要有這行才會把文字顯示出來
}

void drawtext(char *text, uint16_t color) {
  /*在屏幕上绘制文字
  text：文字内容
  color：文字颜色
  */
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.setTextSize(3);
  tft.print(text);
}
