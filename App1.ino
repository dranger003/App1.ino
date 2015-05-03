// hamster-crazy.ino
//

#include "stm32_it.h"

#define IR_FREQ     38000

// Pulse counts
const uint8_t pcs[][2] = {
    { 94, 72 }, // Init
    { 16, 16 }, // 0
    { 16, 44 }  // 1
};

// Command sequences
// First index = length
const uint8_t vol_up[] = {
    50,
    0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1
};

const uint8_t vol_down[] = {
    50,
    0, 2, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1
};

// Test sequences
const uint8_t sq0[] = { 8, 0, 1, 1, 1, 2, 1, 2, 2 };
const uint8_t sq1[] = { 7, 0, 2, 2, 1, 1, 2, 2 };

// Current sequence
const uint8_t *sq = sq0;

// Run flags
volatile uint8_t l = 0;
volatile uint8_t r = 1;

// Mark/space, pulse count, sequence index
volatile uint8_t m = 1;
volatile uint32_t p = 0;
volatile uint8_t s = 1;

// Enable PWM
void mark() {
    pinMode(RX, AF_OUTPUT_PUSHPULL);
}

// Disable PWM
void space() {
    pinMode(RX, OUTPUT);
}

void ISR_A1() {
    // Run mode change
    if (r != l) {
        if (r)
            mark();
        else
            space();

        l = r;

        return;
    }

    if (r) {
        if (p >= pcs[sq[s]][!m]) {
            // m = mark, !m = space
            // !m = mark index, m = space index
            if (!m) {
                if (++s >= sq[0] + 1) {
                    // Sequence complete, reset
                    s = 1;
                    r = !r;
                }
                else {
                    mark();
                }
            }
            else {
                space();
            }

            p = 0;
            m = !m;
        }
        else {
            ++p;
        }
    }
}

void setup() {
    // Debug stuff
    Serial.begin(115200);
    while (!Serial.available()) {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\r\nsetup()");

    attachInterrupt(A1, ISR_A1, RISING);

    tone(A0, IR_FREQ);
    tone(RX, IR_FREQ);

    // Start not running
    r = 0;
}

void loop() {
    if (Serial.available()) {
        uint8_t k = Serial.read();
        if (k == '1') {
            sq = sq0;
            r = !r;
        }
        else if (k == '2') {
            sq = sq1;
            r = !r;
        }
        else if (k == 'u') {
            sq = vol_up;
            r = !r;
        }
        else if (k == 'd') {
            sq = vol_down;
            r = !r;
        }
    }
}
