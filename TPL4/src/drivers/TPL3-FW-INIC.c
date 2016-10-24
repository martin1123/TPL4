
#include "Infotronic.h"


/********************************************************************************
	\fn  void Inicializar ( void )
	\brief Inicializacion de Hardware.
	\author & date: Informática II
 	\param void
	\return:	void
*/
void Inicializar ( void )
{
	InitPLL ( ) ;
	InicSysTick ( );
	InitExpansion();
	InitUART1();
}

/********************************************************************************
	\fn  void InicSysTick ( void )
	\brief Inicialización de Interrupcion Systick.
	\author & date: Informática II
 	\param void
	\return:	void
*/
void InicSysTick ( void )
{
	STRELOAD = (( STCALIB / 4) - 1);	// Recarga cada 2.5 ms
	STCURR = 0;	// Cargando con cero limpio y provoco el disparo de una intrrupcion
	// Habilito el conteo
	// Habilito interrupcion
	// Utilizamos Pclk
	STCTRL |=  ( ( 1 << ENABLE ) | ( 1 << TICKINT ) | ( 1 << CLKSOURCE ) );
}

void InitExpansion(void)
{
	SetPINSEL(DIG1,0); // comun digito 0 GPIO
	SetPINSEL(DIG2,0); // comun digito 1 GPIO
	SetPINSEL(DIG3,0); // comun digito 2 GPIO
	SetPINSEL(DIG4,0); // comun digito 3 GPIO
	SetPINSEL(DIG5,0); // comun digito 4 GPIO
	SetPINSEL(DIG6,0); // comun digito 5 GPIO
	SetPINSEL(seg_a,0); // segmento a
	SetPINSEL(seg_g,0); // segmento g
	SetPINSEL(seg_f,0); // segmento f
	SetPINSEL(seg_e,0); // segmento e
	SetPINSEL(seg_d,0); // segmento d
	SetPINSEL(seg_c,0); // segmento c
	SetPINSEL(seg_b,0); // segmento b

	SetDIR(DIG1,1); // salida
	SetDIR(DIG2,1); // salida
	SetDIR(DIG3,1); // salida
	SetDIR(DIG4,1); // salida
	SetDIR(DIG5,1); // salida
	SetDIR(DIG6,1); // salida
	SetDIR(seg_a,1); // salida
	SetDIR(seg_g,1); // salida
	SetDIR(seg_f,1); // salida
	SetDIR(seg_e,1); // salida
	SetDIR(seg_d,1); // salida
	SetDIR(seg_c,1); // salida
	SetDIR(seg_b,1); // salida
	// elección de GPIO - PINSEL
	// a, b, c, d, e, f, g, dp
	// común dígito 0, común dígito 1, común dígito 2
	// común dígito 3, común dígito 4, común dígito 5

	// Configuración de los puertos - FIODIR
	// a, b, c, d, e, f, g, dp
	// común dígito 0, común dígito 1, común dígito 2
	// común dígito 3, común dígito 4, común dígito 5

	SetPINSEL(BUTTON_0,0); // fila 0 GPIO pulsador mas a la derecha
	SetPINSEL(BUTTON_1,0); // fila 1 GPIO
	SetPINSEL(BUTTON_2,0); // fila 2 GPIO
	SetPINSEL(BUTTON_3,0); // fila 3 GPIO ante ultimo pulsador mas a la izquierda

	SetDIR(BUTTON_0,0); // entrada
	SetDIR(BUTTON_1,0); // entrada
	SetDIR(BUTTON_2,0); // entrada
	SetDIR(BUTTON_3,0); // entrada

	SetPINMODE(BUTTON_0,0); // pull up
	SetPINMODE(BUTTON_1,0); // pull up
	SetPINMODE(BUTTON_2,0); // pull up
	SetPINMODE(BUTTON_3,0); // pull up
}

void InitUART1 (void)
{
       PCONP |= 0x01<<4;	             //1.- Registro PCONP (0x400FC0C4) – bit 4 en 1 prende la UART1
       PCLKSEL0 &= ~(0x03<<8);  //2.- Registro PCLKSEL0 - bits 8 y 9 en 0 seleccionan que el clk de la UART1 sea CCLK/4

       U1LCR1 = 0x00000083;         //3.- Registro U1LCR - Tx de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1
       U1DLM = 0x0A; 	                //4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) – 9600 baudios:
       U1DLL = 0x2C;   	           //0x00D9 p/115200;

//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
       SetPINSEL(0,15,1); 	//TX0D   P0.2  PINSEL0: 4/5
       SetPINSEL(0,16,1);	//RX0D   P0.3  PINSEL0: 6/7
       U1LCR1 = 0x03;		 //6.- Registro U1LCR, pongo DLAB en 0

       U1IER = IER_RBR | IER_THRE ;		// Habilito interrupciones
       ISER0 |= (1<<6);

}
