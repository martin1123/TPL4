#include "Infotronic.h"

uint8_t Buff_Display[CANT_DIGITOS] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D };

uint8_t flag = OFF;
uint8_t tecla = NO_KEY;

uint8_t BufferRx[BUFF_SIZE];
uint8_t BufferRx[BUFF_SIZE];

int main(void) {

	uint8_t demora = OFF;
	Inicializar();


	while (1) {

		if (U1LSR& 0X20)
		{
			/*Se genera una demora de 250 ms con el systick*/
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

	/*
	 Inicializar();

	 while (1) {
	 Display7seg(123456);

	 if (flag) {
	 DriverDisplay();
	 flag = OFF;
	 }

	 }

	 /*
	 uint8_t c;
	 uint32_t Valor = 123456;

	 Inicializar();

	 while (1)
	 {

	 c = Tecla();
	 Display7seg (Valor);

	 switch (c)
	 {
	 case SUMAR: Valor++; break;
	 case RESTAR: Valor--; break;
	 default: break;
	 }

	 if(flag)
	 {
	 DriverDisplay();
	 TecladoSW ();
	 flag = OFF;
	 }

	 }*/

	return 0;
}

void SysTick_Handler(void) {
	static uint8_t i = 0;

	/*Se activa FLAG en ON cada 250 ms*/
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

