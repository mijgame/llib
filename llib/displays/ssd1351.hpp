#ifndef LLIB_SSD1351_HPP
#define LLIB_SSD1351_HPP

#include "peripheral.hpp"
#include "base.hpp"
#include "wait.hpp"

// Todo: Code cleanup

namespace llib::displays {
    template<typename bs, typename dc, typename rs>
    class ssd1351 {
        protected:
            bs & bus;
            dc & data_command;
            rs & reset;

            void write_command(const uint8_t command){
                // wait data is transfered before writing
                while(bus.is_transfering());

                data_command.set(false);
                bus.write(command);
            }

            void write_data(const uint8_t * data, const size_t size){
                // wait data is transfered before writing
                while(bus.is_transfering());

                data_command.set(true);
                for(size_t i = 0; i < size; i++){
                    bus.write(data[i]);
                }
            }

        public:
            ssd1351(bs bus, dc data_command, rs reset):
                bus(bus), data_command(data_command), reset(reset)   
            {}

            void init(){
                // display setup
                reset.set(true);
                // wait 10ms to make sure the screen is on
                wait_for(llib::ms{10});
                // reset the display
                reset.set(false);
                // wait 10ms for the screen to completely reset
                wait_for(llib::ms{10});
                // enable the screen again
                reset.set(true);
                // wait 10ms for the screen to startup
                wait_for(llib::ms{10});

                // disable command lock
                set_command_lock(0); 
                // enable access to commands
                enable_power_options(1); 
                // turn sleep on(screen off)
                set_sleep_mode(1); 
                // set clock
                set_clock_divider(0xF1); 
                // set mux ratio
                set_mux_ratio(0x7F); 
                // set multiple screen settings
                set_re_co(0, 0, 1, 1, 1, 0x01); 
                // set start line(height)
                set_display_startline(0); 
                // set offset(width)
                set_display_offset(0); 
                // set gpio
                set_gpio(0); 
                // set power options and interface registers
                set_interface_reg(1, 0x00); 
                // set phases
                set_phases(0x2, 0x3);
                // set vsl 
                set_external_vsl(0); 
                // set com deselect voltage
                set_com_deselect_voltage(0x05); 
                // set master contrast
                set_master_contrast(0x0F); 
                // set second precharge period
                set_second_precharge(0x01); 
                // reset display commands
                set_display_mode(0x2); 
                // set color contrast
                set_color_contrast(0xFE, 0xFE, 0xFE); 
                //turn sleep off(screen on)
                set_sleep_mode(0); 
                // set start column
                set_column_address(0, 127);
                // set start row
                set_row_address(0, 127);                
            }

            void set_clock_divider(const uint8_t divider){
                // 0xB3 = command for changing the front clock divider
                write_command(0xB3);
                write_data(&divider, 1);
            } 

            void set_gpio(uint8_t gpio) {
                // 0xA2 = command for setting gpio
                gpio &= 0x0F;

                write_command(0xB5);
                write_data(&gpio, 1);
            }

            void set_display_offset(uint8_t offset) {
                // 0xA2 = command for display offset
                // For this command you need to enable the power options
                offset &= 0x7F;
                write_command(0xA2);
                write_data(&offset, 1);
            }

            void set_display_startline(uint8_t startline) {
                // 0xA1 = command for setting the starting line
                startline &= 0x7F;
                write_command(0xA1);
                write_data(&startline, 1);
            }

            void set_interface_reg(bool r, uint8_t interface) {
                // 0xAB = command to set the interface type and to enable and disable the internal regulator during sleep
                // A0 = 0b0 = Disable internal regulator during sleep
                // A0 = 0b1 = Enable internal regulator
                // A6:7 = 0b00 = Select 8-bit parallel interface
                // A6:7 = 0b01 = Select 16-bit parallel interface
                // A6:7 = 0b11 = Select 18-bit parallel interface
                interface = uint8_t((interface & 0x03) << 6 | r);

                write_command(0xAB);
                write_data(&interface, 1);
            }

            void set_command_lock(bool c) {
                // 0xFD = command for setting command lock without this unlocked the SSD1351 wont respond to commands and doesn't give memory access
                // 0x12 = disable command lock
                // 0x16 = enable command lock
                auto data = static_cast<uint8_t>(c ? 0x16 : 0x12);

                write_command(0xFD);
                write_data(&data, 1);
            }

            void set_phases(uint8_t c, uint8_t r) {
                // 0xFD = command for changing phase periods
                // A0:A3 = Phase 1 clocks
                // A4:A7 = Phase 2 clocks
                auto data = static_cast<uint8_t>(
                    r << 4 | (c & 0x0F)
                );

                write_command(0xB1);
                write_data(&data, 1);
            }

            void enable_power_options(bool o) {
                // Normaly you dont need these commands use with caution
                // enable to use commands 0xA2, 0xB1, 0xB3, 0xBB, 0xBE, 0xC1 these commands are necessary certain operations look at the datasheet for more info
                // 0xFD = command for setting command lock without this unlocked the SSD1351 wont respond to commands and doesn't give memory access
                // 0xB0 = dont allow access to the commands
                // 0xB1 = allow access to the commands
                auto data = static_cast<uint8_t>(0xB0 | uint8_t(o));

                write_command(0xFD);
                write_data(&data, 1);
            }

            void set_color_contrast(uint8_t A, uint8_t B, uint8_t C) {
                // 0xC1 = command for setting color contrast
                // For this command you need to enable the power options
                uint8_t data[] = {A, B, C};

                write_command(0xC1);
                write_data(data, 3);
            }

            void set_master_contrast(uint8_t M) {
                // 0xC7 = command for setting master contrast
                // the higher M is the more the output current is limited
                // 0x00 = reduce output currents for all color to 1/16
                //        ...
                // 0x0E = reduce output currents for all color to 15/16
                // 0x0F = no change
                M &= 0x0F;

                write_command(0xC7);
                write_data(&M, 1);
            }

            void set_mux_ratio(uint8_t m) {
                // 0xCA = command for mux ratio setting
                m &= 0x7F;

                write_command(0xCA);
                write_data(&m, 1);
            }

            void set_column_address(uint8_t start, uint8_t end) {
                // 0x15 = command for setting the column 
                // second byte is start adress
                // third byte is end adress
                uint8_t data[] = {
                        static_cast<uint8_t>(start & 0x7F),
                        static_cast<uint8_t>(end & 0x7F)
                };

                write_command(0x15);
                write_data(data, 2);
            }

            void set_row_address(uint8_t start, uint8_t end) {
                // 0x75 = command for setting the row
                // second byte is start adress
                // third byte is end adress
                uint8_t data[] = {
                        static_cast<uint8_t>(start & 0x7F),
                        static_cast<uint8_t>(end & 0x7F)
                };

                write_command(0x75);
                write_data(data, 2);
            }

            void set_display_mode(uint8_t mode) {
                // 0xA4:0xA7 = commands for the display modes
                // 0xA4 = All off
                // 0xA5 = All on
                // 0xA6 = reset to normal display
                // 0xA7 = Inverse Display
                mode = static_cast<uint8_t>(0xA4 | (mode & 0x03));
                write_command(mode);
            }

            void set_sleep_mode(bool s) {
                // 0xAE:0xAF = command for sleep state
                // 0xAE = Sleep mode on
                // 0xAF = Sleep mode off
                auto command = static_cast<uint8_t>(0xAF - s);
                write_command(command);
            }

            void set_re_co(bool increment, bool map, bool sequence, bool scan, bool split,
                                    uint8_t depth) {
                // Set Remap/ Color depth
                // A0 = 0b0 = Horizontal address increment
                // A0 = 0b1 = Vertical address increment
                // A1 = 0b0 = Column address 0 is mapped to SEG0
                // A1 = 0b1 = Column address 127 is mapped to SEG0
                // A2 = 0b0 = Color sequence A -> B -> C
                // A2 = 0b1 = Color sequence C -> B -> A
                // A3 = Reserved
                // A4 = 0b0 Scan from COM0 to COM[n-1]
                // A4 = 0b1 Scan from COM[n-1] to COM0
                // A5 = 0b0 Disable COM split odd even
                // A5 = 0b1 Enable COM split odd even
                // A6:7 = 0b00 = 65K color depth
                // A6:7 = 0b01 = 65K color depth
                // A6:7 = 0b10 = 262K color depth
                // A6:7 = 0b11 = 262K color depth, 16 bit format 2
                auto data = static_cast<uint8_t>(
                        (depth & 0x03) << 6
                        | split << 5
                        | scan << 4
                        | sequence << 2
                        | map << 1
                        | increment
                );

                write_command(0xA0);
                write_data(&data, 1);
            }

            void set_external_vsl(uint8_t v) {
                // Set VSL
                // 0xB4 = command for vsl
                // 0b00 = External VSL [reset]
                // 0b01, 0b10, 0b11 = invalid
                uint8_t data[] = {
                        static_cast<uint8_t>(0xA0 | (v & 0x03)),
                        0xB5,
                        0x55
                };

                write_command(0xB4);
                write_data(data, 3);
            }

            void set_com_deselect_voltage(uint8_t s) {
                // set com deselect voltage
                // 0xBE = com deselect voltage command
                // 0b000 = 0x00 = 0.72 x VCC\n
                // 0b101 = 0x05 = 0.82 x VCC [reset]\n
                // 0b111 = 0x07 = 0.86 x VCC\n
                s &= 0x07;

                write_command(0xBE);
                write_data(&s, 1);
            }

            void set_second_precharge(uint8_t p) {
                // set second pre-charge period
                // 0xB6 = second pre-charge period command
                // 0b0000 = invalid\n
                // 0b0001 = 1 DCLKS\n
                // 0b0010 = 2 DCLKS\n
                // 0b1111 = 15 DCLKS\n
                p &= 0x0F;

                write_command(0xB6);
                write_data(&p, 1);
            }

            void start_write() {
                write_command(0x5C);
            }

            void write_color(uint16_t color) {
                uint8_t arr[] = {
                        static_cast<uint8_t>(color >> 8),
                        static_cast<uint8_t>(color & 0xFF)
                };

                write_data(arr, 2);
            }
    };
}

#endif //LLIB_SSD1351_HPP
