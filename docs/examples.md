# Run the Clock Core example

A fake reporting 32,768 Hz is borrowed by `Clock`. Asking for one million microseconds yields 32,768 cycles. Inspect the behavior test for an unavailable domain, fractional rounding, a stopped clock and inputs at the 32-bit limit. The same facade works with a source that never supports rate changes.

## Example program

The [program](../examples/example.cpp) uses the [local fake](../examples/fake.hpp) to demonstrate injection. A concrete Adapter implementing the same Contract can be supplied to the same facade.

```cpp
#include <clock/clock.hpp>
#include "fake.hpp"

using namespace mhaa::clock;
using namespace example;

int main()
{
    Fake source;
    Clock clock(source);
    uint64_t cycles = 0;
    return clock.cycles_for_microseconds(Domain::Peripheral, 1000000, cycles) &&
                   cycles == 32768
               ? 0
               : 1;
}
```

## Build and run

Build from this repository root. Set `contract_include` to the matching Contract's `include/` directory. The value below applies to the MHAA development workspace. Both programs exit with status 0 on success and print no output. On Windows execute `example.exe` and `behavior.exe`.

```sh
contract_include=../../contracts/clock-contract/include
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" examples/example.cpp -o example
./example
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -I"$contract_include" tests/behavior.cpp -o behavior
./behavior
```

See the [behavior test](../tests/behavior.cpp) for the additional cases described above.
