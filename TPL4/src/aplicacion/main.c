#include "Infotronic.h"

uint8_t Buff_Display[CANT_DIGITOS] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D };

uint8_t flag = OFF;
uint8_t tecla = NO_KEY;

uint8_t BufferRx[TOPE_BUFFER];
uint8_t BufferTx[TOPE_BUFFER];
uint8_t inxRxIn;
uint8_t inxRxOut;
uint8_t inxTxIn;
uint8_t inxTxOut;
uint8_t TxStart;

void Transmitir (char *p);
void armarTrama(uint8_t c, char []);
int obtenerValorTrama(int v);

int main(void) {
	int b = 1;
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

		 /**TEST-INI**/
		 if(b)
		 {
			 armarTrama(1,tramaTx);
			 Transmitir(tramaTx);
			 b = 0;
		 }
		 /**TEST-FIN**/
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

int obtenerValorTrama(int v)
{
	int i;
	char tramaRx[TRAMA_SIZE];

	for(i = 0; i < TRAMA_SIZE && (tramaRx[i] = PopRx()) !=-1; i++);

	if(tramaRx[0] != -1)
		return tramaRx[1]; //Valor transmitido

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
