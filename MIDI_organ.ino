#include <Control_Surface.h>

// USB MIDI interface setup
USBMIDI_Interface midi;

// Signal pins from multiplexers
const pin_t muxAPin = A0;
const pin_t muxBPin = A1;
const pin_t muxCPin = A2;
const pin_t muxDPin = A3;

// Shared address pins for all multiplexers
AH::Array<pin_t, 4> muxAddressPins = {5, 4, 3, 2};

// Initialization of 4 multiplexers
CD74HC4067 muxA(muxAPin, muxAddressPins);
CD74HC4067 muxB(muxBPin, muxAddressPins);
CD74HC4067 muxC(muxCPin, muxAddressPins);
CD74HC4067 muxD(muxDPin, muxAddressPins);

// MIDI note values array (from C2 = 36 to A6 = 93, total 58 notes)
int keyBoard[58];

// Array storing the last read state of each button
bool lastState[58];

void setup() {
  // Initialize multiplexers
  muxA.begin();
  muxB.begin();
  muxC.begin();
  muxD.begin();

  // Initialize USB MIDI
  Control_Surface.begin();
  Serial.begin(9600);

  // Initialize lastState array
  for (int i = 0; i < 58; i++) {
    lastState[i] = HIGH;
  }

  // Fill the note array from 36 (C2) to 93 (A6)
  for (int i = 0; i < 58; i++) {
    keyBoard[i] = 36 + i;
  }

  // Set pin mode for each input in the multiplexers
  for (int i = 0; i < 16; i++) {
    ExtIO::pinMode(muxA.pin(i), INPUT_PULLUP);
    ExtIO::pinMode(muxB.pin(i), INPUT_PULLUP);
    ExtIO::pinMode(muxC.pin(i), INPUT_PULLUP);
    ExtIO::pinMode(muxD.pin(i), INPUT_PULLUP);
  }
}

void loop() {
  Control_Surface.loop();  // MIDI handling

  // Iterate 58 inputs 
  for (int i = 0; i < 58; i++) {
    bool currentState = HIGH;

    if (i < 16) {
      currentState = ExtIO::digitalRead(muxA.pin(i));
    } else if (i < 32) {
      currentState = ExtIO::digitalRead(muxB.pin(i - 16));
    } else if (i < 48) {
      currentState = ExtIO::digitalRead(muxC.pin(i - 32));
    } else {
      currentState = ExtIO::digitalRead(muxD.pin(i - 48));
    }

    handleMidi(keyBoard[i], currentState, lastState[i]);
  }

  delay(5); 
}

void handleMidi(int midiValue, bool currentState, bool &lastState) {
  if (currentState != lastState) {
    if (currentState == LOW) {
      midi.sendNoteOn({midiValue, CHANNEL_1}, 0x7F);
    } else {
      midi.sendNoteOff({midiValue, CHANNEL_1}, 0x7F);
    }
    lastState = currentState;
  }
}
