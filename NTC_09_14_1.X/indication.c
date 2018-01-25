#include "indication.h"
#include "pin_definitions.h"

Blink blinks[INDICATOR_COUNT];

void set_pattern(uint32_t pattern);

void indication_init()
{
    SDI_VD_CONFIG = 0;
    CLK_VD_CONFIG = 0;
    LE_VD_CONFIG = 0;
    uint8_t i;
    for(i = 0; i < INDICATOR_COUNT; ++i)
    {
        blinks[i].tick_counter = 0;
        blinks[i].blink_once = 0;
        blinks[i].state = 0;
        blinks[i].period_ticks = 0;
    }
    /*
    uint8_t *indPtr = &IND_STATUS;
    uint8_t i;
    for(i = 0; i < INDICATOR_COUNT; ++i) 
    {
        indPtr[i] = 0;
    }
    */
}

void indication_update()
{   
    interrupts_disable();
    uint32_t data = 0;
    uint8_t i;
    for(i = 0; i < INDICATOR_COUNT; ++i)
    {
        if(blinks[i].state)
            data |= (1UL << i);
    }
    set_pattern(0x00);
    set_pattern(data);
    
    interrupts_enable();
}

void set_pattern(uint32_t pattern)
{
    uint8_t i;
    for(i = 0; i < 24; ++i)
    {
        SDI_VD = (pattern & 1);
        CLK_VD = 1;
        CLK_VD = 0;
        pattern >>= 1;
    }
    SDI_VD = 0;
    LE_VD = 1;
    LE_VD = 0;
}

void blink_tick()
{
    uint8_t i;
    for(i = 0; i < INDICATOR_COUNT; ++i)
    {
        blinks[i].tick_counter++;
    }
}
void blink()
{
    uint8_t i = 0;
    for(i = 0; i < INDICATOR_COUNT; ++i)
    {
        if(blinks[i].tick_counter >= blinks[i].period_ticks && blinks[i].period_ticks != 0)
        {
            if(blinks[i].blink_once)
            {
                blinks[i].period_ticks = 0;
                blinks[i].blink_once = false;
            }
            blinks[i].state = !blinks[i].state;
            blinks[i].tick_counter = 0;
        }
    }    
}

void disable_all_indicator()
{
    uint8_t i;
    for(i = 0; i < INDICATOR_COUNT; ++i)
    {
        blinks[i].state = 0; 
    }
}
void blink_set_value(unsigned int id, float ratio)
{
    if(id <= INDICATOR_COUNT && ratio >= 0.0f && ratio <= 1.0f) {
        blinks[id].period_ticks = 500 * ratio;        
    }
}

void blink_set_initial_state(unsigned int id, bool state)
{
    if(id <= INDICATOR_COUNT) {
         //blinks[id].initialState = state;        
    }
}
