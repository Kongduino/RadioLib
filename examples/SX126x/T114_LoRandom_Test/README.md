# T114_LoRandom_Test

This example code uses a T114 with TFT to test LoRandom integrated to RadioLib.

(a) It fills a buffer and displays it. Requires [hexdump](https://github.com/Kongduino/hexdump).

(b) Pulls randombytes and plots them on the TFT.

```
   +------------------------------------------------+ +----------------+
   |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f | |      ASCII     |
   +------------------------------------------------+ +----------------+
 0.|54 e7 6c 89 9a b6 92 cb d2 24 a6 9d c2 94 0d 6a | |T.l......$.....j|
 1.|a9 54 ed 6c e9 14 69 0d 04 24 52 aa a5 25 5a ad | |.T.l..i..$R..%Z.|
 2.|25 2c da ef 4a 5a b6 ee 56 52 a7 6a 2c 18 82 27 | |%,..JZ..VR.j,..'|
 3.|37                                              | |7               |
   +------------------------------------------------+ +----------------+


randomByte()
randomByte: 0x53 randomByte: 0x2e randomByte: 0x76 randomByte: 0xf7
randomByte: 0x03 randomByte: 0x6a randomByte: 0x22 randomByte: 0xa5
randomByte: 0x4a randomByte: 0x9a randomByte: 0xc0 randomByte: 0x00
randomByte: 0x2f randomByte: 0xf5 randomByte: 0x52 randomByte: 0x3b
randomByte: 0xdd randomByte: 0xd6 randomByte: 0xb2 randomByte: 0xa5
randomByte: 0x6b randomByte: 0x6d randomByte: 0x03 randomByte: 0x61
randomByte: 0x54 randomByte: 0x57 randomByte: 0xb9 randomByte: 0x7f
randomByte: 0xd8 randomByte: 0x92 randomByte: 0xac randomByte: 0xdb
randomByte: 0xfb randomByte: 0xea randomByte: 0xdd randomByte: 0x58
randomByte: 0x14 randomByte: 0x99 randomByte: 0xab randomByte: 0x76
randomByte: 0x88 randomByte: 0x2d randomByte: 0xb6 randomByte: 0xb4
randomByte: 0xcd randomByte: 0x6d randomByte: 0xca randomByte: 0x4b
randomByte: 0x88 randomByte: 0xb6 randomByte: 0xe6 randomByte: 0x54
randomByte: 0x99 randomByte: 0x24 randomByte: 0xad randomByte: 0x4a
randomByte: 0x44 randomByte: 0x65 randomByte: 0xd5 randomByte: 0x34
randomByte: 0x8b randomByte: 0x22 randomByte: 0x5d randomByte: 0x75
randomByte: 0xbf randomByte: 0x99 randomByte: 0xf4 randomByte: 0xa3
randomByte: 0x55 randomByte: 0x37 randomByte: 0x45 randomByte: 0xd9
randomByte: 0xb0 randomByte: 0x00 randomByte: 0x6c randomByte: 0x5e
randomByte: 0x9e randomByte: 0x7f randomByte: 0xeb randomByte: 0x5a
randomByte: 0x54 randomByte: 0x91 randomByte: 0xab randomByte: 0x2a
randomByte: 0x54 randomByte: 0xaa randomByte: 0xcf randomByte: 0xfa
randomByte: 0x25 randomByte: 0xd6 randomByte: 0x94 randomByte: 0x91
randomByte: 0x0b randomByte: 0x00 randomByte: 0xd5 randomByte: 0xbb
randomByte: 0xbe randomByte: 0x4a randomByte: 0x42 randomByte: 0x92
randomByte: 0xb3 randomByte: 0x6b randomByte: 0xd6 randomByte: 0xd3
randomByte: 0x2a randomByte: 0x25 randomByte: 0x2b randomByte: 0xb5
randomByte: 0xb6 randomByte: 0x6e randomByte: 0xe9 randomByte: 0xdd
randomByte: 0xb5 randomByte: 0xa6 randomByte: 0x9a randomByte: 0xdb
randomByte: 0x2a randomByte: 0x6a randomByte: 0xd8 randomByte: 0x94
randomByte: 0xab randomByte: 0x52 randomByte: 0xa6 randomByte: 0xeb
randomByte: 0x99 randomByte: 0x94 randomByte: 0x69 randomByte: 0x64


Even: 65, odd: 63

0-127: 59, 128-255: 69
```

## LoRandom API

* `void fillRandom();` Fills the internal `randomStock` buffer with 256, from which `randomByte()` gets its data. The buffer is replenished automatically when all used up.
* `void fillRandom(uint8_t*, uint16_t);` Fills a buffer with `ln` random bytes.
* `void shuffle(uint8_t *, uint16_t);` Shuffles a specified buffer 256 times.
