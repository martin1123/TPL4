/*
 * TPL4-PuertoSerie.c
 *
 *  Created on: 21 de oct. de 2016
 *      Author: Martin
 */
#include "Infotronic.h"
#include "RegsLPC1769.h"

int PopRx (void)
{

    int aux = -1;

    if (inxRxIn != inxRxOut)
      {
        aux = BufferRx[inxRxOut];
        inxRxOut ++;
        inxRxOut %= TOPE_BUFFER;
      }
 return aux;
}

void PushTx (unsigned char dato)
{
    BufferTx[inxTxIn] = dato;
    inxTxIn ++;
    inxTxIn %= TOPE_BUFFER;

    if (TxStart == 0)
       {
        TxStart = 1;
        U1THR= BufferTx[inxTxOut];
       }
}
