#ifndef DISPLAY_32X32_LLIB_HPP
#define DISPLAY_32X32_LLIB_HPP

#include <pins.hpp>
#include <interrupt.hpp>

namespace llib::displays{
    template<typename R0, typename R1, typename G0, typename G1, typename B0, typename B1, typename A, typename B, typename C, typename D, typename OE, typename LAT, typename CLK>
    class display_32x32{
        private:
            constexpr inline static uint8_t height = 32;
            constexpr inline static uint8_t width = 32;
            constexpr static uint8_t page_size = 8;
            constexpr static uint8_t leds_per_page = 64;
            constexpr static uint16_t lookup[512] = {448, 449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367};

            static inline uint8_t buffer_r1[32*16];
            static inline uint8_t buffer_g1[32*16];
            static inline uint8_t buffer_b1[32*16];

            static inline uint8_t buffer_r2[32*16];
            static inline uint8_t buffer_g2[32*16];
            static inline uint8_t buffer_b2[32*16];

            static inline uint8_t curr_bit = 0;
            static inline uint8_t switch_bit = 0;            

        public:
            static void init(){
                pin_out<R0>::init();
                pin_out<R1>::init();
                pin_out<G0>::init();
                pin_out<G1>::init();
                pin_out<B0>::init();
                pin_out<B1>::init();
                pin_out<A>::init();
                pin_out<B>::init();
                pin_out<C>::init();
                pin_out<D>::init();
                pin_out<OE>::init();
                pin_out<LAT>::init();
                pin_out<CLK>::init();

                // init the display
                pin_out<R0>::set(false);
                pin_out<R1>::set(false);
                pin_out<G0>::set(false);
                pin_out<G1>::set(false);
                pin_out<B0>::set(false);
                pin_out<B1>::set(false);
                pin_out<A>::set(false);
                pin_out<B>::set(false);
                pin_out<C>::set(false);
                pin_out<D>::set(false);
                pin_out<OE>::set(true);
                pin_out<LAT>::set(true);
                pin_out<CLK>::set(false);

                // attatch update function to a interupt call TODO: add the timer
                // llib::target::attach_interrupt<handler, mask>(&flush);           
            }

            static void set_pixel(uint32_t x, uint32_t y, uint8_t red, uint8_t green, uint8_t blue){
                if(x >= height || y >= width){
                    // out of bounds
                    return;
                }

                // check if position is in top or bottom half of the screen
                if(y <= 0xF){
                    uint16_t position = y * width + x;
                    buffer_r1[lookup[position]] = red;
                    buffer_g1[lookup[position]] = green;
                    buffer_b1[lookup[position]] = blue;
                } else {
                    uint16_t position = (y - 16) * width + x;
                    buffer_r2[lookup[position]] = red;
                    buffer_g2[lookup[position]] = green;
                    buffer_b2[lookup[position]] = blue;                    
                }
            }

            static void clear(uint8_t red, uint8_t green, uint8_t blue){
                // range on buffer array
                for(uint16_t i = 0; i < (32 * 16); i++){
                    // set color on top half of the screen
                    buffer_r1[i] = red;
                    buffer_g1[i] = green;
                    buffer_b1[i] = blue;     

                    // set color on bottom half of the screen  
                    buffer_r2[i] = red;
                    buffer_g2[i] = green;
                    buffer_b2[i] = blue;       
                }
            }

            static void flush(){
                for (uint_fast8_t curr_page = 0; curr_page < page_size; curr_page++){
                    // // set page selection
                    pin_out<A>::set(curr_page & (1 << 0));
                    pin_out<B>::set(curr_page & (1 << 1));
                    pin_out<C>::set(curr_page & (1 << 2));
                    pin_out<D>::set(curr_page & (1 << 3)); 

                    // disable output so we can change the values
                    pin_out<OE>::set(false);
                    pin_out<LAT>::set(false);  

                    // write leds_per_page bits at a time
                    for(uint8_t z = 0; z < leds_per_page; z++){
                        uint16_t tot = (curr_page * leds_per_page) + z;
                        pin_out<R0>::set(buffer_r1[tot] & (1 << curr_bit));
                        pin_out<R1>::set(buffer_r2[tot] & (1 << curr_bit));

                        pin_out<G0>::set(buffer_g1[tot] & (1 << curr_bit));
                        pin_out<G1>::set(buffer_g2[tot] & (1 << curr_bit));

                        pin_out<B0>::set(buffer_b1[tot] & (1 << curr_bit));
                        pin_out<B1>::set(buffer_b2[tot] & (1 << curr_bit));                        

                        pin_out<CLK>::set(1);
                        pin_out<CLK>::set(0);
                    }                   

                    // enable output after update
                    pin_out<OE>::set(true);
                    pin_out<LAT>::set(true);                      
                }

                // update pixel on importance on bit position
                if(switch_bit){
                    // tick down the switch_bit every flush
                    switch_bit--;
                } else {
                    // update the current bit
                    if(curr_bit){
                        // move bit down if above 0
                        curr_bit--;
                    } else {
                        // reset the bit if 0
                        curr_bit = 3;
                    }
                    // calculate new switch_bit based on curr_bit
                    switch_bit = pow(2, curr_bit);
                }
            }
    };
}

#endif