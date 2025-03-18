#include <xc.h>                 
#define _XTAL_FREQ 4000000      

#pragma config FOSC = XT         
#pragma config PLLCFG = OFF      
#pragma config PRICLKEN = ON     
#pragma config FCMEN = OFF        
#pragma config IESO = OFF        

#pragma config PWRTEN = ON      
#pragma config BOREN = OFF      
#pragma config BORV = 190       
#pragma config WDTEN = OFF      
#pragma config WDTPS = 32768    

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
        case 5: RESULTADO = (OPERANDO_2 != 0) ? (OPERANDO_1 / OPERANDO_2) : 0; break; // Divisi�n con prevenci�n de error por cero
        default: RESULTADO = 0; break;    
    }  
}

void MOSTRAR_RESULTADO(void)
{
    LATD = RESULTADO; 
    __delay_ms(20000); 
    LATD = 0; 
}