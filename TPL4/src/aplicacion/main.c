#include "Infotronic.h"

uint8_t Buff_Display[CANT_DIGITOS] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D };

uint8_t flag = OFF;
uint8_t tecla = NO_KEY;

volatile uint8_t BufferRx[TOPE_BUFFER];
volatile uint8_t BufferTx[TOPE_BUFFER];
volatile uint8_t inxRxIn;
volatile uint8_t inxRxOut;
volatile uint8_t inxTxIn;
volatile uint8_t inxTxOut;
volatile uint8_t TxStart;
volatile uint8_t bufferTxEmpty = ON;
volatile uint8_t bufferRxEmpty = ON;
volatile uint8_t bufferTxFull = OFF;
volatile uint8_t bufferRxFull = OFF;

void Transmitir (char *p);
void armarTrama(uint8_t c, char []);
int obtenerValorTrama(int v);

int main(void) {
	/*int b = 1;*/
	uint8_t c;
    uint32_t Valor = 0;
    char tramaTx[TRAMA_SIZE];
    Inicializar();

/*********************
 * Primera parte TPL4*
 *					 *
 *********************
	while (1) {

		if (U1LSR& 0X20)
		{
			//Se genera una demora de 250 ms con el systick
			if(demora == OFF)
			{
				demora = ON;
				//Se inicializa contador del systick
				activarDemora();
			}

			if(flag == ON)
			{
				demora = OFF;
				flag = OFF;
				U1THR = 0xAA;
			}

		}

	}
*/

	/*********************
	 * Segunda parte TPL4*
	 *					 *
	 *********************/

	 while (1)
	 {

		 c = Tecla();
		 //Actualiza Valor si se recibio dato por bufferRX
		 Valor = obtenerValorTrama(Valor);

		 Display7seg (Valor);

		 switch (c)
		 {
	 	 	 case SW1:
	 	 	 case SW2:
	 	 	 case SW3:
	 	 	 case SW4: armarTrama(c,tramaTx);
	 	 	 	 	   Transmitir(tramaTx);
	 	 	 	 	   break;
	 	 	 default: break;
		 }

		 if(flag)
		 {
			 DriverDisplay();
			 TecladoSW ();
			 flag = OFF;
		 }

	 }

	return 0;
}

void Transmitir (char *p)
{
    uint32_t i;

    for (i=0; p[i]; ++i)
         PushTx(p[i]);
}

void armarTrama(uint8_t c, char trama[])
{
	trama[0] = '#';
	trama[1] = c;
	trama[2] = '$';
	trama[3] = '\0';
}

/*Se recibe valor actual de V por parametro. Si se obtuvo toda la trama de datos
 * a recibir, se retorna el dato que interesa, almacenada en el buffer de trama
 * de recepcion. En caso de no obtenerse la trama, se retorna el mismo valor
 * recibido por parametro.*/
int obtenerValorTrama(int v)
{
	static int i = 0;
	static uint8_t tramaRx[TRAMA_SIZE];
	int r;

	r = PopRx();

	if(r != -1)
		tramaRx[i++] = (uint8_t)r;

	if(r == '$')
	{
		i = 0;
		return tramaRx[IND_DATA]; //Valor transmitido
	}
	return v;
}

void SysTick_Handler(void) {
	//Se activa FLAG en ON cada 2.5 ms
	flag = ON;
}

/*Parte A del TPL4*/
/*
void SysTick_Handler(void) {
	static uint8_t i = 0;

	//Se activa FLAG en ON cada 250 ms
	if(i < 100)
	{
		i++;
	}
	else
	{
		flag = ON;
		i = 0;
	}

}
*/
