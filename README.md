# SAM - Software Automatic Mouth - Tiny Speech Synthesizer - Arduino Library

Sam is a very small Text-To-Speech (TTS) program written in C, that runs on most popular platforms.
It is an adaption to C of the speech software SAM (Software Automatic Mouth) for the Commodore C64 published 
in the year 1982 by Don't Ask Software (now SoftVoice, Inc.). It includes a Text-To-Phoneme converter called reciter and a Phoneme-To-Speech routine for the final output. It is so small that it will work also on embedded computers.  

I created this project with the intention to provide SAM as Arduino Library which supports different output alternatives:

- [Output with a callback method](examples/text_to_speach_callback/text_to_speach_callback.ino)
- [Output to a Arduino Stream](examples/text_to_speach_stream/text_to_speach_stream.ino)
- [Output to I2S (for the ESP32)](examples/text_to_speach_i2s/text_to_speach_i2s.ino)

## Installation

You can download the library as zip and call include Library -> zip library. Or you can git clone this project into the Arduino libraries folder e.g. with
```
cd  ~/Documents/Arduino/libraries
git clone pschatzmann/SAM.git
```

## Documentation

- [class documentation for the Arduino API ](https://pschatzmann.github.io/arduino-SAM/doc/html/class_s_a_m.html) 
- [supported Phonemes](PHONES.md) 
- [the original Readme](SAM.md) 
- [the manual of the equivalent Apple II program](http://www.apple-iigs.info/newdoc/sam.pdf)

## Voices

Voices can be defined by setting the speed, pitch, throat and moth parameters:

```
	DESCRIPTION          SPEED     PITCH     THROAT    MOUTH
	Elf                   72        64        110       160
	Little Robot          92        60        190       190
	Stuffy Guy            82        72        110       105
	Little Old Lady       82        32        145       145
	Extra-Terrestrial    100        64        150       200
	SAM                   72        64        128       128
```

You can try out some alternative parameter combinations [here](https://discordier.github.io/sam/).


## Memory Requirements


| Memory Type        |  Used        |
|--------------------|--------------|
| Progmem            | 225'000      |
| Dynamic Memory     |  14'000      |  

The requirements have been determined by compiling the project with an ESP32. The values are rounded up!  


## License

The software is a reverse-engineered version of a commercial software published more than 30 years ago. The current copyright holder is SoftVoice, Inc. (www.text2speech.com)

Any attempt to contact the company failed. The website was last updated in the year 2009. The status of the original software can therefore best described as Abandonware (http://en.wikipedia.org/wiki/Abandonware)

As long this is the case we cannot put the code under any specific open source software license: Use it at your own risk.

