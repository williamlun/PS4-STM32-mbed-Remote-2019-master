#include "pinDefind.h"

//Serial  device(PA_2, PA_3); // UART0 tx,rx
//Serial  PS(PA_9, PA_10);  // UART1 tx, rx

//extern volatile uint16_t PC_rx_in; //真傳
int main() 
{
    
    
    PC_SERIAL_INIT();
    PS4_SERIAL_INIT();
    while (1) {checkFlatLoop();}
}
// Interupt Routine to read in data from serial port
