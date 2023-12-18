//
// Derived from quadrature encoder interface example
//
// * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
// *
// * SPDX-License-Identifier: BSD-3-Clause
//
// The PIO program reads phase A/B of a quadrature encoder and increments or
// decrements an internal counter to keep the current absolute step count
// updated. At any point, the main code can query the current count by using
// the quadrature_encoder_*_count functions. The counter is kept in a full
// 32 bit register that just wraps around. Two's complement arithmetic means
// that it can be interpreted as a 32-bit signed or unsigned value, and it will
// work anyway.
//
// As an example, a two wheel robot being controlled at 100Hz, can use two
// state machines to read the two encoders and in the main control loop it can
// simply ask for the current encoder counts to get the absolute step count. It
// can also subtract the values from the last sample to check how many steps
// each wheel as done since the last sample period.
//
// One advantage of this approach is that it requires zero CPU time to keep the
// encoder count updated and because of that it supports very high step rates.
//

#include <Arduino.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "quadrature_encoder.pio.h"

// put function declarations here:

// declare variables
int new_qei_value =0;
int old_qei_value = 0;
int qei_delta = 0;
const u_int PIN_AB = 10;  // encoder A and B outputs connected to GPIO 10 and 11
const u_int sm = 0;       // state machine 0

// instantiate objects
PIO pio = pio0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pio_add_program(pio, &quadrature_encoder_program);
  quadrature_encoder_program_init(pio, sm, PIN_AB, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  new_qei_value = quadrature_encoder_get_count(pio, sm);
  qei_delta = new_qei_value - old_qei_value;
  old_qei_value = new_qei_value; 
  Serial.print("Value: ");
  Serial.print(new_qei_value); 
  Serial.print("  Delta: ");
  Serial.print(qei_delta);
  Serial.println();
  delay(100);
}

// put function definitions here:

