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
