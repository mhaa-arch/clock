#include <clock/clock.hpp>
#include "../examples/fake.hpp"

#include <cassert>
#include <type_traits>

using namespace mhaa::clock;
using namespace example;

int main()
{
    static_assert(!std::is_constructible<Clock, Fake &&>::value,
                  "A clock cannot borrow a temporary");
    Fake source;
    Clock clock(source);
    uint64_t cycles = 7;
    assert(!clock.cycles_for_microseconds(Domain::Cpu, 100, cycles) && cycles == 7);
    assert(clock.cycles_for_microseconds(Domain::Peripheral, 1, cycles) && cycles == 1);
    assert(source.queries == 2);
    assert(!source.set_frequency_hz(Domain::Peripheral, 0));
    assert(source.set_frequency_hz(Domain::Peripheral, 1000000));
    assert(clock.cycles_for_microseconds(Domain::Peripheral, 11, cycles) && cycles == 11);
    source.frequency = UINT32_MAX;
    assert(clock.cycles_for_microseconds(Domain::Peripheral, UINT32_MAX, cycles));
    assert(cycles == UINT64_C(18446744065120));
    source.frequency = 0;
    assert(clock.cycles_for_microseconds(Domain::Peripheral, 50, cycles) && cycles == 0);

    uint32_t rate_hz = 23;
    const ClockDomain other_bus{Domain::Peripheral, static_cast<DomainId>(1)};
    assert(clock.frequency_hz(other_bus, rate_hz) && rate_hz == 8000000);
    const ClockDomain unknown_bus{Domain::Peripheral, static_cast<DomainId>(2)};
    assert(!clock.frequency_hz(unknown_bus, rate_hz) && rate_hz == 8000000);
    assert(clock.cycles_for_microseconds(other_bus, 3, cycles) && cycles == 24);
    assert(clock.frequency_hz(Domain::Peripheral, rate_hz) && rate_hz == 0);
    assert(!clock.set_frequency_hz(Domain::Peripheral, 0));
    assert(clock.set_frequency_hz(Domain::Peripheral, 1000000));
    assert(clock.frequency_hz(Domain::Peripheral, rate_hz) && rate_hz == 1000000);
    const Clock read_only(static_cast<const ClockSource &>(source));
    assert(!read_only.frequency_hz(Domain::LowSpeed, rate_hz));
}
