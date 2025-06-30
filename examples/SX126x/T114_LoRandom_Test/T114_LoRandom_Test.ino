/*
  RadioLib SX126x LoRandom example.
  This example uses the SX1262's TRNG function
  to produce random bytes. Derived from
  https://github.com/Kongduino/Sx1262LoRandom
  This was tested on a Heltec T114 with TFT
*/

// include the library
#include <RadioLib.h>
#include <hexdump.h>
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>

Adafruit_ST7789 tft = Adafruit_ST7789(&SPI1, PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_RST);

#define SX126X_CS (0 + 24)
#define SX126X_DIO1 (0 + 20)
// Note DIO2 is attached internally to the module to an analog switch for TX/RX switching
// #define SX1262_DIO3 (0 + 21)
// This is used as an *output* from the sx1262 and connected internally to power the tcxo, do not drive from the
//    main
// CPU?
#define SX126X_RESET (0 + 25)
#define SX126X_BUSY (0 + 17)
// Not really an E22 but TTGO seems to be trying to clone that
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8

// SX1262 has the following connections:
// NSS pin:   10
// DIO1 pin:  2
// NRST pin:  3
// BUSY pin:  9
SX1262 radio = new Module(SX126X_CS, SX126X_DIO1, SX126X_RESET, SX126X_BUSY);

void shuffle(uint8_t *buffer, uint16_t ln) {
  for (uint8_t ix = 0; ix < 255; ix++) {
    uint8_t a, b, tmp;
    a = radio.randomByte() % ln;
    b = radio.randomByte() % ln;
    while (b == a) b = radio.randomByte() % ln;
    tmp = buffer[a];
    buffer[a] = buffer[b];
    buffer[b] = tmp;
  }
}

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < 5; i++) {
    Serial.printf("%d, ", (5 - i));
    delay(1000);
  }
  Serial.println("0!");
  // initialize SX1262 with default settings
  pinMode(PIN_TFT_VDD_CTL, OUTPUT);  //TFT VDD ENABLE
  digitalWrite(PIN_TFT_VDD_CTL, 0);
  pinMode(PIN_TFT_LEDA_CTL, OUTPUT);  //LEDA ENABLE
  digitalWrite(PIN_TFT_LEDA_CTL, 0);
  tft.init(135, 240);  // Init ST7789 240x135
  tft.setRotation(3);

  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  tft.setSPISpeed(40000000);
  Serial.print(F("[SX1262] Initializing ... "));
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }
}

void loop() {
  tft.fillScreen(ST77XX_GREEN);
  delay(200);
  tft.fillScreen(ST77XX_WHITE);
  uint8_t buffer[49];
  Serial.print("\n\nRandom Buffer()\n");
  radio.fillRandom(buffer, 49);
  hexDump(buffer, 49);
  shuffle(buffer, 49);
  Serial.print("\n\nShuffle\n");
  hexDump(buffer, 49);
  radio.fillRandom();
  uint8_t odd = 0, even = 0, below128 = 0, over127 = 0;
  for (uint8_t i = 0; i < 128; i += 4) {
    uint8_t x = radio.randomByte();
    if (x & 1 == 1) odd++;
    else even++;x
    if (x < 128) below128++;
    else over127++;
    tft.drawPixel(x, i, ST77XX_BLACK);
    Serial.printf("radio.randomByte: 0x%02x ", x);
    x = radio.randomByte();
    if (x & 1 == 1) odd++;
    else even++;
    if (x < 128) below128++;
    else over127++;
    tft.drawPixel(x, i + 1, ST77XX_RED);
    Serial.printf("radio.randomByte: 0x%02x ", x);
    x = radio.randomByte();
    if (x & 1 == 1) odd++;
    else even++;
    if (x < 128) below128++;
    else over127++;
    tft.drawPixel(x, i + 2, ST77XX_GREEN);
    Serial.printf("radio.randomByte: 0x%02x ", x);
    x = radio.randomByte();
    if (x & 1 == 1) odd++;
    else even++;
    if (x < 128) below128++;
    else over127++;
    tft.drawPixel(x, i + 3, ST77XX_BLUE);
    Serial.printf("radio.randomByte: 0x%02x\n", x);
  }
  Serial.printf("\n\nEven: %d, odd: %d\n\n", even, odd);
  Serial.printf("0-127: %d, 128-255: %d\n\n", below128, over127);
  delay(20000);
}
