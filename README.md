This is a simple quadrature encoder class for the Pico that is based on the Raspberry Pi Pico PIO examples.

It uses a state machine to provide an absolute value from a quadrature encoder (initialized to zero at start-up), 
as well as a delta from the last reading.

---------------------------------------------------------------------------

Derived from quadrature encoder interface example

 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause

 The PIO program reads phase A/B of a quadrature encoder and increments or
 decrements an internal counter to keep the current absolute step count
 updated. At any point, the main code can query the current count by using
 the quadrature_encoder_*_count functions. The counter is kept in a full
 32 bit register that just wraps around. Two's complement arithmetic means
 that it can be interpreted as a 32-bit signed or unsigned value, and it will
 work anyway.

 One advantage of this approach is that it requires zero CPU time to keep the
 encoder count updated and because of that it supports very high step rates.

 ----------------------------------------------------------------------------