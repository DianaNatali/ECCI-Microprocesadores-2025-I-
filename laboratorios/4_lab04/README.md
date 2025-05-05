# Lab04: Comunicación UART en PIC18F45K22

## Objetivos

1. Configurar el módulo UART en un ```PIC18F45K22``` para permitir la comunicación serial.

2. Transmitir datos a través del UART desde el PIC hacia un terminal serial conectado a través de USB-UART.

3. Implementar funciones de transmisión y recepción de datos a través de UART.

4. Visualizar los datos recibidos en el terminal y comprender el proceso de transmisión asíncrona.

## Materiales

1. PIC18F45K22 o cualquier PIC compatible.

2- Conversor USB a serial UART (por ejemplo el CP2102).

3. Cable de conexión entre el conversor y el PC.

4. Computador con software de terminal serial (puede usar PuTTY, Tera Term, o cualquier terminal de comunicación serial).


## Fundamento teórico

UART (Universal Asynchronous Receiver/Transmitter) es un protocolo de comunicación serial utilizado para la transmisión de datos de forma asíncrona, es decir, sin necesidad de una señal de reloj externa. En un sistema UART, dos dispositivos se comunican a través de dos líneas: TX (transmisión) y RX (recepción). El PIC18F45K22 tiene un módulo UART que se puede configurar para transmitir y recibir datos en serie.

* Baud Rate: La tasa de transferencia de datos. El valor común para este ejemplo es 9600 bps.

* Bits de datos: Generalmente se usan 8 bits de datos en la transmisión.
  
* Paridad: Normalmente no se usa en este ejemplo.

* Bits de parada: Un bit de parada indica el final de un byte transmitido.

* Configuración del módulo UART

    El módulo UART en el ```PIC18F45K22``` debe configurarse para transmitir y recibir datos a una velocidad de 9600 bps. El valor de la constante de baudios (```SPBRG```) debe calcularse según la fórmula:

    $$ SPBRG=\frac{F_{osc}}{64×Baudrate}−1$$

    Para un oscilador de $64$ MHz y un baudrate de $9600$, el valor de ```SPBRG``` es $25$.

## Procedimiento

### Parte 1: Configuración del UART en el PIC18F45K22
`
<div align="center">
 <img src="/laboratorios/figs/lab04/uart1.png" alt="pwm" width="850" />
 </div>
 <div align="center">
 <img src="/laboratorios/figs/lab04/uart2.png" alt="pwm" width="850" />
 </div>

 <div align="center">
 <img src="/laboratorios/figs/lab04/uart3.png" alt="pwm" width="850" />
 </div>