#include "system.h"

#pragma config FNOSC=FRCPLL
#pragma config IESO=OFF
#pragma config FCKSM=CSECME
#pragma config OSCIOFNC=ON
#pragma config POSCMD=NONE
#pragma config IOL1WAY=OFF

/* Turns off JTAG and selects debug channel */
#pragma config JTAGEN=OFF
#pragma config ICS=PGD2

/* Disable WDT and configure it */
#pragma config FWDTEN=OFF
#pragma config WINDIS=OFF
#pragma config WDTPRE=PR32
#pragma config WDTPOST=PS2048
        
_PERSISTENT uint32_t sysFreq;

void system_init()
{
    RCONbits.SWDTEN = 0;
    
    SRbits.IPL = 0;
    
    CLKDIVbits.PLLPRE  = 0b00000;   //N1=2
    CLKDIVbits.PLLPOST = 0b00;     //N2=2
    PLLFBDbits.PLLDIV  = 0b101001;  //M=43
    
    unsigned char osc = 0b001;
    
    // Initiate Clock Switch
    __builtin_write_OSCCONH((unsigned char) osc);
    // Switch (first bit in OSCCONL)
    uint8_t val = OSCCONL;
    val |= 1;
    __builtin_write_OSCCONL(val);
    
    sysFreq = get_system_frequency();
}

uint32_t get_system_frequency()
{
    return INT_CRYSTAL_FREQ *
            (PLLFBD + 2) /
            ( (CLKDIVbits.PLLPOST + 2) * (CLKDIVbits.PLLPRE + 2) );
}
void interrupts_disable() {
    asm volatile ("disi #0x3FFF");
}

void interrupts_enable() {
    __builtin_write_DISICNT(0);
}