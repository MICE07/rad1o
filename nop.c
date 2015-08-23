#include <r0ketlib/display.h>
#include <r0ketlib/print.h>
#include <r0ketlib/keyin.h>
#include <r0ketlib/itoa.h>
#include <rad1olib/pins.h>

#include <rad1olib/light_ws2812_cortex.h>
#include <rad1olib/setup.h>
#include <r0ketlib/display.h>

#include "usetable.h"

static void redraw(uint8_t brightness,uint8_t pattern,uint8_t ledposition1,uint8_t ledposition2,uint8_t ledposition3);

//# MENU ws2812b
void ram(void){
    uint8_t brightness = 0;
    uint8_t pattern = 0;
    uint8_t mydelay = 80;
    uint8_t mycounter = 0;
    uint8_t submenu = 0;
    uint8_t ledposition1 = 0;
    uint8_t ledposition2 = 7;
    uint8_t ledposition3 = 0;
    uint8_t leddirection1 = 0;
    uint8_t leddirection2 = 1;

    getInputWaitRelease();

    SETUPgout(RGB_LED);

    while(1){
        lcdClear(0xff);
        lcdPrintln("WS2812B LEDs 0.4");
        lcdPrintln("ENTER: exit");
        lcdPrintln("L/R: menu");

        switch(submenu){
            case 0:
                lcdPrintln("U/D: brightness");
                switch(getInput()){
                    case BTN_UP:
                        if(brightness < 10)
                            redraw(++brightness,pattern,ledposition1,ledposition2,ledposition3);
                        break;
                    case BTN_DOWN:
                        if(brightness > 0)
                            redraw(--brightness,pattern,ledposition1,ledposition2,ledposition3);
                        break;
                    case BTN_LEFT:
                        if(submenu > 0)
                            --submenu;
                        break;
                    case BTN_RIGHT:
                        if(submenu < 2)
                            ++submenu;
                        break;
                    case BTN_ENTER:
                        return;
                };
                break;
            case 1:
                lcdPrintln("U/D: pattern");
                switch(getInput()){
                    case BTN_UP:
                        if(pattern < 4)
                        {
                            ledposition1 = 2;
                            leddirection1 = 0;
                            ledposition2 = 6;
                            leddirection2 = 1;
                            redraw(brightness,++pattern,ledposition1,ledposition2,ledposition3);
                        }
                        break;
                    case BTN_DOWN:
                        if(pattern > 0)
                        {
                            ledposition1 = 2;
                            leddirection1 = 0;
                            ledposition2 = 6;
                            leddirection2 = 1;
                            redraw(brightness,--pattern,ledposition1,ledposition2,ledposition3);
                        }
                        break;
                    case BTN_LEFT:
                        if(submenu > 0)
                            --submenu;
                        break;
                    case BTN_RIGHT:
                        if(submenu < 2)
                            ++submenu;
                        break;
                    case BTN_ENTER:
                        return;
                };
                break;
            case 2:
                lcdPrintln("U/D: delay");
                switch(getInput()){
                    case BTN_UP:
                        if(mydelay < 500)
                        {
                            if (mydelay < 10)
                                mydelay++;
                            else if (mydelay < 30)
                                mydelay = mydelay + 5;
                            else if (mydelay < 80)
                                mydelay = mydelay + 10;
                            else
                                mydelay = mydelay + 50;
                        }
                        break;
                    case BTN_DOWN:
                        if(mydelay > 0)
                        {
                            if (mydelay < 10)
                                mydelay--;
                            else if (mydelay < 30)
                                mydelay = mydelay - 5;
                            else if (mydelay < 80)
                                mydelay = mydelay - 10;
                            else
                                mydelay = mydelay - 50;
                        }
                        break;
                    case BTN_LEFT:
                        if(submenu > 0)
                            --submenu;
                        break;
                    case BTN_RIGHT:
                        if(submenu < 2)
                            ++submenu;
                        break;
                    case BTN_ENTER:
                        return;
                };
                break;
        };
        lcdDisplay();
        if (++mycounter >= mydelay)
        {
             mycounter = 0;
             switch(pattern){
                case 2:
                    if(ledposition1 >= 7)
                        leddirection1 = 1;
                    else if (ledposition1 <= 0)
                        leddirection1 = 0;
                    if(leddirection1 == 0)
                        ledposition1++;
                    else
                        ledposition1--;
                    break;
                case 3:
                    if(ledposition1 >= 7)
                        ledposition1 = 0;
                    else
                        ledposition1++;
                    break;
                case 4:
                    if(ledposition1 >= 6)
                    {
                        ledposition1 = 6;
                        leddirection1 = 1;
                    }
                    else if (ledposition1 <= 2)
                    {
                        ledposition1 = 2;
                        leddirection1 = 0;
                    }
                    if(leddirection1 == 0)
                        ledposition1++;
                    else
                        ledposition1--;
                    if(ledposition2 >= 6)
                    {
                        ledposition2 = 6;
                        leddirection2 = 1;
                    }
                    else if (ledposition2 <= 2)
                    {
                        ledposition2 = 2;
                        leddirection2 = 0;
                    }
                    if(leddirection2 == 0)
                        ledposition2++;
                    else
                        ledposition2--;
                    if(ledposition3 == 0)
                        ledposition3 = 1;
                    else
                        ledposition3 = 0;
                    break;
             }
             redraw(brightness,pattern,ledposition1,ledposition2,ledposition3);
        }
    };
    return;
};

static void redraw(uint8_t brightness,uint8_t pattern,uint8_t ledposition1,uint8_t ledposition2,uint8_t ledposition3){
    uint8_t patternarray[] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    };
// 00 01 02
// 03 04 05 
// 06 07 08
// 09 10 11
// 12 13 14
// 15 16 17
// 18 19 20
// 21 22 23
        switch(pattern){
            case 0:
                patternarray[0] = 255;
                patternarray[1] = 255;
                patternarray[3] = 255;
                patternarray[4] = 255;
                patternarray[8] = 255;
                patternarray[11] = 255;
                patternarray[14] = 255;
                patternarray[17] = 255;
                patternarray[20] = 255;
                patternarray[21] = 255;
                break;
            case 1:
                patternarray[0] = 255;
                patternarray[4] = 255;
                patternarray[8] = 255;
                patternarray[9] = 255;
                patternarray[13] = 255;
                patternarray[17] = 255;
                patternarray[18] = 255;
                patternarray[22] = 255;
                break;
            case 2:
            case 3:
                for(uint8_t i=0; i<sizeof(patternarray); i++){
                    if (i % 3 == 0)
                        patternarray[i] = 255;
                    if (i == (ledposition1*3) + 1)
                    {
                        patternarray[i-1] = 0;
                        patternarray[i] = 255;
                    }
                }
                break;
            case 4:
                for(uint8_t i=0; i<sizeof(patternarray); i++){
                    if (i % 3 == 0)
                        patternarray[i] = 255;
                    if (i == (ledposition1*3) + 1)
                    {
                        patternarray[i-1] = 0;
                        patternarray[i] = 255;
                    }
                    if (i == (ledposition2*3) + 1)
                    {
                        patternarray[i-1] = 0;
                        patternarray[i] = 255;
                    }
                    if (i == (ledposition3*3) + 2)
                    {
                        patternarray[i-2] = 0;
                        patternarray[i] = 255;
                    }
                }
                break;
        }

    for(uint8_t i=0; i<sizeof(patternarray); i++){
        patternarray[i] = patternarray[i] * brightness / 10;
    }

    ws2812_sendarray(patternarray, sizeof(patternarray));
}
