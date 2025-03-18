#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC output and ready status are not delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

#pragma config STVREN = ON      
#pragma config LVP = OFF        
#pragma config XINST = OFF      


#include <xc.h>
#define _XTAL_FREQ 4000000   

void CONF_PUERTOS(void);
void BORRAR_BASURA(void);
void LEER_OPERANDO_1(void);
void LEER_OPERANDO_2(void);
void LEER_OPERACION(void);
void FUNCION_ENTER(void);
void CALCULAR_RESULTADO(void);
void MOSTRAR_RESULTADO(void);

unsigned char OPERANDO_1;
unsigned char OPERANDO_2;
unsigned char selector;
unsigned char RESULTADO;

void main(void) 
{
    while(1)
    {
        CONF_PUERTOS();
        BORRAR_BASURA();
        
        FUNCION_ENTER();
        LEER_OPERANDO_1();
        LATD = OPERANDO_1; 
        
        FUNCION_ENTER();
        LEER_OPERANDO_2();
        LATD = OPERANDO_2; 
        
        FUNCION_ENTER();
        LEER_OPERACION();
        LATC = selector;
        
        FUNCION_ENTER();
        CALCULAR_RESULTADO();
        MOSTRAR_RESULTADO();
    }
}

void CONF_PUERTOS(void)
{
    TRISB = 0b00011111; 
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    ANSELB = 0b00000000; 
    INTCON2bits.RBPU = 0; 
}

void BORRAR_BASURA(void)
{
   LATC = LATD = 0; 
   OPERANDO_1 = OPERANDO_2 = selector = RESULTADO = 0;
}

void LEER_OPERANDO_1(void)
{
    OPERANDO_1 = PORTB & 0b00001111; 
}

void LEER_OPERANDO_2(void)
{
    OPERANDO_2 = PORTB & 0b00001111;
}

void LEER_OPERACION (void)
{        
    selector = PORTB & 0b00001111; 
}

void FUNCION_ENTER(void)
{
    while(PORTBbits.RB4 == 0) {} 
    __delay_ms(50);
    
    while(PORTBbits.RB4 == 1) {} 
    __delay_ms(50);
}

void CALCULAR_RESULTADO(void)
{
    switch(selector)
    {
        case 0: RESULTADO = OPERANDO_1 + OPERANDO_2; break;
        case 1: RESULTADO = OPERANDO_1 - OPERANDO_2; break;
        case 2: RESULTADO = OPERANDO_1 & OPERANDO_2; break;
        case 3: RESULTADO = OPERANDO_1 | OPERANDO_2; break;
        case 4: RESULTADO = OPERANDO_1 * OPERANDO_2; break;
        case 5: RESULTADO = (OPERANDO_2 != 0) ? (OPERANDO_1 / OPERANDO_2) : 0; break;
        default: RESULTADO = 0; break;    
    }  
}

void MOSTRAR_RESULTADO(void)
{
    LATD = RESULTADO; 
    __delay_ms(20000); 
    LATD = 0; 
}