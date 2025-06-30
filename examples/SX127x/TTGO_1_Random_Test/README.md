# T114_LoRandom_Test

This example code uses a T114 with TFT to test LoRandom integrated to RadioLib.

(a) It fills a buffer and displays it. Requires [hexdump](https://github.com/Kongduino/hexdump).

(b) Pulls randombytes and plots them on the TFT.

```
Random Buffer()
     +------------------------------------------------+ +----------------+
     |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f | |      ASCII     |
     +------------------------------------------------+ +----------------+
000. |59 cc 4f 3b e8 17 f3 63 aa d4 0a 66 ff 18 1a c7 | |Y.O;...c...f....|
001. |16 40 32 60 a0 33 c3 4c 10 cc f6 5e 27 b6 4d 1b | |.@2`.3.L...^'.M.|
002. |fd 5d 9b 64 c5 72 80 14 da a3 7d a2 a8 73 d2 0b | |.].d.r....}..s..|
003. |93                                              | |.               |
     +------------------------------------------------+ +----------------+


Shuffle
     +------------------------------------------------+ +----------------+
     |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f | |      ASCII     |
     +------------------------------------------------+ +----------------+
000. |0a 3b 66 4d 14 33 5d 0b cc 32 fd 93 aa c7 40 64 | |.;fM.3]..2....@d|
001. |5e 10 80 a2 cc f3 4c 1b a3 7d e8 d2 60 4f 9b 16 | |^.....L..}..`O..|
002. |59 c3 d4 b6 c5 1a ff da 18 72 63 f6 a0 73 a8 17 | |Y........rc..s..|
003. |27                                              | |'               |
     +------------------------------------------------+ +----------------+
radio1.randomByte: 0xe7 radio1.randomByte: 0x23 radio1.randomByte: 0xd6 radio1.randomByte: 0xa5
radio1.randomByte: 0x28 radio1.randomByte: 0xa1 radio1.randomByte: 0x37 radio1.randomByte: 0x37
radio1.randomByte: 0xd4 radio1.randomByte: 0xf0 radio1.randomByte: 0x99 radio1.randomByte: 0x85
radio1.randomByte: 0x7f radio1.randomByte: 0x82 radio1.randomByte: 0x4a radio1.randomByte: 0xb1
radio1.randomByte: 0x70 radio1.randomByte: 0x51 radio1.randomByte: 0xc8 radio1.randomByte: 0x61
radio1.randomByte: 0xbb radio1.randomByte: 0xd1 radio1.randomByte: 0xc8 radio1.randomByte: 0x3b
radio1.randomByte: 0x7a radio1.randomByte: 0x9f radio1.randomByte: 0xab radio1.randomByte: 0xa1
radio1.randomByte: 0x02 radio1.randomByte: 0xe4 radio1.randomByte: 0x2d radio1.randomByte: 0x80
radio1.randomByte: 0xe8 radio1.randomByte: 0x12 radio1.randomByte: 0x6a radio1.randomByte: 0x30
radio1.randomByte: 0xdd radio1.randomByte: 0x87 radio1.randomByte: 0x2f radio1.randomByte: 0x85
radio1.randomByte: 0xa7 radio1.randomByte: 0xdf radio1.randomByte: 0xa2 radio1.randomByte: 0xe5
radio1.randomByte: 0xe4 radio1.randomByte: 0x22 radio1.randomByte: 0x70 radio1.randomByte: 0x4a
radio1.randomByte: 0x81 radio1.randomByte: 0xf7 radio1.randomByte: 0x18 radio1.randomByte: 0xc3
radio1.randomByte: 0x6e radio1.randomByte: 0xe8 radio1.randomByte: 0x9b radio1.randomByte: 0x50
radio1.randomByte: 0x5a radio1.randomByte: 0x68 radio1.randomByte: 0x8b radio1.randomByte: 0x99
radio1.randomByte: 0x51 radio1.randomByte: 0x00 radio1.randomByte: 0xc6 radio1.randomByte: 0x37
radio1.randomByte: 0x58 radio1.randomByte: 0xab radio1.randomByte: 0x16 radio1.randomByte: 0x88
radio1.randomByte: 0xa4 radio1.randomByte: 0xfb radio1.randomByte: 0x6a radio1.randomByte: 0xcb
radio1.randomByte: 0xe6 radio1.randomByte: 0x13 radio1.randomByte: 0x24 radio1.randomByte: 0x9f
radio1.randomByte: 0x87 radio1.randomByte: 0x3a radio1.randomByte: 0x4c radio1.randomByte: 0x80
radio1.randomByte: 0x47 radio1.randomByte: 0xc3 radio1.randomByte: 0x9f radio1.randomByte: 0x17
radio1.randomByte: 0x73 radio1.randomByte: 0xf3 radio1.randomByte: 0xb6 radio1.randomByte: 0xae
radio1.randomByte: 0x67 radio1.randomByte: 0xbb radio1.randomByte: 0x4f radio1.randomByte: 0x38
radio1.randomByte: 0x1c radio1.randomByte: 0x4b radio1.randomByte: 0xec radio1.randomByte: 0xd9
radio1.randomByte: 0xc8 radio1.randomByte: 0x69 radio1.randomByte: 0x41 radio1.randomByte: 0x65
radio1.randomByte: 0xa5 radio1.randomByte: 0x5c radio1.randomByte: 0xda radio1.randomByte: 0xc8
radio1.randomByte: 0xce radio1.randomByte: 0xa8 radio1.randomByte: 0x8e radio1.randomByte: 0x45
radio1.randomByte: 0x76 radio1.randomByte: 0xd7 radio1.randomByte: 0x35 radio1.randomByte: 0x77
radio1.randomByte: 0x82 radio1.randomByte: 0x77 radio1.randomByte: 0x8e radio1.randomByte: 0x47
radio1.randomByte: 0xae radio1.randomByte: 0x19 radio1.randomByte: 0x53 radio1.randomByte: 0xfb
radio1.randomByte: 0x6d radio1.randomByte: 0x1d radio1.randomByte: 0xcd radio1.randomByte: 0xa0
radio1.randomByte: 0x86 radio1.randomByte: 0x74 radio1.randomByte: 0x7d radio1.randomByte: 0x89


Even: 59, odd: 69

0-127: 59, 128-255: 69
```

## LoRandom API

* `void fillRandom();` Fills the internal `randomStock` buffer with 256, from which `randomByte()` gets its data. The buffer is replenished automatically when all used up.
* `void fillRandom(uint8_t*, uint16_t);` Fills a buffer with `ln` random bytes.
* `void shuffle(uint8_t *, uint16_t);` Shuffles a specified buffer 256 times.
