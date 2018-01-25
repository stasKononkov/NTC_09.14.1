#include "timer.h"
#include "system.h"
#include "indication.h"
#include "pin_definitions.h"

static unsigned int blink_ticks = 0;

void timer_init()
{
    T1CONbits.TON = 0;      // Turn off Timer 1
    T1CONbits.TCS = 0;      // 0 - Internal clock, 1 - External clock (TxCK pin)
    T1CONbits.TGATE = 0;    // Don't use Gated Timer mode
    T1CONbits.TSYNC = 0;    // 1 - Synchronize external clock input, 0 - Don't synchronize
                            // When TCS=0 - unused
    T1CONbits.TCKPS = 0b01; // Prescaler:
                            // 00 - 1:1
                            // 01 - 1:8
                            // 10 - 1:64
                            // 11 - 1:256
    TMR1 = 0x00;            // Reset Timer register
    PR1 = FCY / 8000;
    // Setup Timer1 interrupt handling
    IPC0bits.T1IP = MS_TIMER_INTERRUPT_PRIORITY;  // IPL
    IFS0bits.T1IF = 0;           // Clear interrupt flag
    IEC0bits.T1IE = 1;           // Enable interrupt
    // Start Timer1
    T1CONbits.TON = 1;      
    
    //Timer 3 indication
    T3CONbits.TON = 0;
    T3CONbits.TCS = 0;
    T3CONbits.TGATE = 0;
    T3CONbits.TCKPS = 0b01;
    IPC2bits.T3IP = INDICATION_TIMER_INTERRUPT_PRIORITY; 
    PR3 = FCY/(1000);//(8000);
    TMR3=0;
    IFS0bits.T3IF = 0;          
    IEC0bits.T3IE = 1; 
    T3CONbits.TON = 1;
    
    TRISCbits.TRISC3 = 0;
}

void __attribute__((__interrupt__,auto_psv)) _T1Interrupt(void)
{   
    blink_tick();
    
    IFS0bits.T1IF = 0;
}

void __attribute__((__interrupt__,auto_psv)) _T3Interrupt(void)
{   
    indication_update();
    IFS0bits.T3IF = 0;
}

unsigned int get_blink_ticks()
{
    return blink_ticks;
}

void reset_blink_ticks()
{
    blink_ticks = 0;
}

