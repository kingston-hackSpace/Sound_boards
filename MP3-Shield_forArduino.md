# MP3 Player Shield by Sparkfun

The SparkFun MP3 Shield is an MP3 decoder with the capabilities of storing music files onto a microSD card, therefore giving you the ability to add music or sound effects to any project, very similar principle works with Touch-board. With this board you can pull MP3 files from a microSD card and play them using one shield, effectively turning any Arduino into a fully functional stand-alone MP3 player. The VS1053 receives its input bit stream through a serial input bus (SPI). After the IC has decoded the stream, the audio is sent out to both a 3.5mm stereo headphone jack, as well as a 2-pin 0.1” pitch header. The Sparkfun MP3 shield is also capable of decoding MP3/AAC/WMA/MIDI audio.

Load mp3 files onto the SD card. Use the convention of 8 characters for the name, no spaces or illegal characters. They will be played based on their order in the directory (i.e. first file= [0] second file=[1] etc)

playing an mp3 causes an interupt. During playing, the arduino is in a delayed state. We found that by connecting the arduino with the shield to a second arduino, then using this second arduino to send serial commands to play the mp3s allows you to run synchoronous code and logic on the first board.

Sparkfunn Hookup Guide [here](https://learn.sparkfun.com/tutorials/mp3-player-shield-hookup), PDF version [here](https://github.com/kingston-hackSpace/Sound_boards/blob/main/MP3%20Player%20Shield%20Hookup%20-%20SparkFun%20Learn.pdf)

----
### INSTALLING LIBRARIES

This board uses the The "SFEMP3Shield" and "SdFat" libraries. Download them [here](https://github.com/kingston-hackSpace/Sound_boards/raw/refs/heads/main/Sparkfun-MP3-Player-Shield-Arduino-Library-master.zip)

Move your files to corresponding Arduino libraries folder. For help installing the library, check out this [Installing an Arduino Library tutorial](https://learn.sparkfun.com/tutorials/installing-an-arduino-library).

----
### FILE TYPE

The VS1053B is capable of playing MP3, AAC, WMA, MIDI, and Ogg Vorbis audio files. Read [here](https://learn.sparkfun.com/tutorials/mp3-player-shield-hookup)

MP3 files **MUST BE NAMED** AS: "track001.mp3", "track002.mp3", etc.

----
# TUTORIALS

----
### Tutorial 1: BASIC PLAYBACK

The following code reproduces one track ("track001.mp3") in loop. Add your track to the micro-SD card. Then upload [this code](https://github.com/kingston-hackSpace/Sound_boards/blob/main/MP3-shield_simple-playback.ino) to the Arduino board.
