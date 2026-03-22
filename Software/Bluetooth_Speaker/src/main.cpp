#include <Arduino.h>
#include <Audiotools.h>
#include <BluetoothA2DPSink.h>

// Button GPIO pins 
#define BUTTON_PLAY_PAUSE 5
#define BUTTON_PREVIOUS 18
#define BUTTON_NEXT 19
#define BUTTON_VOLUME_UP 21
#define BUTTON_VOLUME_DOWN 22

#define I2S_LRC 14
#define I2S_BCLK 27
#define I2S_DIN 26

// I2S and Bluetooth Link 
I2SStream i2s; 
BluetoothA2DPSink a2dp_sink(i2s);

// buttons states
bool lastPlayPauseState = HIGH;
bool lastPreviousState = HIGH;
bool lastNextState = HIGH;
bool lastVolumeUpState = HIGH;
bool lastVolumeDownState = HIGH;

// playback state 
bool isPlaying = false;



void setup() {
Serial.begin(115200);

// configure buttons 
pinMode(BUTTON_PLAY_PAUSE, INPUT);
pinMode(BUTTON_PREVIOUS, INPUT);
pinMode(BUTTON_NEXT, INPUT);
pinMode(BUTTON_VOLUME_UP, INPUT);
pinMode(BUTTON_VOLUME_DOWN, INPUT);

// configure i2s
auto cfg = i2s.defaultConfig();
cfg.pin_bck = I2S_BCLK; // BCLK pin
cfg.pin_ws = I2S_LRC; // LRC pin
cfg.pin_data = I2S_DIN; // din pin
i2s.begin(cfg);

// start bluteooth link
a2dp_sink.start("ESPEAKER");
a2dp_sink.set_volume(64);
}

void loop() {
  // read button states
  bool currentPlayPauseState = digitalRead(BUTTON_PLAY_PAUSE);
  bool currentPreviousState = digitalRead(BUTTON_PREVIOUS);
  bool currentNextState = digitalRead(BUTTON_NEXT);
  bool currentVolumeUpState = digitalRead(BUTTON_VOLUME_UP);
  bool currentVolumeDownState = digitalRead(BUTTON_VOLUME_DOWN);
  Serial.println(a2dp_sink.get_volume());

  // Handle Play-pause
  if (currentPlayPauseState == LOW && lastPlayPauseState == HIGH) {
    Serial.println("Play/Pause Button Pressed");
    if(isPlaying) {
      a2dp_sink.pause(); // call pause 
      isPlaying = false;
      Serial.println(" Paused");
    } else {
      a2dp_sink.play(); // call play
      isPlaying =  true;
      Serial.println(" Playing");
    }
  }

  lastPlayPauseState = currentPlayPauseState;

  // Handle previous track button
  if(currentPreviousState == LOW && lastPreviousState == HIGH) {
    Serial.println("Previous Track Button Pressed");
    a2dp_sink.previous(); // go to prior track 
  }
  lastPreviousState = currentPreviousState;
  
  // handle next track button 
  if(currentNextState == LOW && lastNextState == HIGH) {
    Serial.println("Next Track Button Pressed");
    a2dp_sink.next(); // go to next track 
  }
  lastNextState = currentNextState;

  // handle volume up button 
  if(currentVolumeUpState == LOW && lastVolumeUpState == HIGH) {
    Serial.println("Volume up button pressed");
    a2dp_sink.volume_up(); // increment volume by one 
  }
  lastVolumeUpState = currentVolumeUpState;

  // handle volume down button 
  if(currentVolumeDownState == LOW && lastVolumeDownState == HIGH){
    Serial.println("Volume down button pressed");
    a2dp_sink.volume_down(); // decrement volume by one 
  }
  lastVolumeDownState = currentVolumeDownState;

  // short delay to debounce buttonz
  delay(50);
}
