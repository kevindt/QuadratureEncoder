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

#include "quadrature_encoder.h"

// put function declarations here:
void qei_debug_serial();
// declare variables
int new_qei_value = 0;
int qei_delta = 0;
const u_int pin_AB = 4; // encoder A and B outputs connected to GPIO 4 and 5
const u_int state_machine = 0;
const int max_step_rate = 0;

// instantiate objects
PIO pio = pio0;
QuadratureEncoder qei(pio, state_machine, pin_AB, max_step_rate);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // main encoder
  qei.init();
}
void loop()
{
  // put your main code here, to run repeatedly:
  // get main encoder value and delta
  qei.poll_qei();
  new_qei_value = qei.new_val;
  qei_delta = qei.delta;
  qei_debug_serial();
  delay(10);
}
// put function definitions here:
//  qei print to Serial
void qei_debug_serial()
{
  Serial.print("Main Encoder Value: ");
  Serial.print(new_qei_value);
  Serial.print("  Main Encoder Delta: ");
  Serial.print(qei_delta);
  Serial.println();
}