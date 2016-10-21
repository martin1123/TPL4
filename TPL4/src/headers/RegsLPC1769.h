/*
===============================================================================
 TPL2 - Systic Timer
===============================================================================
*/
#ifndef REGS_H_
#define REGS_H_

#define		__RW				volatile
typedef 	unsigned int 		uint32_t;
typedef 	unsigned short 		uint16_t;
typedef 	unsigned char 		uint8_t;
typedef 	__RW uint32_t 		registro_t;  //!< defino un tipo 'registro'.

///////////////////////////   MACROS PORTS   /////////////////////////////
#define		PORT0		0
#define		PORT1		1
#define		PORT2		2
#define		PORT3		3
#define		PORT4		4

#define		FUNCION_GPIO	0
#define		FUNCION_1		1
#define		FUNCION_2		2
#define		FUNCION_3		3

#define		MODO_0		0
#define		MODO_1		1
#define		MODO_2		2
#define		MODO_3		3

#define		ENTRADA		0
#define		SALIDA		1


//!< GPIO - PORT0
	/*	*						*
		*************************
		*		FIODIR			*	0x2009C000
		*************************
		*		RESERVED		*	0x2009C004
		*************************
		*		RESERVED		*	0x2009C008
		*************************
		*		RESERVED		*	0x2009C00C
		*************************
		*		FIOMASK			*	0x2009C010
		*************************
		*		FIOPIN			*	0x2009C014
		*************************
		*		FIOSET			*	0x2009C018
		*************************
		*		FIOCLR			*	0x2009C01C
		*************************
		*						*
		*						*
	*/



// REGISTROS ------------------------------------------------------------------------------------------------------------------------
#define		PINSEL		( ( registro_t  * ) 0x4002C000UL )		//!< Direccion de inicio de los registros PINSEL
#define		PINMODE		( ( registro_t  * ) 0x4002C040UL )		//!< Direccion de inicio de los registros de modo de los pines del GPIO
#define		GPIO		( ( registro_t  * ) 0x2009C000UL )		//!< Direccion de inicio de los registros de GPIOs

// 0xE000E010UL: Registro de control del SysTick:
#define 	SYSTICK		( (registro_t *) 0xE000E010UL )

#define		STCTRL		SYSTICK[ 0 ]
	#define	ENABLE			0
	#define	TICKINT			1
	#define	CLKSOURCE		2
	#define	COUNTFLAG		16
#define		STRELOAD	SYSTICK[ 1 ]
#define		STCURR		SYSTICK[ 2 ]
#define		STCALIB		SYSTICK[ 3 ]

#define TICKINT_ON    STCTRL |= 0x00000002 // pongo en 1  el bit 1 del STCTRL Hablito   interr del Systick
#define TICKINT_OFF   STCTRL &= 0xFFFFFFFD // pongo en 0  el bit 1 del STCTRL Deshablito interr del Systick

//  Power Control for Peripherals register (PCONP - 0x400F C0C4) [pag. 62 user manual LPC1769]
// 0x400FC0C4UL : Direccion de inicio del registro de habilitación de dispositivos:
#define 	PCONP	(* ( ( registro_t  * ) 0x400FC0C4UL ))

// Peripheral Clock Selection registers 0 and 1 (PCLKSEL0 -0x400F C1A8 and PCLKSEL1 - 0x400F C1AC) [pag. 56 user manual]
// 0x400FC1A8UL : Direccion de inicio de los registros de seleccion de los CLKs de los dispositivos:
#define		PCLKSEL		( ( registro_t  * ) 0x400FC1A8UL )
//!< Registros PCLKSEL
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]

#define DIR_UART ((volatile uint32_t *) 0x40010000UL)
#define DIR_UART1 DIR_UART[0]

#define U1LCR1 (*( ( registro_t  * ) 0x4001000CUL))

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
#define         ISER0                   (*( ( registro_t  * )  0xE000E100UL ))

#define	TXD		1
#define	RXD		1
#define IER_RBR 0x01
#define IER_THRE 0x02

#endif
