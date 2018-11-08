//---------------------------------------------------------------------------
//#pragma hdrstop
#include "UCryptage.h"
//---------------------------------------------------------------------------
FILE * ptfic = NULL;

char lefic [400];
char leficlu [97100][1000];
unsigned int  leficnbr;   //nombre de ligne du fichier
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

int lire (char nomfic[400])
{
	leficnbr = -1;
	strcpy(lefic, nomfic);
	if ((ptfic = fopen (lefic, "r")) != NULL)
	{
		leficnbr = 0;

		while (fgets (leficlu[leficnbr], 1001, ptfic) != NULL)
		   leficnbr = leficnbr + 1;

		fclose(ptfic);
	}
	return leficnbr;
}
//---------------------------------------------------------------------------

void ecrire (char nomfic[400])
{
	strcpy(lefic, nomfic);
	unsigned int nbr;
	if ((ptfic = fopen (lefic, "w"))!=NULL)  fclose(ptfic);
	if ((ptfic = fopen (lefic, "a")) != NULL)
	{
		for (nbr = 0; nbr < leficnbr; nbr++)
		   fprintf (ptfic, leficlu[nbr]);

		fclose(ptfic);
	}
}
//---------------------------------------------------------------------------

void decrypte_crypte (char lachaine[1000], char j)
{
	unsigned int i = 0;
	unsigned char resultat, sav, ChgCode;
	unsigned int nbr, b1, b2;

	b1=32;
	b2=127;

	if (j == 'd' || j == 'D')
	{
		b1 = 112;
		b2 = 207;
	}

	while (lachaine[i])
	{
		resultat = lachaine[i]; //le caractere [i]
		nbr = resultat;         // sa valeur ASCII

		if (nbr > 32 && nbr < 113 && b1 == 112)
			resultat = nbr + 132;

		if(nbr > b1 && nbr < b2)
		{
			if (b1 == 112)
			   resultat = resultat-80;

			sav = resultat;

			ChgCode = sav & 0xF0;
			ChgCode = ChgCode | ((sav & 0x01) << 3);
			ChgCode = ChgCode | ((sav & 0x02) << 1);
			ChgCode = ChgCode | ((sav & 0x04) >> 1);
			ChgCode = ChgCode | ((sav & 0x08) >> 3);

			resultat = ChgCode;

			if (b1 == 32)
			   resultat = ChgCode + 80;
		}

		if (b1 == 112)
		{
			if (nbr > 206 && nbr < 213)
			   resultat = nbr + 38;

			if (nbr > 212 && nbr < 251)
			   resultat = nbr - 86;
		}
		else
		{
			if (nbr > 126 && nbr <165)
			   resultat = nbr + 86;

			if (nbr > 164 && nbr < 245)
			   resultat = nbr - 132;

			if (nbr > 244 && nbr < 251)
			   resultat = nbr- 38;
		}

		if (nbr == 253)
			resultat = 32;

		if (nbr == 32)
			resultat = 253;

		 // reponse pour ce caractere
		lachaine[i++] = resultat;
	}
}
//---------------------------------------------------------------------------

void encrypte (char nomficOrig[400], char nomficDest[400])
{
	lire (nomficOrig);

	for (int nbr = 0; nbr < leficnbr; nbr++)
		 decrypte_crypte (leficlu[nbr], 'c');

	ecrire (nomficDest);

}
//---------------------------------------------------------------------------

void decrypte (char nomficOrig[400], char nomficDest[400])
{
	lire (nomficOrig);

	for (int nbr = 0; nbr < leficnbr; nbr++)
		 decrypte_crypte (leficlu[nbr], 'd');

	ecrire (nomficDest);

}
//---------------------------------------------------------------------------

int ReadKeyString (char sSection[50], char sKey[50], char sValue[1000], char nomfichier[400])
{
	lire (nomfichier);
	for (int nbr = 0; nbr < leficnbr; nbr++)
		 decrypte_crypte (leficlu[nbr], 'd');

	int iRet = 0;
	int iSectionOk = 0;
	for (int nbr = 0; nbr < leficnbr; nbr++)
	{
		if (iSectionOk < 2)
		{
			char cLigne[1000];
			strcpy(cLigne, leficlu[nbr]);

			//ADU RTrim ??
			if ((cLigne[0] != ';') && (strlen(cLigne) > 0))//Si on est pas sur un commentaire...
			{
				if (cLigne[0] == '[')
				{
					char cSection[51];
					cSection[0] = '\0';
					for (int i = 0; i < 50; i++)
					{
						if (i+1 < strlen(cLigne))
						{
							if (cLigne[i+1] != ']')
							{
								cSection[i] = cLigne[i+1];
								cSection[i+1] = '\0';

							}
							else
							{
								if ((iSectionOk == 0) && (strcmp(cSection, sSection) == 0))
								{
									iSectionOk = 1;
								}
								else if (iSectionOk == 1)
								{
									iSectionOk = 2; //fin de la section cherchée, on passe à la suivante dans le fichier ini
								}

								i = 50;
							}
						}
					}
				}
				else if (iSectionOk == 1)
				{
					char cKey[51];
					cKey[0] = '\0';
					char cValue[1001];
					cValue[0] = '\0';
					int iEqual = -1;
					for (int i = 0; i < 50; i++)
					{
						if (i < strlen(cLigne))
						{
							if (cLigne[i] != '=')
							{
								cKey[i] = cLigne[i];
								cKey[i+1] = '\0';
							}
							else
							{
								iEqual = i;
								i = 50;
							}
						}
					}
					if ((iEqual >= 0) && (strcmp(cKey, sKey) == 0))
					{
						int j = 0;
						for (int i = iEqual+1; i < strlen(cLigne); i++)
						{
							if (j < 1000)
							{
								cValue[j] = cLigne[i];
								cValue[j+1] = '\0';
								j++;
							}
						}
						strcpy(sValue, cValue);
                        iRet = 1;
					}
				}
			}
		}
	}

	return iRet;
}
