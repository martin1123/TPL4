/////////////////////////////////////////////////////////////////
/* algunas funciones que pueden ser utilizadas en la programacion de la UART del LPC1769
 *
 *//////////////////////////////////////////////////////////////////////////////////

#define SYSTEMCORECLOCK		100000000UL	// 100 MHZ
#define			U1RBR					(*( ( registro_t  * ) 0x40010000UL ))// Receiver Buffer Register. (DLAB = 0)		RO
#define			U1THR					(*( ( registro_t  * ) 0x40010000UL ))// Transmit Holding Register. (DLAB = 0)	WO
#define			U1DLL					(*( ( registro_t  * ) 0x40010000UL ))// Divisor Latch LSB. (DLAB = 1)			RW		0x01

#define			U1IER					(*( ( registro_t  * ) 0x40010004UL ))// Interrupt Enable Register. (DLAB = 0)	RW		NA
#define			U1DLM					(*( ( registro_t  * ) 0x40010004UL ))// Divisor Latch MSB. (DLAB = 1)			RW		NA

#define			U1IIR					(*( ( registro_t  * ) 0x40010008UL ))// Interrupt ID Register					RO		0x01
#define			U1FCR					(*( ( registro_t  * ) 0x40010008UL ))// FIFO Control Register					WO		0x00

#define			U1LCR					(*( ( registro_t  * ) 0x4001000cUL ))// Line Control Register					RW		0x00

#define			U1LSR					(*( ( registro_t  * ) 0x40010014UL ))// Line Status Register						RO		0x60

#define			U1SCR					(*( ( registro_t  * ) 0x4001001cUL ))// Scratch Pad Register						RW		0x00
#define			U1ACR					(*( ( registro_t  * ) 0x40010020UL ))// Auto-baud Control Register				RW		0x00
#define			U1ICR					(*( ( registro_t  * ) 0x40010024UL ))// IrDA Control Register					RW		0x00
#define			U1FDR					(*( ( registro_t  * ) 0x40010028UL ))// Fractional Divider Register				RW		0x10
#define			U1TER					(*( ( registro_t  * ) 0x40010030UL ))// Transmit Enable Register					RW		0x80

#define			UART1					( ( registro_t  * ) 0x40010000UL )

#define	TXD		1
#define	RXD		1


void UART1_IRQHandler (void)
{
 uint8_t aux, dato_tx, dato;

    do
      {
        aux = U1IIR; // una vez que lo lei se resetea

        switch (aux & 0x06)
           {
             case 0x02: dato_tx = PopTx ();
                        if (dato_tx > 0)
                            U1THRE = dato_tx;
                        else
                            TxStart = 0; // aviso que puedo volver a transmitir
                        //BufferTx[inxOut]; //transmito
                        //inxOut++;
                        //inxOut %= TOPE_BUFFER;
                        break;

             case 0x04: dato = U1RBR;
                        PushRx (dato);
                        //BufferRx[inxIn] = U1RBR;           //recibo
                        //inxIn++;
                        //inxIn %= TOPE_BUFFER;
                        break;

             case 0x06: //errores
                        break;
           }
    } while ((aux & 0x01) == 0); // me fijo si hay otra interrupcion pendiente -> b0 = 0

}

int PopRx (void)
{
    int aux = -1;

    if (inxRxIn != inxRxOut)
      {
        aux = BufferRx[inxRxOut];
        inxRxOut ++;
        inxRxOut &= TOPE_BUFFER;
      }
 return aux;
}

void PushRx (unsigned char dato)
{
  BufferRx[inxIn] = dato;           //recibo
  inxIn++;
  inxIn %= TOPE_BUFFER;
}

int PopTx (void)
{
  int aux = -1;

  if (inxTxIn != inxTxOut)
    {
      aux = BufferTx[inxTxOut];
      inxTxOut ++;
      inxTxOut &= TOPE_BUFFER;
    }

  return aux;
}

void PushTx (unsigned char dato)
{
    BufferTx[inxTxIn] = dato;
    inxTxIn ++;
    inxTxIn &= TOPE_BUFFER;

    if (TxStart == 0)
       {
        TxStart = 1;
        U1THR= BufferTx[inxTxOut];
       }
}

void Transmitir (char *p)
{
    uint32_t i;

    for (i=0; p[i]; ++i)
         PushTx(p[i]);
}

void UART1_Init(int baudrate)
{
    int pclk,Fdiv;

    // PCLK_UART0 is being set to 1/4 of SystemCoreClock
    pclk = SYSTEMCORECLOCK / 4;

    // Enciendo la UART0 (On por default)
    ///LPC_SC->PCONP |=  PCUART0_POWERON;

    //Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 - 0x400FC1A8 and PCLKSEL1 - 0x400FC1AC)
    // A pair of bits in a Peripheral Clock Selection register controls the rate of the clock signal
    // that will be supplied to the corresponding peripheral as specified in Table 40, Table 41 and
    // 00 PCLK_peripheral = CCLK/4 (Reset value)
    // 01 PCLK_peripheral = CCLK
    // 10 PCLK_peripheral = CCLK/2
    // 11 PCLK_peripheral = CCLK/8, except for CAN1, CAN2, and CAN filtering when “11” selects = CCLK/6.

    // Turn on UART0 peripheral clock
    ///LPC_SC->PCLKSEL0 &= ~(PCLK_UART0_MASK);
    ///LPC_SC->PCLKSEL0 |=  (0 << PCLK_UART0);		// PCLK_periph = CCLK/4

    // Seleccion de los pines como Tx y Rx de la UART1
    SetPINSEL( 0 , 15 , TXD );
    SetPINSEL( 0 , 16 , RXD );

    U1LCR = 0x83;						// 8 bits, no Parity, 1 Stop bit, DLAB=1

    // Sin divisor Fraccional
    Fdiv = ( pclk / 16 ) / baudrate ;	// FR = 1
    U1DLM = Fdiv / 256;
    U1DLL = Fdiv % 256;					// BR medida = 9642 con un Er = 0.44% - MUY BUENO !!!

    U1LCR = 0x03;						// 8 bits, no Parity, 1 Stop bit DLAB = 0
    U1FCR = 0x00; 						//FIFO disabled

    U1IER = IER_RBR | IER_THRE ;		// Habilito interrupciones
    ISER0 |= (1<<6);
}
