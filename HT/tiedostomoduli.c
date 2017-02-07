/*
 * CT60A0210 Käytännön ohjelmoinnin harkkatyö.
 * Päivämäärä: kevät 16
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: stackoverflow.com
 */
/*tiedostomoduli: tiedostonluku, kuitin tulostus, lokitiedostojen (tilapäisloki, loppuloki) kirjoitus*/

#include "tiedostomoduli.h"
#include "apufunktiot.h"
#include "listamoduuli.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>


void tiedostoLuku(pTiedot *pA) {												/*Aliohjelma tuotetietojen lukuun*/

	FILE* tiedosto;																/*Määrittelyjä*/
	char puskuri[CHAR_MAX];
	char *pApu;
	int i;
	char *tyyppi;
	float tilavuus, pantti;

	if ((tiedosto=fopen("tuotetiedosto.txt","r")) == NULL) {					/*Avatataan tiedosto lukutilaan*/
		printf("Tiedoston avaaminen epäonnistui.\n");							/*Jos tiedoston avaaminen epäonnistuu*/
		fclose(tiedosto);
		exit(1);
	}

	while(fgets(puskuri,(sizeof(puskuri)), tiedosto) != NULL) {					/*Käydään tiedosto läpi rivi kerrallaan ja luetaan tiedot talteen*/

		i=0;
		pApu=strtok(puskuri," ");
		while(pApu) {
			if(i == 0) {
				tyyppi = pApu;
			}
			else if(i == 1) {
				tilavuus = atof(pApu);
			}
			else if(i == 2) {
				pantti = atof(pApu);
			}
			i=i+1;
			pApu=strtok(NULL, " ");
		}

		if(tVaraaMuisti(pA,tyyppi,tilavuus,pantti) == 0) {						/*Varataan muistia luetuille tiedoille ja tallennetaan tiedot listaan*/
			printf("Muistin varaus epäonnistui!\n");							/*Jos muistin varaaminen epäonnistuu*/
			//fflush(tiedosto);
			fclose(tiedosto);
			exit(0);
		}

	}
	fclose(tiedosto);															/*Suljetaan tiedosto*/
}


void tulostaKuitti(pTiedot *pA, Maara *pAlku) {									/*Aliohjelma kuitin tulostamista varten palautuksen lopuksi*/

	struct tLista *ptrr;														/*Määrittelyjä*/
	struct nLista *ptr;
	float summa = 0;
	int laskuri = 0;
	int valisumma=0;
	int i;
	int k=1;																	/*Laskuri eri tuotetyyppien läpikäymiseen*/

	ptrr = *pA;																	/*Pointterit osoittamaan listojen alkuun*/
	ptr = *pAlku;

	time_t nyt;																	/*Haetaan aika ja siihen liittyviä määrittelyjä*/
	struct tm *aika;
	time(&nyt);
	aika = localtime(&nyt);

	while(ptr != NULL) {														/*Lasketaan palautettujen pullojen määrä*/
		laskuri = laskuri+1;
		ptr=ptr->pnSeuraava;
	}

	if (aika->tm_min < 10){														/*Tulostetaan kuitin otsikkorivi*/
		printf("Kuitti %d.%d.%d %d:0%d\n", aika->tm_mday, aika->tm_mon + 1,		/*Jos minuutit välillä 0-9*/
		aika->tm_year + 1900, aika->tm_hour, aika->tm_min);
	}
	else {
		printf("Kuitti %d.%d.%d %d:%d\n", aika->tm_mday, aika->tm_mon + 1,		/*Jos minuutit välillä 10-59*/
		aika->tm_year + 1900, aika->tm_hour, aika->tm_min);
	}

	//printf("Kuitti\n");														/*Vioperivi*/
	printf("Palautetut pullot ja tölkit yhteensä %d kappaletta.\n",laskuri);	/*Tulostetaan palautettujen pullojen lukumäärä*/

	while(ptrr != NULL) {														/*Käydään kaikki tuotevaihtoehdot läpi*/
		valisumma = 0;
		ptr=*pAlku;																/*Joka kierroksella aloitetaan palautuslistan alusta*/

		for(i=0; i < laskuri; i++) {											/*Käydään kaikki palautuslistan alkiot läpi*/

			if((ptr->numero) == k) {											/*Lasketaan kunkin tuotetyypin palautusten lukumäärä*/
				valisumma = valisumma + 1;
			}
			ptr=ptr->pnSeuraava;												/*Siirrytään palautuslistan seuraavaan alkioon*/
		}

		if(valisumma > 0) {														/*Jos tuotetta on palautettu, tulostetaan tiedot*/
			printf("%s %4.2fl\tpantit %d x %4.2f = %4.2f€\n", ptrr->Ltyyppi,ptrr->Ltilavuus, valisumma, ptrr->Lpantti,
			valisumma*(ptrr->Lpantti));
		}

		summa = summa + valisumma*(ptrr->Lpantti);								/*Päivitetään palautusten kokonaissummaa*/
		k = k + 1;																/*Siirrytään seuraavaan tuotteeseen*/
		ptrr = ptrr->ptSeuraava;												/*Siirrytään tuotelistalla eteenpäin*/
	}

	printf("Pantit yhteensä %4.2f€\n",summa);									/*Tulostetaan kokonaissumma*/

	loppuLoki(summa,laskuri);													/*Tallennetaan palautustiedot lokitiedostoon*/
	tVapautaMuisti(*pA);
	pVapautaMuisti(*pAlku);
}


void valiLoki(pTiedot *pA, int numero) {										/*Aliohjelma tietojen tallentamiseen tilapäislokiin*/

	time_t nyt;																	/*Haetaan aika ja siihen liittyviä määrittelyjä*/
	struct tm *aika;
	time(&nyt);
	aika = localtime(&nyt);

	FILE* tiedosto;
	int i; 																		/*laskuri oikean tuotemuodon tulostamista varten*/
	struct tLista *ptr;

	if ((tiedosto=fopen("tilapaistiedosto.txt","a")) == NULL) {					/*Avataan tilapäisloki lisäys-tilaan*/
		printf("Tiedoston avaaminen epäonnistui.\n");							/*Jos tiedoston avaaminen epäonnistuu*/
		exit(1);
	}

	ptr=*pA;

	for(i=1; i<numero; i++) {													/*Etsitään tuotelistasta oikea kohta*/
		ptr=ptr->ptSeuraava;
	}
																				/*Kirjoitetaan tiedot tilapäislokiin*/
	if (aika->tm_min < 10){														/*Jos minuutit välillä 0-9*/
		fprintf(tiedosto, "%d.%d.%d %d:0%d:%s-%4.2fl:%4.2f€.\n", aika->tm_mday, aika->tm_mon + 1, aika->tm_year + 1900,
		aika->tm_hour, aika->tm_min, ptr->Ltyyppi, ptr->Ltilavuus, ptr->Lpantti);
	}
	else {																		/*Jos minuutit välillä 10-59*/
		fprintf(tiedosto, "%d.%d.%d %d:%d:%s-%4.2fl:%4.2f€.\n", aika->tm_mday, aika->tm_mon + 1, aika->tm_year + 1900,
		aika->tm_hour, aika->tm_min, ptr->Ltyyppi, ptr->Ltilavuus, ptr->Lpantti);
	}

	//fprintf("%s-%4.2fl:%4.2f€.\n", ptr->Ltyyppi, ptr->Ltilavuus, ptr->Lpantti);		/*vioperivi*/

	fclose(tiedosto);															/*Suljetan tiedosto*/
}


void loppuLoki(float summa, int kpl) {											/*Aliohjelma palautustietojen tallentamiseen päälokiin*/

	FILE* tiedosto;
	time_t nyt;																	/*Haetaan aika ja siihen liittyviä määrittelyjä*/
	struct tm *aika;
	time(&nyt);
	aika = localtime(&nyt);

	if ((tiedosto=fopen("lokitiedosto.txt","a")) == NULL) {						/*Avataan lokitiedosto lisäys-tilaan*/
		printf("Tiedoston avaaminen epäonnistui.\n");							/*Jos tiedoston avaaminen epäonnistuu*/
		exit(1);
	}

	if (aika->tm_min < 10){														/*Kirjoitetaan tiedot päälokitiedostoon*/
		fprintf(tiedosto, "%d.%d.%d %d:0%d - Palautukset %d kpl. Pantit %4.2f€.\n", aika->tm_mday, aika->tm_mon + 1,
		aika->tm_year + 1900, aika->tm_hour, aika->tm_min, kpl, summa);			/*jos minuutit välillä 0-9*/
	}
	else{
		fprintf(tiedosto, "%d.%d.%d %d:%d - Palautukset %d kpl. Pantit %4.2f€.\n", aika->tm_mday, aika->tm_mon + 1,
		aika->tm_year + 1900, aika->tm_hour, aika->tm_min, kpl, summa);			/*jos minuutit välillä 10-59*/
	}

	//fprintf(tiedosto, "Palautukset %d kpl. Pantit %4.2f€.\n", kpl, summa);	/*vioperivi*/

	fclose(tiedosto);
}

/*eof*/
