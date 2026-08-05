the playback is bad. /*
This programme runs audio (track01.WAV) on startup

REMINDER: enable PSRAM
Arduino IDE → Tools → PSRAM → OPI PSRAM.
*/

#include "FS.h"
#include "SD.h"

#define WAV_FILE_NAME "/track1.wav"
#define WAV_HEADER_SIZE 44
#define PWM_PIN D7          // D7 — change if you wired a different pin
#define PWM_FREQ 62500     // fast carrier wave, smoothed later by your RC filter
#define PWM_RESOLUTION 8   // 8-bit duty cycle: values 0–255

int16_t *audioBuffer = NULL;
volatile uint32_t sampleCount = 0;
volatile uint32_t currentSample = 0;

hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer() {
  if (currentSample < sampleCount) {
    int16_t sample = audioBuffer[currentSample];
    uint8_t duty = (sample + 32768) >> 8;  // convert signed 16-bit sample to 0–255
    ledcWrite(PWM_PIN, duty);
    currentSample++;
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  if (!SD.begin(21)) {
    Serial.println("Failed to mount SD Card!");
    while (1) ;
  }

  File file = SD.open(WAV_FILE_NAME, FILE_READ);
  if (!file) {
    Serial.println("Failed to open track1.wav!");
    while (1) ;
  }

  file.seek(WAV_HEADER_SIZE);  // skip past the 44-byte header
  uint32_t dataSize = file.size() - WAV_HEADER_SIZE;
  sampleCount = dataSize / 2;  // 16-bit samples = 2 bytes each

  audioBuffer = (int16_t *) ps_malloc(dataSize);
  Serial.printf("File size: %d bytes, dataSize: %d bytes, free PSRAM: %d bytes\n", file.size(), dataSize, ESP.getPsramSize());
  if (audioBuffer == NULL) {
    Serial.println("Not enough memory to load file!");
    while (1) ;
  }

  file.read((uint8_t *)audioBuffer, dataSize);
  file.close();

  Serial.printf("Loaded %d samples. Starting playback...\n", sampleCount);

  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);

  timer = timerBegin(16000);           // timer ticks at 16000 Hz — matches your recording sample rate
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 1, true, 0);       // fire onTimer() once every tick
}

void loop() {
  static bool announced = false;

  if (currentSample >= sampleCount) {
    if (!announced) {
      Serial.println("Playback finished. Looping...");
      announced = true;
    }
    delay(500);          // brief pause between loops
    currentSample = 0;   // jump back to the start of the buffer
    announced = false;
  }
}