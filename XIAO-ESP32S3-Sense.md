# Play a sound-track using a XIAO-ESP32S3-Sense board

----
### WHY THE XIAO ESP32S3 SENSE?

The Seeed Studio XIAO ESP32S3 Sense is a thumbnail-sized (21 x 17.5mm) board built around the ESP32-S3 dual-core processor, with WiFi/Bluetooth, 8MB of PSRAM and a microSD card slot on its Expansion Board. The extra PSRAM is what makes it useful for sound: it gives enough RAM to load a whole WAV file into memory and stream it out sample-by-sample, something a plain Arduino can't do.

It ships with a camera and digital microphone attached, but for an audio-only project like this one the camera module simply unplugs from its FPC connector — you're left with a small, capable board and no wasted hardware.

----
### HARDWARE

- [Seeed Studio XIAO ESP32S3 Sense](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/)
- Seeed Studio XIAO Expansion Board (adds the microSD card slot)
- microSD card, formatted FAT32, with a mono 16-bit PCM WAV file named `track1.wav` recorded at 16kHz
- [SparkFun Noisy Cricket Stereo Amplifier - 1.5W](https://learn.sparkfun.com/tutorials/noisy-cricket-stereo-amplifier---15w-hookup-guide/all)
- A speaker 4Ω 3W 
- 1x resistor (1kΩ)
- 1x capacitor (10nF) for a simple RC low-pass filter
- USB-C cable

----
### SETTING UP THE ARDUINO IDE

1. Open **File → Preferences** and add this URL to *Additional boards manager URLs*:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2. Open **Tools → Board → Boards Manager**, search for **esp32** (by Espressif Systems) and install it.
3. Select **Tools → Board → esp32 → XIAO_ESP32S3**.
4. **Important:** go to **Tools → PSRAM** and set it to **OPI PSRAM**. Without this the sketch cannot allocate the audio buffer and will fail with "Not enough memory to load file!".
5. Plug the XIAO in via USB-C and select the matching **Port**.

----
### WIRING

The XIAO ESP32S3 Sense clips into the Expansion Board (line up the board-to-board connector and press until it clicks) — this gives you the microSD slot. Insert the microSD card with `track1.wav` on it into that slot.

The sketch drives a single PWM audio signal out of pin **D7**. This is a raw square wave, so it needs a low-pass filter before it reaches the amplifier, otherwise the switching noise gets amplified along with the audio:

0. On the back of the amplifier, solder-short the **ENABLE MONO OUTPUT** jumper pads (and, optionally, the **MONO BASS BOOST** jumper to keep more low end).
1. **D7 → resistor (~1kΩ) → amplifier input.** Wire the resistor in series between D7 and the Noisy Cricket's `Left-IN`, then bridge `Left-IN` to `Right-IN` so the same signal drives both input channels — in mono mode the board sums both channels at the output, so feeding only one side halves your output level.
2. **Capacitor (~10nF) from the amplifier-input side of the resistor to GND.** This forms the low-pass filter with the resistor above, smoothing the PWM into an analog-ish signal.
3. **XIAO GND → Noisy Cricket GND** (both the input GND and power GND).
4. **XIAO 5V → Noisy Cricket VCC.** The Noisy Cricket accepts 2.4-5.5V.
5. **Speaker → Noisy Cricket `Left OUT` and `MONO` pins** — one wire to each. In mono mode these two pins are the speaker output; **do not** connect either speaker terminal to GND, per the [hookup guide](https://learn.sparkfun.com/tutorials/noisy-cricket-stereo-amplifier---15w-hookup-guide/all).


----
# TUTORIALS

----
### Tutorial 1: BASIC PLAYBACK

The following code loads `track1.wav` from the microSD card into PSRAM on startup, then plays it back through pin D7 using a hardware timer running at 16000Hz (matching the recording's sample rate), looping once playback finishes. Add your `track1.wav` file to the microSD card, then upload [this code](https://github.com/kingston-hackSpace/Sound_boards/blob/main/XIAO_test/XIAO_test.ino) to the XIAO ESP32S3 Sense.

Open the Serial Monitor at 115200 baud to see load and playback status.
