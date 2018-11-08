/* -----------------------------------------------------------------------*
 * MODULE CryptDLL.cpp
 *
 * (c) Copyright 2014, Cezanne S.A.S.
 *         All rights reserved.
 *
 *----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------*
 * !!! TODO !!!
 *-----------------------------------------------------------------------*
 *
 * - factoriser code
 * - quid du contournement possible par 2 allumages successifs de XIPC ? => faire une lecture à blanc et tester intégrité avant toute écriture => si échec : abandon ? audit trail, etc ?
 * - avertir de la nécessité d'utiliser pour tous les WritePrivateProfileString des fichiers controlés par l'application => notice d'utilisation !
 *
 *----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------*
 * INCLUDED HEADER FILES
 *----------------------------------------------------------------------- */

#include "CryptDLL.h"

#include <vcl.h>
#include <windows.h>
#include <dos.h>
#include <stdio.h>
#include <System.hpp>
#include <System.Classes.hpp>
#include "md5.h"
#include "UCryptage.h"

/* -----------------------------------------------------------------------*
 * LOCAL CONSTANTS (within this module)
 *----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------*
 * LOCAL STRUCTURES AND TYPE DEFINITIONS (within this module)
 *----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------*
 * LOCAL PROTOTYPES (within this module)
 *----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------*
 * LOCAL GLOBALS (within this module)
 *----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
/* ---------------------------- P U B L I C S ---------------------------- */
/* ----------------------------------------------------------------------- */

#pragma argsused

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason,
	void * lpReserved) {
	switch (reason) {
		// Initialize once for each new process (Return FALSE to fail DLL load)
	case DLL_PROCESS_ATTACH:
		// MessageBox(NULL, "attach", "kichk", MB_OK);
		break;

		// Perform any necessary cleanup
	case DLL_PROCESS_DETACH:
		// MessageBox(NULL, "detach", "kichk", MB_OK);
		break;

		// DLL_THREAD_ATTACH, DLL_THREAD_DETACH
	default:
		break;
	}

	return (TRUE);
}

/* -----------------------------------------------------------------------*
 *
 *----------------------------------------------------------------------- */

int __stdcall GetMD5(char sSaisie[50], char sMD5[200]) {
	GetMD5(sSaisie, strlen(sSaisie), sMD5);

	return 0;
}

int __stdcall DecrypteFile (char nomficOrig[400], char nomficDest[400])
{
	decrypte(nomficOrig, nomficDest);
	return 1;
}

int __stdcall EncrypteFile (char nomficOrig[400], char nomficDest[400])
{
	encrypte(nomficOrig, nomficDest);
	return 1;
}

int __stdcall GetKeyString(char sSection[50],
	char sKey[50], char sValue[100], char nomfichier[400]) {
	return ReadKeyString (sSection, sKey, sValue, nomfichier);
}
/* ----------------------------- END OF FILE ----------------------------- */
