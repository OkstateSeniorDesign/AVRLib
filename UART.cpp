

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define F_CPU 8000000UL  // 8 MHz

volatile unsigned byte value;  

ISR(USART_RXC_vect){
 
   value = UDR;             //read UART register into value
}
void USARTInit(){USARTInit(BAUD_PRESCALE)}
void USARTInit(uint16_t baudRate){
   // Set baud rate
   UBRRL = F_CPU/(baudRate*16UL)-1;// Load lower 8-bits into the low byte of the UBRR register
   UBRRH = (F_CPU/(baudRate*16UL)-1 >> 8); 
	

  // Enable receiver and transmitter and receive complete interrupt 
  UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
}


void USART_SendByte(uint8_t u8Data){

  while((UCSRA &(1<<UDRE)) == 0);

  // Transmit data
  UDR = u8Data;
}


uint8_t USART_ReceiveByte(){
  while((UCSRA &(1<<RXC)) == 0);
  return UDR;
}


int main(void){
   USARTInit();  // Initialise USART
   sei();         // enable all interrupts
   for(;;){    // Repeat indefinitely
             
     USART_SendByte(value);  // send value 
     _delay_ms(250);         
		 
   }
}
