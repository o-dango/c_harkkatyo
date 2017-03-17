/*
 * CT60A0210 Käytännön ohjelmoinnin harkkatyö.
 * Päivämäärä: kevät 16
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: stackoverflow.com
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>
 #include <ctype.h>
 #include "listamoduuli.h"
 #include "apufunktiot.h"
 #include <time.h>
 #include "tiedostomoduli.h"

 int PaaValikko(void) {															/*päävalikko*/

 	char *valinta = NULL;
 	char merkkivalinta[CHAR_MAX];
 	int inttivalinta, virhe;

 	printf("PULLONPALAUTUSAUTOMAATTI\n");
 	printf("Automaatti on valmis ottamaan vastaan pullot ja tölkit.\n");
 	printf("1) Aloita palautus\n");
 	printf("0) Lopeta\n");
 	printf("Valitse: ");														/*Valinta, mitä tehdään*/
 	fgets(merkkivalinta, (sizeof(merkkivalinta)), stdin);
 	valinta = (char*)malloc((strlen(merkkivalinta)+1));
 	strcpy(valinta, merkkivalinta);
 	virhe = TarkistaPaa(valinta);												/*syötteen tarkistus*/

 	if (virhe == 1){															/*oikea syöte*/
 		inttivalinta = atoi(valinta);
		free(valinta);															/*vapautetaan muistia*/
 		return inttivalinta;
 	}
 	else {																		/*väärä syöte*/
		free(valinta);
 		return 2;
 	}

 }


 void PalautusValikko(pTiedot *pA, Maara *pAlku) {								/*Palautusvalikko*/
 	struct tLista *ptrr;														/*Määrittelyjä*/
 	ptrr = *pA;
 	int a, paate;
 	char *valinta = NULL;
 	char merkkivalinta[CHAR_MAX];
 	int virhe1, i;
 	int virhe2, vertailu = 0;

 	do {
 		a = 1;																	/*kuinka monta alkiota listassa on*/
 		ptrr = *pA;																/*siirretään apupointteri listan alkuun*/
 		printf("\nSyötä uusi pullo tai tölkki.\n");
 		while(ptrr != NULL) {													/*Tulostetaan kaikki mahdolliset palautettavat pullot ja tölkit*/
 			printf("%d) %s %4.2fl\n", a, ptrr->Ltyyppi, ptrr->Ltilavuus);
 			ptrr = ptrr->ptSeuraava;
 			a=a + 1;
 		}

 		printf("%d) Lopeta syöttö ja tulosta kuitti.\n", a);
 		paate = a;																/*lopetusehto*/

 		printf("--> ");
 		fgets(merkkivalinta, (sizeof(merkkivalinta)+1), stdin);					/*siirretään valinta pointteriin*/
 		valinta = (char*)malloc((strlen(merkkivalinta)+1));
 		strcpy(valinta, merkkivalinta);

 		virhe1 = TarkistaPalautus(valinta, a);									/*tarkastetaan syöte*/
 		if (virhe1 == 1) {														/*oikea syöte*/
 			vertailu = atoi(valinta);

 			if (vertailu == paate) {											/*lopetus*/
				free(valinta);													/*vapautetaan muisti*/
 				break;
 			}

 			else {
 				virhe2 = pVaraaMuisti(pAlku, vertailu);							/*lisätään palautuslistaan tuotenumero*/
 				if (virhe2 == 0) {												/*jos epäonnistuu*/
 					printf("Pullon lisäys ei onnistunut, syötä pullo uudelleen.\n");
					free(valinta);
 				}

 				else {															/*haetaan syötetyn tuotteen tiedot*/
 					ptrr = *pA;

 					for (i = 1; i<vertailu; i++) {
 						ptrr = ptrr->ptSeuraava;
 					}

 					printf("Syötetty: %s %4.2fl\n", ptrr->Ltyyppi, ptrr->Ltilavuus);
 					valiLoki(pA, vertailu);										/*tallennetaan tiedot tilapäislokiin*/
					free(valinta);

 				}
 			}
 		}

 		else {																	/*jos syöte oli väärä*/
 			printf("Väärä valinta!\n");
			free(valinta);

 		}

 	} while (vertailu != paate);

 	tulostaKuitti(pA, pAlku);

 }


 int TarkistaPaa(char *valinta) {												/*päävalikon syötteen tarkistus*/

	 int vertailu1, vertailu2;
	 int vertailu3 = 0;
	 int i = 0;

     if (strlen(valinta) > 2) {                                                 /*jos syöte on liian pitkä esim. 01*/
         return 0;
     }

	 while(valinta[i] != '\n') {												/*tarkistetaan syöte merkki kerrallaan*/
	 	vertailu1 = isalpha(valinta[i]);
	 	vertailu2 = isalnum(valinta[i]);

	 	if(vertailu1 != 0 && vertailu2 != 0) {									/*jos merkki on kirjain*/
	 		vertailu3 = 1;
	 		break;
	 	}
	 	else if (vertailu1 == 0 && vertailu2 != 0) {							/*jos merkki on numero*/
			vertailu3 = 0;
	 	}
	 	else {																	/*jos merkki on merkki*/
	 		vertailu3 = 1;
	 		break;
	 	}
	 	i++;
	 }

	 if (vertailu3 == 0) {														/*tarkastetaan numerosyötteen oikeellisuus*/
	 	if (atoi(valinta) <=1  && atoi(valinta) >= 0) {
	 		return 1;															/*jos syöte oli oikea*/
	 	}
	 	else {																	/*jos syöte oli väärä*/
	 		return 0;
	 	}
	 }
	 else {																		/*jos syöte oli väärä*/
	 	return 0;
	 }
 }


 int TarkistaPalautus(char *valinta, int a) {									/*tarkistetaan palautusvalikon syöte*/

 	int vertailu1, vertailu2;
	int vertailu3 = 0;
 	int i = 0;

    if (valinta[0] == '0') {
        return 0;
    }

 	while (valinta[i] != '\n') {												/*tarkistetaan syöte merkki kerrallaan*/
 		vertailu1 = isalpha(valinta[i]);
 		vertailu2 = isalnum(valinta[i]);

		if (vertailu1 != 0 && vertailu2 != 0) {									/*jos merkki on kirjain*/
			vertailu3 = 1;
			break;
		}
		else if (vertailu1 == 0 && vertailu2 != 0) {							/*jos merkki on numero*/
			vertailu3 = 0;
		}
		else {																	/*jos merkki on merkki*/
			vertailu3 = 1;
			break;
		}
		i++;
	}

	if (vertailu3 == 0) {														/*tarkistetaan syötteen oikeellisuus*/
		if (atoi(valinta) <= a && atoi(valinta) > 0) {							/*jos syöte oli oikea*/
			return 1;
		}
		else {																	/*jos syöte oli väärä*/
			return 0;
		}
	}
	else {																		/*jos syöte oli väärä*/
		return 0;
	}
}

void haeAika(char *pAika) {

    time_t nyt;																	/*Haetaan aika*/
    struct tm *aika;
    time(&nyt);
    aika = localtime(&nyt);

    strftime(pAika, 20, "%d.%m.%Y %H:%M", aika);                                /*Muodostetaan aikaleima*/
}


int TarkistaTiedosto(char *pApu) {												/*tiedoston tarkistus*/

    int vertailu1, vertailu2;
    int vertailu3 = 0;
    int i = 0;

    while(pApu[i] != '\n') {												    /*tarkistetaan syöte merkki kerrallaan*/
       vertailu1 = isalpha(pApu[i]);
       vertailu2 = isalnum(pApu[i]);

       if(vertailu1 != 0 && vertailu2 != 0) {									/*jos merkki on kirjain*/
           if (vertailu3 == 0) {
               vertailu3 = 0;
               break;
           }
       }

       else if (vertailu1 == 0 && vertailu2 != 0) {							    /*jos merkki on numero*/
           vertailu3 = 1;
       }

       else if(pApu[i] == '\0') {
           break;
       }

       else {																	/*jos merkki on merkki*/
           vertailu3 = 2;
       }
       i++;
    }


    if (vertailu3 == 0) {                                                       /*palauttaa nollan jos kirjaimia*/
       return 0;
    }

    else if(vertailu3 == 1) {                                                   /*palauttaa ykkösen jos numeroita*/
        return 1;
    }

    else {                                                                      /*muussa tapauksessa*/
        return 2;
    }
}

/*eof*/
