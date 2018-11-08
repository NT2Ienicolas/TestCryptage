//---------------------------------------------------------------------------

#ifndef UCryptageH
#define UCryptageH

#include <System.hpp>
#include <System.Classes.hpp>
//#include <windows.h>
//#include <windowsx.h>
//#include <commctrl.h>
//#include <ctype.h>
//#include <conio.h>
//#include <dlgs.h>
//#include <direct.h>

//#include <dos.h>
//#include <io.h>
//#include <fcntl.h>

//#include <math.h>
//#include <malloc.h>
//#include <memory.h>
//#include <mmsystem.h>
//#include <process.h>
//#include <shellapi.h>
//#include <signal.h>
//#include <string.h>

//#include <stdlib.h>
#include <stdio.h>
//#include <time.h>
//#include <vcl.h>

//#include <sys/types.h>
//#include <sys/timeb.h>
//#include <sys/stat.h>
//---------------------------------------------------------------------------
int lire (char nomfic[400]);
void ecrire (char nomfic[400]);
void decrypte_crypte (char lachaine[5000], char j);
void encrypte (char nomficOrig[400], char nomficDest[400]);
void decrypte (char nomficOrig[400], char nomficDest[400]);
int ReadKeyString (char sSection[50], char sKey[50], char sValue[5000], char nomfichier[400]);
#endif
