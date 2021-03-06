// This is the basic demo program for the new color block
// testing functions of all, including led, speaker, vibration motor, accelerometer

#include "neopixel_leds.h"
#include <XBee.h>
#include <SoftwareSerial.h>
#include "pitches.h"

// hardware connection define here
#define XBEE_RX 7
#define XBEE_TX 8
#define ACCEL_X A0
#define ACCEL_Y A1
#define ACCEL_Z A2
#define SPEAKER 3
#define VIBR_MOTOR 5

NeopixelLeds neopixelleds;
SoftwareSerial xbeeSerial(XBEE_RX, XBEE_TX);  // RX, TX
XBee xbee = XBee();

// notes in the melody:
int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4};

// for led pattern time control
unsigned long timer_last, timer_now;
const int PATTERN_PERIOD = 20000;

void setup() {
    // Serial.begin(9600);

    // 1.xbee
    // xbeeSerial.begin(9600);
    // xbee.setSerial(xbeeSerial);

    // 2.accelerometer

    // 3.speaker
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++) {
        // to calculate the note duration, take one second
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(SPEAKER, melody[thisNote], noteDuration);
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(SPEAKER);
    }

    // 4.vibration motor
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
        // sets the value (range from 0 to 255):
        analogWrite(VIBR_MOTOR, fadeValue);
        delay(30);
    }
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
        // sets the value (range from 0 to 255):
        analogWrite(VIBR_MOTOR, fadeValue);
        delay(30);
    }

}

void loop() {

    // // accelerometer test
    // // print the accelerometer readings:
    // Serial.print(analogRead(ACCEL_X));
    // // print a tab between values:
    // Serial.print("\t");
    // Serial.print(analogRead(ACCEL_Y));
    // // print a tab between values:
    // Serial.print("\t");
    // Serial.print(analogRead(ACCEL_Z));
    // Serial.println();
    // // delay before next reading:
    // delay(100);

    // // xbee test, send message
    // xbeeSerial.println("Hello, there.");



    // 5.neopixel leds
    // each pattern last for 20 sec

    // rainbow spiral pattern
    neopixelleds.rainbow_spiral_begin();
    timer_last = millis();
    while (millis() - timer_last < PATTERN_PERIOD) {
        neopixelleds.rainbow_spiral_update();
    }
    neopixelleds.clear_pixels();

    // rainbow circular pattern
    neopixelleds.rainbow_circular_begin();
    timer_last = millis();
    while (millis() - timer_last < PATTERN_PERIOD) {
        neopixelleds.rainbow_circular_update();
    }
    neopixelleds.clear_pixels();

    // color ramp pattern
    neopixelleds.color_ramp_begin();
    timer_last = millis();
    while (millis() - timer_last < PATTERN_PERIOD) {
        neopixelleds.color_ramp_update();
    }
    neopixelleds.clear_pixels();

    // color wave pattern
    neopixelleds.color_wave_begin();
    timer_last = millis();
    while (millis() - timer_last < PATTERN_PERIOD) {
        neopixelleds.color_wave_update();
    }
    neopixelleds.clear_pixels();

    // countdown pattern
    neopixelleds.countdown_begin();
    timer_last = millis();
    while (millis() - timer_last < PATTERN_PERIOD) {
        neopixelleds.countdown_update();
    }
    neopixelleds.clear_pixels();

}



