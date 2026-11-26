#ifndef MHAA_CLOCK_HPP
#define MHAA_CLOCK_HPP

#include <stdint.h>
#include <clock/clock_source.hpp>
#include <clock/clock_control.hpp>
#include <clock/types.hpp>

namespace mhaa
{
    namespace clock
    {
        /** @brief Samples nominal frequency from one borrowed clock source. */
        class Clock
        {
        public:
            explicit Clock(const ClockSource &source) : source_(source), control_(nullptr) {}
            explicit Clock(ClockControl &source) : source_(source), control_(&source) {}
            Clock(const ClockSource &&) = delete;

            bool frequency_hz(ClockDomain domain, uint32_t &frequency_hz) const
            {
                return source_.frequency_hz(domain, frequency_hz);
            }

            bool set_frequency_hz(ClockDomain domain, uint32_t frequency_hz)
            {
                return control_ && frequency_hz != 0 && control_->set_frequency_hz(domain, frequency_hz);
            }

            /** @brief Rounds fractional cycles up. Preserves cycles if frequency is unavailable. */
            bool cycles_for_microseconds(ClockDomain domain, uint32_t duration_us, uint64_t &cycles) const
            {
                uint32_t rate_hz = 0;
                if (!frequency_hz(domain, rate_hz))
                {
                    return false;
                }

                constexpr uint64_t microseconds_per_second = 1000000;
                const uint64_t scaled = uint64_t{rate_hz} * duration_us;
                cycles = (scaled + microseconds_per_second - 1) / microseconds_per_second;
                return true;
            }

        private:
            const ClockSource &source_;
            ClockControl *control_;
        };
    }
}

#endif
