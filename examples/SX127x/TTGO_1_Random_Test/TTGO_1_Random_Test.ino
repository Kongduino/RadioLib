/*
  RadioLib SX127x Settings Example
  https://randomnerdtutorials.com/ttgo-lora32-sx1276-arduino-ide/
  This example shows how to change all the properties of LoRa transmission.
  RadioLib currently supports the following settings:
  - pins (SPI slave select, digital IO 0, digital IO 1)
  - carrier frequency
  - bandwidth
  - spreading factor
  - coding rate
  - sync word
  - output power during transmission

  Other modules from SX127x/RFM9x family can also be used.

  For default module settings, see the wiki page
  https://github.com/jgromes/RadioLib/wiki/Default-configuration#sx127xrfm9x---lora-modem

  For full API reference, see the GitHub Pages
  https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>
#include <hexdump.h>

// SX1278 has the following connections:
#define SS 18
#define RST 14
#define DI0 26

SX1276 radio1 = new Module(SS, DI0, RST, 0);

// SX1272 has different connections:
// NSS pin:   9
// DIO0 pin:  4
// RESET pin: 5
// DIO1 pin:  6
// SX1272 radio2 = new Module(9, 4, 5, 6);

// or detect the pinout automatically using RadioBoards
// https://github.com/radiolib-org/RadioBoards
/*
#define RADIO_BOARD_AUTO
#include <RadioBoards.h>
Radio radio3 = new RadioModule();
*/

void shuffle(uint8_t *buffer, uint16_t ln) {
  for (uint8_t ix = 0; ix < 255; ix++) {
    uint8_t a, b, tmp;
    a = radio1.randomByte() % ln;
    b = radio1.randomByte() % ln;
    while (b == a) b = radio1.randomByte() % ln;
    tmp = buffer[a];
    buffer[a] = buffer[b];
    buffer[b] = tmp;
  }
}


void setup() {
  Serial.begin(115200);
  delay(2000);
  // initialize SX1278 with default settings
  SPI.begin(5, 19, 27, 18);
  Serial.print(F("[SX1278] Initializing ... "));
  int state = radio1.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

  // initialize the second LoRa instance with
  // non-default settings
  // this LoRa link will have high data rate,
  // but lower range
  // NOTE: when using spreading factor 6, the total packet
  //       length has to be known in advance!
  //       you have to pass the number of expected bytes
  //       to the receive() method
  Serial.print(F("[SX1272] Initializing ... "));
  // carrier frequency:           433.5 MHz
  // bandwidth:                   125.0 kHz
  // spreading factor:            6
  // coding rate:                 5
  // sync word:                   0x34
  // output power:                20 dBm
  // preamble length:             8 symbols
  // amplifier gain:              1 (maximum gain)

  // you can also change the settings at runtime
  // and check if the configuration was changed successfully

  // set carrier frequency to 433.5 MHz
  if (radio1.setFrequency(433.5) == RADIOLIB_ERR_INVALID_FREQUENCY) {
    Serial.println(F("Selected frequency is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set bandwidth to 250 kHz
  if (radio1.setBandwidth(125.0) == RADIOLIB_ERR_INVALID_BANDWIDTH) {
    Serial.println(F("Selected bandwidth is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set spreading factor to 10
  if (radio1.setSpreadingFactor(12) == RADIOLIB_ERR_INVALID_SPREADING_FACTOR) {
    Serial.println(F("Selected spreading factor is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set coding rate to 6
  if (radio1.setCodingRate(6) == RADIOLIB_ERR_INVALID_CODING_RATE) {
    Serial.println(F("Selected coding rate is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set LoRa sync word to 0x14
  // NOTE: value 0x34 is reserved for LoRaWAN networks and should not be used
  if (radio1.setSyncWord(0x14) != RADIOLIB_ERR_NONE) {
    Serial.println(F("Unable to set sync word!"));
    while (true) { delay(10); }
  }

  // set output power to 10 dBm (accepted range is -3 - 17 dBm)
  // NOTE: 20 dBm value allows high power operation, but transmission
  //       duty cycle MUST NOT exceed 1%
  if (radio1.setOutputPower(10) == RADIOLIB_ERR_INVALID_OUTPUT_POWER) {
    Serial.println(F("Selected output power is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set over current protection limit to 80 mA (accepted range is 45 - 240 mA)
  // NOTE: set value to 0 to disable overcurrent protection
  if (radio1.setCurrentLimit(240) == RADIOLIB_ERR_INVALID_CURRENT_LIMIT) {
    Serial.println(F("Selected current limit is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set LoRa preamble length to 15 symbols (accepted range is 6 - 65535)
  if (radio1.setPreambleLength(8) == RADIOLIB_ERR_INVALID_PREAMBLE_LENGTH) {
    Serial.println(F("Selected preamble length is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set amplifier gain to 1 (accepted range is 1 - 6, where 1 is maximum gain)
  // NOTE: set value to 0 to enable automatic gain control
  //       leave at 0 unless you know what you're doing
  if (radio1.setGain(1) == RADIOLIB_ERR_INVALID_GAIN) {
    Serial.println(F("Selected gain is invalid for this module!"));
    while (true) { delay(10); }
  }

  Serial.println(F("All settings successfully changed!"));
}

void loop() {
  uint8_t buffer[49];
  Serial.print("\n\nRandom Buffer()\n");
  radio1.fillRandom(buffer, 49);
  hexDump(buffer, 49);
  shuffle(buffer, 49);
  Serial.print("\n\nShuffle\n");
  hexDump(buffer, 49);
  radio1.fillRandom();
  uint8_t odd = 0, even = 0, below128 = 0, over127 = 0;
  for (uint8_t i = 0; i < 128; i += 4) {
    uint8_t x = radio1.randomByte();
    if (x & 1 == 1) odd++;
    else even++;
    if (x < 128) below128++;
    else over127++;
    Serial.printf("radio1.randomByte: 0x%02x ", x);
    x = radio1.randomByte();
    if (x & 1 == 1) odd++;
    else even++;
    if (x < 128) below128++;
    else over127++;
    Serial.printf("radio1.randomByte: 0x%02x ", x);
    x = radio1.randomByte();
    if (x & 1 == 1) odd++;
    else even++;
    if (x < 128) below128++;
    else over127++;
    Serial.printf("radio1.randomByte: 0x%02x ", x);
    x = radio1.randomByte();
    if (x & 1 == 1) odd++;
    else even++;
    if (x < 128) below128++;
    else over127++;
    Serial.printf("radio1.randomByte: 0x%02x\n", x);
  }
  Serial.printf("\n\nEven: %d, odd: %d\n\n", even, odd);
  Serial.printf("0-127: %d, 128-255: %d\n\n", below128, over127);
  delay(20000);
}
