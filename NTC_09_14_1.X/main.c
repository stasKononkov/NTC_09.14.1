#include "system.h"
#include "timer.h"
#include "switchers.h"
#include "indication.h"
#include "pin_definitions.h"
#include "analog_inputs.h"
#include "model.h"

int main()
{
    system_init();
    
    timer_init();
    
    switchers_init();
    
    indication_init();
    
    analog_inputs_init();
    
    model_init();
        
    while(1)
    {
        blink();
        model_process();
        
    }
    
    return 0;
}
