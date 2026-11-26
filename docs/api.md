# Use the Clock Core

Public entry headers are [clock/clock.hpp](../include/clock/clock.hpp).

## Query or calculate

Construct `Clock` from a live `const ClockSource&` for reading. Call `frequency_hz` to distinguish an unavailable domain from one reporting zero. `cycles_for_microseconds` samples the rate once, computes a 64-bit result and rounds any fraction up. A zero rate or duration gives zero cycles. An unavailable domain leaves the output unchanged.

## Change a rate

Construct from a `ClockControl&` when reconfiguration is part of the composition. The Core rejects zero and returns false for a read-only binding or a rejected request. It forwards positive requests and leaves the implementation to manage switching.

## Composition and lifetime

Application code calls the Clock Core. It borrows the matching Contract, which an Adapter implements using its Hardware Definitions. Future Devices will create or bind these objects and establish their lifetime. To use the examples today, construct the facade directly with the supplied fake. Keep each borrowed resource alive for its use by the facade and follow the Adapter's access and synchronization requirements.
