#include <watchdog.hpp>
#include <displays/display_32x32.hpp>
#include <ports.hpp>
#include <pins.hpp>
#include <wait.hpp>
#include <math.h>

using namespace llib::sam3x8e;

extern const int8_t sinetab[];

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

RGB ColorHSV(long hue, uint8_t sat, uint8_t val);

int main(){
    // kill the watchdog
    watchdog::disable();

    llib::displays::display_32x32<
        llib::port_out<pin_out<llib::due::pins::d2>, pin_out<llib::due::pins::d5>>, 
        llib::port_out<pin_out<llib::due::pins::d3>, pin_out<llib::due::pins::d6>>, 
        llib::port_out<pin_out<llib::due::pins::d4>, pin_out<llib::due::pins::d7>>, 
        llib::port_out<pin_out<llib::due::pins::a0>, pin_out<llib::due::pins::a1>, pin_out<llib::due::pins::a2>, pin_out<llib::due::pins::a3>>, 
        pin_out<llib::due::pins::d9>, 
        pin_out<llib::due::pins::d10>, 
        pin_out<llib::due::pins::d11>> 
    dis;

    dis.init<tc::channel_1, 60>();

    dis.clear(0x0, 0x0, 0x0);

    const float radius1  = 16.3, radius2  = 23.0, 
                radius3  = 40.8, radius4  = 44.2,
                centerx1 = 16.1, centerx2 = 11.6, 
                centerx3 = 23.4, centerx4 =  4.1, 
                centery1 =  8.7, centery2 =  6.5, 
                centery3 = 14.0, centery4 = -2.9;

    float angle1 = 0.0, angle2 = 0.0, 
          angle3 = 0.0, angle4 = 0.0;

    long hueShift =  0;

    int x1, x2, x3, 
        x4, y1, y2, 
        y3, y4, sx1, 
        sx2, sx3, sx4;
   
    while(true){
        sx1 = cos(angle1) * radius1 + centerx1;
        sx2 = cos(angle2) * radius2 + centerx2;
        sx3 = cos(angle3) * radius3 + centerx3;
        sx4 = cos(angle4) * radius4 + centerx4;
        y1  = sin(angle1) * radius1 + centery1;
        y2  = sin(angle2) * radius2 + centery2;
        y3  = sin(angle3) * radius3 + centery3;
        y4  = sin(angle4) * radius4 + centery4;

        uint8_t x, y;
        for(y=0; y < 32; y++) {
            x1 = sx1; x2 = sx2; x3 = sx3; x4 = sx4;
            for(x=0; x < 32; x++) {
            long value = hueShift
                + (sinetab[((x1 * x1 + y1 * y1) >> 2)])
                + (sinetab[((x2 * x2 + y2 * y2) >> 2)])
                + (sinetab[((x3 * x3 + y3 * y3) >> 3)])
                + (sinetab[((x4 * x4 + y4 * y4) >> 3)]);
            RGB t = ColorHSV(value * 3, 255, 255);
            dis.set_pixel(x, y, t.r, t.g, t.b);
            x1--; x2--; x3--; x4--;
            }
            y1--; y2--; y3--; y4--;
        }

        angle1 += 0.03;
        angle2 -= 0.07;
        angle3 += 0.13;
        angle4 -= 0.15;
        hueShift += 2;   

        llib::wait_for(llib::ms{50});
    }
}

RGB ColorHSV(long hue, uint8_t sat, uint8_t val) {
    uint8_t  r, g, b;

    // -1535 to +1535
    hue %= 1536;             

    if(hue < 0) {
        //     0 to +1535
        hue += 1536;
    } 

    // Low byte  = primary/secondary color mix
    uint8_t lo = hue & 0xFF; 

    // High byte = sextant of colorwheel         
    switch(hue >> 8) {       
        case 0: 
            // R to Y
            r = 255; 
            g = lo;
            b = 0; 
            break; 
        case 1: 
            // Y to G
            r = 255 - lo; 
            g = 255; 
            b = 0; 
            break; 
        case 2: 
            // G to C
            r = 0; 
            g = 255; 
            b = lo; 
            break; 
        case 3: 
            // C to B
            r = 0; 
            g = 255 - lo; 
            b = 255; 
            break;
        case 4: 
            // B to M
            r = lo;
            g = 0;
            b = 255;
            break; 
        default: 
            // M to R
            r = 255; 
            g = 0; 
            b = 255 - lo; 
            break; 
    }

    // Saturation: add 1 so range is 1 to 256, allowig a quick shift operation
    // on the result rather than a costly divide, while the type upgrade to int
    // avoids repeated type conversions in both directions.
    uint16_t s1 = sat + 1;
    r  = 255 - (((255 - r) * s1) >> 8);
    g  = 255 - (((255 - g) * s1) >> 8);
    b  = 255 - (((255 - b) * s1) >> 8);

    return {r, g, b};
}

const int8_t sinetab[256] = {
    0,   2,   5,   8,  11,  15,  18,  21,
    24,  27,  30,  33,  36,  39,  42,  45,
    48,  51,  54,  56,  59,  62,  65,  67,
    70,  72,  75,  77,  80,  82,  85,  87,
    89,  91,  93,  96,  98, 100, 101, 103,
    105, 107, 108, 110, 111, 113, 114, 116,
    117, 118, 119, 120, 121, 122, 123, 123,
    124, 125, 125, 126, 126, 126, 126, 126,
    127, 126, 126, 126, 126, 126, 125, 125,
    124, 123, 123, 122, 121, 120, 119, 118,
    117, 116, 114, 113, 111, 110, 108, 107,
    105, 103, 101, 100,  98,  96,  93,  91,
    89,  87,  85,  82,  80,  77,  75,  72,
    70,  67,  65,  62,  59,  56,  54,  51,
    48,  45,  42,  39,  36,  33,  30,  27,
    24,  21,  18,  15,  11,   8,   5,   2,
    0,  -3,  -6,  -9, -12, -16, -19, -22,
    -25, -28, -31, -34, -37, -40, -43, -46,
    -49, -52, -55, -57, -60, -63, -66, -68,
    -71, -73, -76, -78, -81, -83, -86, -88,
    -90, -92, -94, -97, -99,-101,-102,-104,
    -106,-108,-109,-111,-112,-114,-115,-117,
    -118,-119,-120,-121,-122,-123,-124,-124,
    -125,-126,-126,-127,-127,-127,-127,-127,
    -128,-127,-127,-127,-127,-127,-126,-126,
    -125,-124,-124,-123,-122,-121,-120,-119,
    -118,-117,-115,-114,-112,-111,-109,-108,
    -106,-104,-102,-101, -99, -97, -94, -92,
    -90, -88, -86, -83, -81, -78, -76, -73,
    -71, -68, -66, -63, -60, -57, -55, -52,
    -49, -46, -43, -40, -37, -34, -31, -28,
    -25, -22, -19, -16, -12,  -9,  -6,  -3
};
