#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=139,107
AudioFilterBiquad        biquad1;        //xy=322,98
AudioFilterBiquad        biquad2;        //xy=336,146
AudioOutputI2S           i2s1;           //xy=503,95
AudioConnection          patchCord1(i2s2, 0, biquad1, 0);
AudioConnection          patchCord2(i2s2, 1, biquad2, 0);
AudioConnection          patchCord3(biquad1, 0, i2s1, 0);
AudioConnection          patchCord4(biquad2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=185,211
// GUItool: end automatically generated code


//const int myInput = AUDIO_INPUT_LINEIN;
const int myInput = AUDIO_INPUT_MIC;

void setup() {
  Serial.begin(9600);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.micGain(36);
  
  
/*  biquad1.setBandpass(0,1000,500);
  biquad2.setBandpass(0,1000,500);
  biquad1.setBandpass(1,1000,500);
  biquad2.setBandpass(1,1000,500);
  biquad1.setBandpass(2,1000,500);
  biquad2.setBandpass(2,1000,500);
  biquad1.setBandpass(3,1000,500);
  biquad2.setBandpass(3,1000,500);*/
  biquad1.setHighpass(0,1000,0.3);
  biquad2.setHighpass(0,1000,0.3);
  biquad1.setLowpass(1,5000,0.1);
  biquad2.setLowpass(1,5000,0.1);
  
}

elapsedMillis volmsec=0;

void loop() {

  
  // every 50 ms, adjust the volume, frequency and filter with
  if (volmsec > 50) {
    float vol = analogRead(1);
    float frq = analogRead(2);
    float with = analogRead(3);
    
    
    vol = vol / 1023.0;
    frq = frq * 20.0;
    with = with / 1023.0;
    
    Serial.print("Vol ");
    Serial.print(vol);
    Serial.print(" Frq ");
    Serial.print(frq);
    Serial.print(" with ");
    Serial.println(with);
    
    sgtl5000_1.volume(vol);
    /*biquad1.setBandpass(0,frq,with);
    biquad2.setBandpass(0,frq,with);
    biquad1.setBandpass(1,frq,with);
    biquad2.setBandpass(1,frq,with);
    biquad1.setBandpass(2,frq,with);
    biquad2.setBandpass(2,frq,with);
    biquad1.setBandpass(3,frq,with);
    biquad2.setBandpass(3,frq,with);
    biquad1.setHighpass(0,400,with);
    biquad2.setHighpass(0,400,with);*/
    // biquad2.setHighpass(0,frq,with);
     biquad2.setBandpass(0,frq,with);
    //biquad2.setLowpass(2,200,0.54);
  }
}




