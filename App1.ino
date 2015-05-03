// App1.ino
//

#include "stm32_it.h"

// Pulse counts
const uint8_t pcs[][2] = {
    { 95, 72 }, // Init
    { 16, 44 },	// 0
    { 16, 16 }	// 1
};

// Command sequences, first code = sequence length
const uint8_t sq0[] = { 8, 0, 1, 1, 1, 2, 1, 2, 2 };
const uint8_t sq1[] = { 7, 0, 2, 2, 1, 1, 2, 2 };

// Current sequence
const uint8_t *sq = sq0;

// Run flags
volatile uint8_t l = 0;
volatile uint8_t r = 1;

// Mark/space, pulse count and sequence index
volatile uint8_t m = 1;
volatile uint32_t p = 0;
volatile uint8_t s = 1;

// Enable output
void mark() {
    pinMode(RX, AF_OUTPUT_PUSHPULL);
}

// Disable output
void space() {
    pinMode(RX, OUTPUT);
}

// Interrupt service routine
// A0 in PWM 38kHz connected to A1 w/interrupt on rising
void ISR_A1() {
	// Running mode changed?
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
            if (!m) {
                if (++s >= sq[0]) {
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

    tone(A0, 38000);
    tone(RX, 38000);

	// Start with output disabled
    r = 0;
}

void loop() {
    if (Serial.available()) {
        uint8_t k = Serial.read();

		// Command 1
        if (k == '1') {
            sq = sq0;
            r = !r;
        }
		// Command 2
        else if (k == '2') {
            sq = sq1;
            r = !r;
        }
    }
}
