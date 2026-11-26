# Using Clock across targets

The only project dependency is the matching `clock-contract`. Keep its API revision aligned with this Core.

Cycle counts based on one nominal rate are suitable for arithmetic about that snapshot. They cannot guarantee wall-clock time across rate changes or compensate for oscillator drift. Keep the selected clock and its lifetime under the same composition as the caller using the result.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
