#include "switchers.h"
#include "system.h"
#include "pin_definitions.h"

#define SWITCHER_ACTIVE_STATE 0

void switchers_init()
{
    MODE_CONFIG = 1;
    M1_HAND_CONFIG = 1;
    Y1_HAND_CONFIG = 1;
    Y2_HAND_CONFIG = 1;
    RES_CONFIG = 1;
    ACCIDENT_CONFIG = 1;
    READINESS_CONFIG = 1;
}

bool switchers_is_on(unsigned int switcherId)
{
    bool result = false;
    switch(switcherId) {
        case MODE_ID: 
            result = (MODE == SWITCHER_ACTIVE_STATE);
            break;
        case M1_HAND_ID:
            result = (M1_HAND  == SWITCHER_ACTIVE_STATE);
            break;
        case Y1_HAND_ID:
            result = (Y1_HAND == SWITCHER_ACTIVE_STATE);
            break;
        case Y2_HAND_ID:
            result = (Y2_HAND == SWITCHER_ACTIVE_STATE);
            break;
        case RES_ID:
            result = (RES == !SWITCHER_ACTIVE_STATE);
            break;
        case ACCIDENT_ID:
            result = (ACCIDENT == SWITCHER_ACTIVE_STATE);
            break;
        case READINESS_ID:
            result = (READINESS == SWITCHER_ACTIVE_STATE);
            break;
        default:
            break;
    }
    return result;
}

