# Lab04: Comunicación UART en PIC18F45K22

## Objetivos

1. Configurar el módulo UART en un ```PIC18F45K22``` para permitir la comunicación serial.

2. Transmitir datos a través del UART desde el PIC hacia un terminal serial conectado a través de USB-UART.

3. Implementar funciones de transmisión y recepción de datos a través de UART.

4. Visualizar los datos recibidos en el terminal y comprender el proceso de transmisión asíncrona.

## Materiales

1. PIC18F45K22 o cualquier PIC compatible.

2. Programador/debugger PICkit 3/4.

2. Fuente de alimentación (o PICkit 3/4).

3. Conversor USB a serial UART (por ejemplo el CP2102).

4. Cable de conexión entre el conversor y el PC.

5. Software de terminal serial (puede usar PuTTY, Tera Term, o cualquier terminal de comunicación serial).


## Fundamento teórico

El módulo **EUSART** (Enhanced Universal Synchronous Asynchronous Receiver Transmitter) del ```PIC18F45K22``` permite la comunicación serial tanto síncrona como asíncrona. En este laboratorio se usará en modo asíncrono (**UART**), que no requiere señal de reloj adicional y es muy común para comunicación con PCs u otros dispositivos.

* UART (Universal Asynchronous Receiver/Transmitter) es un protocolo de comunicación serial utilizado para la transmisión de datos de forma asíncrona, es decir, sin necesidad de una señal de reloj externa. En un sistema UART, dos dispositivos se comunican a través de dos líneas: TX (transmisión) y RX (recepción). El PIC18F45K22 tiene un módulo UART que se puede configurar para transmitir y recibir datos en serie.

    * Baud Rate: La tasa de transferencia de datos. El valor común para este ejemplo es 9600 bps.

    * Bits de datos: Generalmente se usan 8 bits de datos en la transmisión.
  
    * Paridad: La paridad es un mecanismo de verificación que añade un bit extra a los datos transmitidos para detectar posibles errores en la comunicación serial.No se usa en este ejemplo.

    * Bits de parada: Un bit de parada indica el final de un *byte* transmitido.


## Procedimiento

### Descripción del funcionamiento del código en Github Classroom

1. Función ```UART_Init(void)```:


    * ```TRISC6 = 0``` configura el pin ```RC6``` como salida (TX).

    * ```TRISC7 = 1``` configura el pin ```RC7``` como entrada (RX).

        Estos pines están conectados internamente al módulo EUSART.

    * ```SPBRG1``` es el registro que determina el divisor del reloj para establecer la velocidad de baudios.

        En este caso, el módulo USART en el ```PIC18F45K22``` debe configurarse para transmitir y recibir datos a una velocidad de $9600$ bps. El valor de la constante de baudios (```SPBRG```) debe calcularse según la fórmula:

        $$SPBRG=\frac{f_{osc}}{64×Baudrate}−1$$

        Para un oscilador de $16$ MHz y un baudrate de $9600$, el valor de ```SPBRG``` es $25$.

    * ```BRGH = 0```: Baja velocidad (divisor de 64)

        Este bit se encuentra en el registro ```TXSTA1``` y controla la velocidad del generador de baud rate:

        * Generador de Baud Rate de 8 bits (```BRG16 = 0```):

            Cuando el bit ```BRG16 ``` está configurado a $0$, significa que el generador de baud rate utiliza un registro de 8 bits (```SPBRG```) para almacenar el valor calculado. Esto permite generar velocidades de transmisión, pero con una precisión limitada debido a la resolución del registro de $8$ bits (pudiendo almacenar valores de $0$ a $255$).

            En este caso, el divisor de la frecuencia de reloj para el cálculo del baud rate es 64. Es una fórmula más simple, y la velocidad de transmisión se ajusta dentro de una precisión razonable.

            Es lo que se conoce como baja velocidad asincrónica.

        * Generador de Baud Rate de $16$ bits (```BRG16 = 1```):

            Cuando ```BRG16``` está configurado a $1$, el generador de baud rate usa un registro de $16$ bits, lo que permite una mayor precisión en el cálculo del baud rate, ya que puede almacenar valores mucho mayores (de $0$ a $65535$).

            Con ```BRG16 = 1```, se puede configurar un baud rate más preciso y ajustarlo más finamente para obtener una transmisión más exacta en ciertas aplicaciones que requieren velocidades más altas.




<!-- <div align="center">
 <img src="/laboratorios/figs/lab04/uart1.png" alt="pwm" width="850" />
 </div>
 <div align="center">
 <img src="/laboratorios/figs/lab04/uart2.png" alt="pwm" width="850" />
 </div>

 <div align="center">
 <img src="/laboratorios/figs/lab04/uart3.png" alt="pwm" width="850" />
 </div> -->