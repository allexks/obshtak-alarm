/*
 * Unlocked the door is
 * As I lost my keys
 * In my bed I cannot sleep
 * I am scared like a sheep
 * Dear Arduino, help me
 * PIR sensor, I trust thee
 * With my piezzo forces unite
 * In case trespassers interrupt my night.
*/

// Pins
#define PIR_SENSOR 2
#define PIEZZO 4
#define LED LED_BUILTIN

// Alarm playback
typedef struct {
    unsigned long duration;
    unsigned int frequency;
} Note;

const unsigned int TEMPO = 120; // bpm
#define FREQ_PAUSE 0
#define FREQ_G4  392  // Hz
#define FREQ_Eb4 311
#define FREQ_Bb4 466
#define FREQ_Gb4 369
#define FREQ_Eb5 622
#define FREQ_D5 587

void fireAlarm();

void setup() {
    pinMode(PIR_SENSOR, INPUT);
    pinMode(PIEZZO, OUTPUT);
    pinMode(LED, OUTPUT);

    delay(8000); // enables one to setup the device before it triggers the alarm
}

void loop() {
    if (digitalRead(PIR_SENSOR) == HIGH) {
        digitalWrite(LED, HIGH);
        fireAlarm();
    }
}

void fireAlarm() {
    unsigned long beatDuration = (1000 * TEMPO) / 60; // milliseconds

    Note melody[] = {
            Note {beatDuration, FREQ_G4},
            Note {2*beatDuration/3, FREQ_G4},
            Note {beatDuration/3, FREQ_G4},
            Note {beatDuration, FREQ_G4},
            Note {2*beatDuration/3, FREQ_Eb4},
            Note {beatDuration/3, FREQ_Bb4},
            Note {beatDuration, FREQ_G4},
            Note {2*beatDuration/3, FREQ_Eb4},
            Note {beatDuration/3, FREQ_Bb4},
            Note {beatDuration, FREQ_G4},
            Note {beatDuration, FREQ_PAUSE},
            Note {beatDuration, FREQ_D5},
            Note {2*beatDuration/3, FREQ_D5},
            Note {beatDuration/3, FREQ_D5},
            Note {beatDuration, FREQ_D5},
            Note {2*beatDuration/3, FREQ_Eb5},
            Note {beatDuration/3, FREQ_Bb4},
            Note {beatDuration, FREQ_Gb4},
            Note {2*beatDuration/3, FREQ_Eb4},
            Note {beatDuration/3, FREQ_Bb4},
            Note {beatDuration, FREQ_G4},
            Note {beatDuration, FREQ_PAUSE}
    };
    int melodyNotesCount = sizeof(melody)/sizeof(Note);

    while (true) {
        for (int i=0; i < melodyNotesCount; i++) {
            if (melody[i].frequency == FREQ_PAUSE) {
                noTone(PIEZZO);
            } else {
                tone(PIEZZO, melody[i].frequency, melody[i].duration);
            }
            delay(melody[i].duration);
        }
    }
}
