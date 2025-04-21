# Lab03: Generación de PWM con PIC18F45K22

## Objetivos

1. Configurar el oscilador interno del ```PIC18F45K22``` con ```PLL``` habilitado, para alcanzar una frecuencia de operación de 64 MHz.

2. Implementar una señal PWM usando el módulo ```CCP1```, ajustando parámetros como el periodo y el ciclo útil (*duty cycle*) a través del temporizador 2.

3. Configurar ```Timer0``` como temporizador de 16 bits con prescaler, para generar eventos periódicos de temporización con precisión.

4. Usar interrupciones de ```Timer0``` para modificar automáticamente el ciclo útil del PWM, demostrando el control dinámico mediante hardware e interrupciones.

5. Leer el valor de un potenciómetro mediante el módulo ADC del microcontrolador y usarlo para ajustar el duty cycle del PWM en tiempo real.


## Materiales

1. ```PIC18F45K22```.
2. Pickit 3/4.
3. MPLAB X IDE + XC8 Compiler.
4. Un LED.
5. Osciloscopio.
6. Fuente de alimentación
7. Potenciómetro
8. Simulador Proteus (opcional).

## Planteamiento del problema:

Se desea generar una señal PWM con un ciclo de trabajo que aumente automáticamente en pasos, utilizando interrupciones del Timer0. La señal debe observarse mediante un osciloscopio y tener un periodo visible (por ejemplo, 100 ms entre cambios de duty). La frecuencia del sistema debe configurarse con el oscilador interno del PIC a 64 MHz mediante el PLL.

## Fundamento Teórico General

### PWM

PWM (*Pulse Width Modulation*) o Modulación por Ancho de Pulsos es una técnica ampliamente utilizada para controlar la potencia entregada a dispositivos eléctricos mediante la variación del ancho de los pulsos en una señal digital de alta frecuencia. Esta modulación se utiliza para controlar la cantidad de energía que se suministra a una carga, como un motor, un LED o incluso en sistemas de regulación de voltaje.

 <img src="/laboratorios/figs/lab03/pwm.png" alt="pwm" width="300" />

**Características clave del PWM**:

1. **Frecuencia**:
Es la cantidad de ciclos completos de la señal por segundo. La frecuencia de la señal PWM determina cuántos pulsos por segundo se envían al dispositivo. La frecuencia es importante porque debe ser alta lo suficiente como para que el ojo humano no perciba el parpadeo o el zumbido de los dispositivos, como un LED o un motor. Sin embargo, debe ser lo suficientemente baja como para no generar interferencia o ruido eléctrico.

$$ f = \dfrac{1}{\text{período}} = \dfrac{1}{f}$$

2. **Ciclo de trabajo (Duty Cycle)**:
 El ciclo de trabajo es el porcentaje del tiempo durante el cual la señal permanece en un nivel alto (encendida) durante un ciclo. Se calcula como la fracción del tiempo en que la señal está en estado alto con respecto al tiempo total del ciclo.


 $$ \text{Ciclo de trabajo}(\%) = \dfrac{\text{Tiempo en alto}}{\text{Período} \Big(T = \dfrac{1}{f}\Big)} $$


3. **Frecuencia y ciclo de trabajo**: La frecuencia y el ciclo de trabajo están relacionados, pero son independientes en cuanto al control. Mientras que la frecuencia controla cuántos ciclos se repiten por segundo, el ciclo de trabajo controla la cantidad de tiempo que la señal permanece "encendida" dentro de cada ciclo.



 <img src="/laboratorios/figs/lab03/PWM02.gif" alt="pwm" width="300" />


### PIC18F45K22 

#### Oscilador interno y PLL

El ```PIC18F45K22``` cuenta con un oscilador interno de $16$ MHz que puede ser multiplicado por $4$ mediante el uso del **PLL** (*Phase-Locked Loop*), lo cual permite una frecuencia de operación de hasta $64$ MHz. Esta frecuencia afecta todos los temporizadores, módulos PWM y ciclos de instrucción, por lo tanto, su correcta configuración es fundamental para un comportamiento preciso del sistema.

#### Módulo PWM (CCP)

El módulo ```CCP1``` permite generar una señal PWM cuyo periodo se define mediante el registro ```PR2``` y la frecuencia del ```Timer2```. El ciclo útil se ajusta mediante el registro ````CCPR1L```. La fórmula de la frecuencia de la señal PWM es:

$$ f_{PWM} = \dfrac{f_{osc}}{4 \times TMR2_{prescaler} \times (PR2+1)}$$


#### Temporizador 0 e interrupciones

El ```Timer0``` puede configurarse como temporizador de $16$ bits con prescaler para generar interrupciones periódicas. En este laboratorio, se usará para generar eventos cada $100$ ms. Dentro de la interrupción se puede modificar el duty cycle, logrando un control automatizado de la modulación.

#### ADC y control manual del PWM

El módulo ```ADC``` (*Analog-to-Digital Converter*) permite convertir una señal analógica (como la de un potenciómetro) en un valor digital. Este valor se puede mapear directamente al rango del duty cycle PWM (0 a $255$), permitiendo ajustar la potencia entregada al actuador de forma manual y en tiempo real.

## Procedimiento

### Parte 1: 

Consiste en condigurar el sistema  para operar a $64$ MHz usando el oscilador interno con PLL. Se habilita el módulo ```CCP1``` para generar PWM y se configura el ```Timer0``` con interrupciones para modificar periódicamente el ciclo útil.

#### Pasos:

1. Configuración inicial del proyecto:

    * Crear un nuevo proyecto en MPLAB X.

    * Configurar los fuses (bits de configuración) para establecer el uso del oscilador interno con PLL y desactivar el watchdog timer:

        ```
        #pragma config FOSC = INTIO67
        #pragma config PLLCFG = ON
        #pragma config WDTEN = OFF
        ```

    * Definir la frecuencia del sistema:
    
        ```
        XTAL_FREQ como 64000000UL
        ```

2. Configuración del oscilador

    * Confirmar que el PLL (Phase-Locked Loop) esté activado mediante configuración de fuses.

    * Usar el registro OSCCON para seleccionar el oscilador interno de 16 MHz como fuente de reloj base:

    ```
    OSCCON = 0b01110000;       // Oscilador interno a 16 MHz
    OSCTUNEbits.PLLEN = 1;     // Activa PLL 
    ```

    * Verificar que el PLL efectivamente multiplica la frecuencia base (16 MHz) por 4, resultando en un sistema de 64 MHz.

3. Configuración del módulo PWM (```CCP1```)

    * Configurar el pin RC2 como salida digital, ya que es donde se encuentra el módulo CCP1 que generará la señal PWM.

        ```
        TRISC2 = 0; // Salida digital
        ```

    * Habilitar el modo PWM en el módulo CCP1 a través del registro CCP1CON:

        ```
        CCP1CON = 0b00001100; // Modo PWM activado
        ```

    * Configurar el ```Timer2```, que actúa como reloj base del PWM:

        ```
        PR2 = 255;            // Valor del periodo del PWM
        T2CON = 0b00000111;   // Encender Timer2 con prescaler 1:16
        ```



4. Configuración del ```Timer0```: 

    * Activar el ```Timer0``` en modo $16$ bits con prescaler $1$:$256$, para generar interrupciones cada 100 ms:

        ```
        T0CON = 0b10000111;  // TMR0 ON, modo 16-bit, prescaler 1:256
        ```

    * Calcular el valor de recarga adecuado para 100 ms:

        * Frecuencia del sistema: 64 MHz → ciclo de instrucción = 64 MHz / 4 = 16 MHz

        * Periodo del ciclo: 1 / 16 MHz = 62.5 ns

        * Para 100 ms: 100 ms / 62.5 ns = 1,600,000 ciclos

        * Como TMR0 es 16-bit (0 a 65535), el valor a cargar sería: TMR0 = 65536 - 1600000 / 256 = 3036

        ```
        TMR0 = 3036;
        ```

    * Habilitar la interrupción de Timer0 y las interrupciones globales:

        ```
        INTCONbits.TMR0IE = 1; // Habilita interrupción TMR0
        INTCONbits.TMR0IF = 0; // Limpia bandera
        INTCONbits.GIE = 1;    // Interrupciones globales ON    
        ```

5. Interrupción del ```Timer0```

    * En la ```ISR```, incrementar el *duty cycle* (valor de $0$ a $255$): Implementar la rutina de servicio de interrupción (```ISR```) para actualizar el duty cycle cada $100$ ms:

    * Reiniciar el ```Timer0```.

    * Actualizar ```CCPR1L``` con el nuevo valor de *duty*.

5. Medición con el osciloscopio

    * Conectar la sonda del osciloscopio al pin ```RC2/CCP1```.

    * Verificar el cambio en el duty cycle cada $100$ ms.

    * Medir la frecuencia de la señal PWM teóricamente y expermientalmente.

    * Calcular el ciclo útil de la señal PWM en diferentes instantes de tiempo.

### Parte 2

El ADC convierte la tensión analógica entregada por el potenciómetro en un valor digital de $10$ bits ($0$ a $1023$). Para el PWM de $8$ bits ($0$ a $255$), basta con tomar los $8$ bits más significativos ($>> 2$). Esto permite usar el potenciómetro para controlar directamente el ciclo de trabajo del PWM.

#### Pasos:

1. Conectar el potenciómetro:

    * Terminal central a ```AN0``` (RA0)

    * Extremos a VDD y GND

2. Configurar ADC:
    ```
    void setupADC(void) {
    TRISA0 = 1;       // RA0 como entrada
    ANSELA0 = 1;      // Habilita analógico en RA0
    ADCON0 = 0b00000001; // Selecciona canal AN0, ADC ON
    ADCON1 = 0b00000000; // Vref+ = VDD, Vref- = VSS
    ADCON2 = 0b10111110; // Justificado a la derecha, Tacq, Fosc/64
    }
    ```
    ```
    unsigned int readADC(void) {
        ADCON0bits.GO = 1; // Inicia conversión
        while (ADCON0bits.GO); // Espera
        return ((ADRESH << 8) + ADRESL); // Resultado 10 bits
    }
    ```

3. En el ```main```, reemplazar el incremento del ciclo útil por la lectura del valor del ADC para ajustar el ciclo útil del PWM de manera dinámica según el valor analógico recibido:

    ```
    while (1) {
    unsigned int adc = readADC();
    duty = adc >> 2;       // Convertir 10 bits a 8 bits
    setDuty(duty);
    __delay_ms(50);
    }
    ```
       

## Entregables

1. Realice las partes [1](#parte-1) y [2](#parte-2) mencionadas en el procedimiento y presente
en clase las implementaciones de cada una al docente.

2. Realice la respectiva documentación de la implementación llevada a cabo.