#ifndef LLIB_WATCHDOG_HPP
#define LLIB_WATCHDOG_HPP

#include "base.hpp"

namespace llib::due {

    class watchdog {
    public:
        static void disable() {
            // Disable the watchdog timer
            WDT->WDT_MR = WDT_MR_WDDIS;
        }

        static void restart() {
            // Restart the watchdog timer
            WDT->WDT_CR = WDT_CR_WDRSTT | WDT_CR_KEY_PASSWD;
        }

        template<unsigned int CounterStart = 0xFFF, unsigned int Delta = 0xFFF, bool Reset = true>
        static void init() {
            WDT->WDT_MR = WDT_MR_WDIDLEHLT                          // Stop watchdog if cpu is in idle mode
                          | WDT_MR_WDDBGHLT                         // Stop watchdog if cpu is in debug state
                          | WDT_MR_WDFIEN                           // Enable watchdog interrupts
                          | WDT_MR_WDV(
                                  CounterStart)                // Set counter value (default takes 16 seconds to trigger Reset)
                          | WDT_MR_WDD(Delta)                       // Set the range the watchdog is allowed to restart
                          // If restart is before this value it will throw an error
                          | static_cast<uint32_t>(Reset
                    << 13);     // If true this will Reset the cpu if underflow or an error occurred
        }

        static bool watchdog_error() {
            // Returns if an error occurred since last read
            return static_cast<bool>(WDT->WDT_SR & WDT_SR_WDERR);
        }

        static bool watchdog_underflow() {
            // Returns if an underflow occurred since last read
            return static_cast<bool>(WDT->WDT_SR & WDT_SR_WDUNF);
        }
    };
}

#endif