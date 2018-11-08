//---------------------------------------------------------------------------

#ifndef UCryptageH
#define UCryptageH

#include <System.hpp>
#include <System.Classes.hpp>
#include <stdio.h>
//---------------------------------------------------------------------------
int lire (char nomfic[400]);
void ecrire (char nomfic[400]);
void decrypte_crypte (char lachaine[5000], char j);
void encrypte (char nomficOrig[400], char nomficDest[400]);
void decrypte (char nomficOrig[400], char nomficDest[400]);
int ReadKeyString (char sSection[50], char sKey[50], char sValue[5000], char nomfichier[400]);
#endif
