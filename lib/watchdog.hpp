#ifndef LLIB_WATCHDOG_HPP
#define LLIB_WATCHDOG_HPP

#include "peripheral.hpp"

namespace llib{
    namespace watchdog{
        static void disable(){
            // stop the watchdog timer
            WDT->WDT_MR = WDT_MR_WDDIS;
        }

        static void reload(){
            // restart the watchdog timer
            WDT->WDT_CR = WDT_CR_WDRSTT | WDT_CR_KEY_PASSWD;
        }

        template<unsigned int CounterStart = 0xFFF, unsigned int Delta = 0xFFF, bool reset = true>
        static void init(){
            WDT->WDT_MR = WDT_MR_WDIDLEHLT                          // stop watchdog if cpu is in idle mode
                          | WDT_MR_WDDBGHLT                         // stop watchdog if cpu is in debug state
                          | WDT_MR_WDFIEN                           // enable watchdog interupts
                          | WDT_MR_WDV(Counter)                     // set counter value(default takes 16 seconds to trigger reset)
                          | WDT_MR_WDD(Delta)                       // set the range the watchdog is allowed to restart
                                                                    // if restart is before this value it will trow an error
                          | static_cast<uint32_t>(reset << 13);     // if true this will reset the cpu if underflow or an error occured                        
        }

        static bool watchdog_error(){
            // returns if an error occured sinds last read
            return WDT->WDT_SR & WDT_SR_WDERR;
        }

        static bool watchdog_underflow(){
            // returns if an underflow occured sinds last read
            return WDT->WDT_SR & WDT_SR_WDUNF;
        }
    }
}

#endif