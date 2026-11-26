#ifndef MHAA_CLOCK_EXAMPLE_FAKE_HPP
#define MHAA_CLOCK_EXAMPLE_FAKE_HPP

#include <clock/clock_source.hpp>
#include <clock/clock_control.hpp>

namespace example
{
    using namespace mhaa::clock;

    class Fake final : public ClockControl
    {
    public:
        bool frequency_hz(ClockDomain domain, uint32_t &rate) const override
        {
            ++queries;
            if (domain.kind != Domain::Peripheral)
            {
                return false;
            }
            if (domain.id == static_cast<DomainId>(1))
            {
                rate = 8000000;
                return true;
            }
            if (domain.id != DomainId{})
            {
                return false;
            }
            rate = frequency;
            return true;
        }
        bool set_frequency_hz(ClockDomain domain, uint32_t rate) override
        {
            if ((domain.kind != Domain::Peripheral || domain.id != DomainId{}) || rate != 1000000)
            {
                return false;
            }
            frequency = rate;
            return true;
        }

        uint32_t frequency = 32768;
        mutable unsigned queries = 0;
    };
}

#endif
