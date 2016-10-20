/*
 * Display_7_seg.c
 *
 *  Created on: 04/06/2014
 *      Author: Hernan
 */
#include "RegsLPC1769.h"
#include "Infotronic.h"

extern uint8_t Buff_Display [] ;

extern uint8_t tecla;

unsigned char Tabla_Digitos_BCD_7seg[] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D, 0x7C, 0x07, 0x7f, 0x67};

void Display7seg ( uint32_t valor  )
{
	uint8_t i;
	 // uint8_t aux [CANT_DIGITOS];

	  for (i = CANT_DIGITOS - 1; i>0; i--)
	    {
		 Buff_Display [i] = Tabla_Digitos_BCD_7seg[valor%10];
		 valor /= 10;
	    }
	  Buff_Display [i] = Tabla_Digitos_BCD_7seg[valor%10];

}


void TecladoSW (void)
{
  static uint8_t CodigoAnterior = NO_KEY;
  static uint8_t contador = 0;
  uint8_t CodigoActual;

  CodigoActual = DriverTeclado();

  if (CodigoActual == NO_KEY)
    {
      CodigoAnterior = NO_KEY;
      contador = 0;
      return;
    }

  if (contador == 0)
    {
      CodigoAnterior = CodigoActual;
      contador ++;
      return;
    }

  if (contador == CANT_REBOTES)
    {
      contador++;
      tecla = CodigoAnterior; // tecla es el buffer donde almaceno la tecla validada
      return;
    }

  if (contador > CANT_REBOTES)
      return;

  if (CodigoActual == CodigoAnterior)
      contador ++;
  else
      contador = 0;

  return;

}

uint8_t Tecla ( void )
{
	uint8_t Tecla;

	  Tecla = tecla;
	  tecla = NO_KEY;

	  return Tecla;
	// leer buffer
	// borrar buffer
	// retornar código de tecla
}

