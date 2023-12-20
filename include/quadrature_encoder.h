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
// Converted to class QuadratureEncoder.
//
#pragma once
// needs for pio quadrature encoder
#include <Arduino.h>
#include "quadrature_encoder.pio.h"

class QuadratureEncoder
{
private:
    int old_val;

public:
    PIO pio;
    u_int sm;
    u_int PIN_AB;
    int max_step_rate;
    int new_val;
    int delta;
    // constructor
    QuadratureEncoder(PIO _pio, u_int _sm, u_int _pin, int _max_step_rate)
    {
        pio = _pio;
        sm = _sm;
        PIN_AB = _pin;
        max_step_rate = _max_step_rate;
    }
    // public functions
    void init()
    {
        pio_add_program(pio, &quadrature_encoder_program);
        quadrature_encoder_program_init(pio, sm, PIN_AB, max_step_rate);
        new_val = 0;
        delta = 0;
        old_val = 0;
    }
    void poll_qei()
    {
        new_val = quadrature_encoder_get_count(pio, sm);
        delta = new_val - old_val;
        old_val = new_val;
    }
};
