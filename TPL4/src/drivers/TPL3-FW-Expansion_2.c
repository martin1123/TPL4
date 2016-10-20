#include "Infotronic.h"

extern uint8_t Buff_Display [];

void DriverDisplay (void)
{
	uint8_t auxiliar;
	static uint8_t digito = 0;

	// Apagado de los dígitos 0,1,2,3,4 y 5

	    	SetPIN(DIG1,0); // comun digito 0 apagado
			SetPIN(DIG2,0); // comun digito 1 apagado
			SetPIN(DIG3,0); // comun digito 2 apagado
			SetPIN(DIG4,0); // comun digito 3 apagado
			SetPIN(DIG5,0); // comun digito 4 apagado
			SetPIN(DIG6,0); // comun digito 5 apagado

	// Encendido de los segmentos a, b, c, d, e, f y g

	        auxiliar = Buff_Display[digito];
			SetPIN(seg_a,(auxiliar & 0x01));
			SetPIN(seg_b,((auxiliar >> 1) & 0x01));
			SetPIN(seg_c,((auxiliar >> 2) & 0x01));
			SetPIN(seg_d,((auxiliar >> 3) & 0x01));
			SetPIN(seg_e,((auxiliar >> 4) & 0x01));
			SetPIN(seg_f,((auxiliar >> 5) & 0x01));
			SetPIN(seg_g,((auxiliar >> 6) & 0x01));

	// Selección del digito a encender ( cíclico en modulo 6 )

			switch ((CANT_DIGITOS - 1) - digito) // Enciende los digitos de izq a der
			   {
					case DIGITO_5: SetPIN(DIG6,1); break;	// comun digito 5 encendido
					case DIGITO_4: SetPIN(DIG5,1); break;	// comun digito 4 encendido
					case DIGITO_3: SetPIN(DIG4,1); break;	// comun digito 3 encendido
					case DIGITO_2: SetPIN(DIG3,1); break;	// comun digito 2 encendido
					case DIGITO_1: SetPIN(DIG2,1); break;	// comun digito 1 encendido
					case DIGITO_0: SetPIN(DIG1,1); break;	// comun digito 0 encendido
		    	}

			digito ++;
			digito %= CANT_DIGITOS;
}

uint8_t DriverTeclado ( void )
{
	// Lectura de los pulsadores
	// Eliminación del rebote de los pulsadores

	if (GetPIN(BUTTON_0,ALTO)==0) //Fila 0
		return SUMAR;

	if (GetPIN(BUTTON_1,ALTO)==0) //Fila 1
		return RESTAR;

	if (GetPIN(BUTTON_2,ALTO)==0) //Fila 2
		return NO_KEY;

	if (GetPIN(BUTTON_3,ALTO)==0) //Fila 3
		return NO_KEY;

	return NO_KEY; //Caso en que se detecte otro boton presionad
}


