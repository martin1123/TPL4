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

    int aux;

    if(bufferRxEmpty)
    	return -1;

    aux = BufferRx[inxRxOut++];
    inxRxOut %= TOPE_BUFFER;
    bufferRxFull = OFF;

    if (inxRxIn == inxRxOut)
    	bufferRxEmpty = ON;

    return aux;
}

int PushTx (unsigned char dato)
{
	if(bufferTxFull)
		return -1;

    BufferTx[inxTxIn++] = dato;
    inxTxIn %= TOPE_BUFFER;
    bufferTxEmpty = OFF;

    if (inxTxIn == inxTxOut)
    	bufferTxFull = ON;

    if (TxStart == 0)
    {
        TxStart = 1;
        bufferTxEmpty = ON;
        U1THR= BufferTx[inxTxOut++];
    }

    return 1;
}
