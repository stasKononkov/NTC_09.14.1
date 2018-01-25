#include "analog_inputs.h"
#include "pin_definitions.h"

void configure_input_pins();
void configure_adc_module();

#define ADC_CHANNEL_COUNT 5

static uint16_t pressure = 0;
static uint16_t supply = 0;
static uint16_t outflow = 0;

void analog_inputs_init()
{
    configure_input_pins();
    configure_adc_module();
}

void configure_input_pins()
{ 
    // Setup pins as inputs
    M1_SET_CONFIG = 1;
    Y1_SET_CONFIG = 1;
    Y2_SET_CONFIG = 1;
    M1_REG_CONFIG = 1;
    Y1_REG_CONFIG = 1;

    // Configure as analog inputs
    AD1PCFGLbits.PCFG0 = 0;  //Y2_SET
    AD1PCFGLbits.PCFG2 = 0;  //Y1_SET
    AD1PCFGLbits.PCFG1 = 0;  //M1_SET
    AD1PCFGLbits.PCFG3 = 0;  //Y1_REG
    AD1PCFGLbits.PCFG4 = 0;  //M1_REG
        
    // Configure as digital inputs
    AD1PCFGLbits.PCFG5 = 1; 
    AD1PCFGLbits.PCFG6 = 1;
}

void configure_adc_module()
{
    AD1CON1bits.FORM   = 0;     // Unsigned int 12 bit format
	AD1CON1bits.SSRC   = 7;		// Sample Clock Source: GP Timer starts conversion
	AD1CON1bits.ASAM   = 1;		// ADC Sample Control: Sampling begins immediately after conversion
	AD1CON1bits.AD12B  = 1;		// 12-bit ADC operation

	AD1CON2bits.CSCNA = 1;		// Scan Input Selections for CH0+ during Sample A bit
	AD1CON2bits.CHPS  = 0;		// Converts CH0

	AD1CON3bits.ADRC = 0;		// ADC Clock is derived from Systems Clock
	AD1CON3bits.ADCS = 63;		// ADC Conversion Clock Tad=Tcy*(ADCS+1) ADCS = [0..63](6bit counter))
							    // ADC Conversion Time for 10-bit Tc=12*Tad
                                // ADC Conversion Time for 12-bit Tc=14*Tad 
    AD1CON3bits.SAMC = 31;      //SAMPLE TIME = 31*Tad
                                //Total Sample Time = Sample Time + Conversion Time =(14+31)*Tad
      
	AD1CON2bits.SMPI = (ADC_CHANNEL_COUNT-1);	// 5 ADC Channel is scanned
    
    AD1CON2bits.VCFG=0b111;  // Vref+  ---> AVdd, Vref- ---> AVss

	//AD1CSSH/AD1CSSL: A/D Input Scan Selection Register
	AD1CSSLbits.CSS0 = 1;
    AD1CSSLbits.CSS1 = 1;
    AD1CSSLbits.CSS2 = 1;
    AD1CSSLbits.CSS3 = 1;
    AD1CSSLbits.CSS4 = 1;
        
    IFS0bits.AD1IF = 0;			// Clear the A/D interrupt flag bit
    IEC0bits.AD1IE = 1;			// Enable A/D interrupt 
    IPC3bits.AD1IP=ADC_INTERRUPT_PRIORITY; // Set interrupt priority
    AD1CON1bits.ADON = 1;		// Turn on the A/D converter
}

void __attribute__((interrupt,no_auto_psv)) _ADC1Interrupt() {   
    
    pressure = ADC1BUF0;
    supply = ADC1BUF2;
    outflow = ADC1BUF1;
      
    IFS0bits.AD1IF=0;
}

uint16_t get_pressure()
{
    return pressure * CONVERT_COEF;
}

uint16_t get_supply()
{
    return supply * CONVERT_COEF;
}

uint16_t get_outflow()
{
    return outflow * CONVERT_COEF;
}
