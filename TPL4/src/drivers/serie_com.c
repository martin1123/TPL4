/////////////////////////////////////////////////////////////////
/* algunas funciones que pueden ser utilizadas en la programacion de la UART del LPC1769
 *
 *//////////////////////////////////////////////////////////////////////////////////
#include "Infotronic.h"
#include "RegsLPC1769.h"

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
                            U1THR = dato_tx;
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

void PushRx (unsigned char dato)
{
  BufferRx[inxRxIn] = dato;           //recibo
  inxRxIn++;
  inxRxIn %= TOPE_BUFFER;
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
