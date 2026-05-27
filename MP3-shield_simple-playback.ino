/*
Play one track in loop
*/

#include <SPI.h>           // SPI library
#include <SdFat.h>         // SDFat Library
#include <FreeStack.h>
#include <SFEMP3Shield.h>  // Mp3 Shield Library

SdFat sd; // Create object to handle SD functions
SFEMP3Shield MP3player; // Create Mp3 library object
const uint8_t volume = 0; // MP3 Player volume 0=max, 255=lowest (off)
const uint16_t monoMode = 1;  // Mono setting 0=off, 3=max

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  initSD();  // Initialize the SD card
  initMP3Player(); // Initialize the MP3 Shield
}

void loop() {
  //loop single track
  if (!MP3player.isPlaying()){
    Serial.println("play track #0");
    uint8_t result = MP3player.playTrack(1);

    //check for errors
    if (result != 0) {
      Serial.print("Error playing track, code: ");
      Serial.println(result);
    }
    delay(500);
  }else{
    //do nothing
  }
}

void initSD(){
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) 
    sd.initErrorHalt();
  if(!sd.chdir("/")) 
    sd.errorHalt("sd.chdir");
}

void initMP3Player(){
  uint8_t result = MP3player.begin(); // init the mp3 player shield
  if(result != 0) { // check result, see readme for error codes.
    Serial.println("Error to init MP3player");
  }
  MP3player.setVolume(volume, volume);
  MP3player.setMonoMode(monoMode);
}
