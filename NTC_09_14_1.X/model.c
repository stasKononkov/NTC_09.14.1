#include "model.h"
#include "analog_inputs.h"
#include "switchers.h"
#include "indication.h"

uint8_t WATER_LEVEL = 0;
uint8_t PUMP_VALUE = 0;
uint8_t VALVE_IN_VALUE = 0;
uint8_t VALVE_OUT_VALUE = 0;

uint8_t MODE = 0;

void indicate_level();
void data_collector();
void model_reset();

void model_init()
{
    model_reset();
}

void model_process()
{
    blink_set_value(L_INNER_LED_0, WATER_LEVEL);
    WATER_LEVEL = PUMP_VALUE*100;
    if(MODE == MODE_MANUAL)
    {
        
        
        //indicate_level();
    }
    else if (MODE == MODE_AUTO)
    {
        
    }
    data_collector();
}

void data_collector()
{
    PUMP_VALUE = get_supply();
    VALVE_IN_VALUE = get_pressure();
    VALVE_OUT_VALUE = get_outflow();
    
    if(switchers_is_on(MODE_ID))
    {
        MODE = MODE_AUTO;
    }
    else
    {
        MODE = MODE_MANUAL;
    }
}

void indicate_level()
{
    if(WATER_LEVEL >= 0 && WATER_LEVEL <= 10)
    {
        blink_set_value(L_INNER_LED_0, WATER_LEVEL/10);
    }
}

void model_reset()
{
    WATER_LEVEL = 40;
    PUMP_VALUE = 0;
    VALVE_IN_VALUE = 0;
    VALVE_OUT_VALUE = 0;
    MODE = -1;
}