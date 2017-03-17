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
#include <ctype.h>


void tiedostoLuku(pTiedot *pA) {												/*Aliohjelma tuotetietojen lukuun*/

	FILE* tiedosto;																/*Määrittelyjä*/
	char puskuri[CHAR_MAX];
	char *pApu;
	int i, j = 0;
	int tarkistus = 0;
	char *tyyppi;
	float tilavuus, pantti;

	if ((tiedosto = fopen("tuotetiedosto.txt","r")) == NULL) {					/*Avatataan tiedosto lukutilaan*/
		perror("Tiedoston avaaminen epäonnistui");								/*Jos tiedoston avaaminen epäonnistuu*/
		exit(1);
	}

	printf("\n");
	while(fgets(puskuri,(sizeof(puskuri)), tiedosto) != NULL) {					/*Käydään tiedosto läpi rivi kerrallaan ja luetaan tiedot talteen*/

		i = 0;
		j = j + 1;
		tarkistus = 0;
		pApu = strtok(puskuri," ");
		while(pApu) {
			if (i == 0) {
				if (TarkistaTiedosto(pApu) == 0) {								/*Tarkistetaan onko tiedot oikeaa tyyppiä*/
					tyyppi = pApu;
				}
				else {
					tarkistus = 1;
				}
			}

			else if (i == 1) {
				if (TarkistaTiedosto(pApu) == 1) {								/*Tarkistetaan onko tiedot oikeaa tyyppiä*/
					tilavuus = atof(pApu);
				}
				else {
					tarkistus = 1;
				}
			}

			else if (i == 2) {
				if (TarkistaTiedosto(pApu) == 1) {								/*Tarkistetaan onko tiedot oikeaa tyyppiä*/
					pantti = atof(pApu);
				}
				else {
					tarkistus = 1;
				}
			}

			i=i + 1;
			pApu=strtok(NULL, " ");												/*Erotellaan rivillä olevat tiedot toisistaan*/
		}

		if (tarkistus == 0) {
			if(tVaraaMuisti(pA,tyyppi,tilavuus,pantti) == 0) {					/*Varataan muistia luetuille tiedoille ja tallennetaan tiedot listaan*/
				perror("Muistin varaus epäonnistui");							/*Jos muistin varaaminen epäonnistuu*/
				fclose(tiedosto);
				exit(1);
			}
		}

		else {
			printf("Virhe tuotetiedostossa rivillä %d.\n", j);					/*Ilmoitetaan, jos on virheellisiä rivejä*/
		}

	}

	if (j == 0) {																/*Jos tiedosto oli tyhjä*/
		perror("Suljetaan pullonpalautusautomaatti");
		printf("Tuotetiedosto on tyhjä!\n");
		fclose(tiedosto);
		exit(1);
	}
	fclose(tiedosto);															/*Suljetaan tiedosto*/
}


void tulostaKuitti(pTiedot *pA, Maara *pAlku) {									/*Aliohjelma kuitin tulostamista varten palautuksen lopuksi*/

	struct tLista *ptrr;														/*Määrittelyjä*/
	struct nLista *ptr;
	float summa = 0;
	int laskuri = 0;
	int valisumma = 0;
	int i, k = 1;																/*Laskuri eri tuotetyyppien läpikäymiseen*/
	char aikaleima[20];

	ptrr = *pA;																	/*Pointterit osoittamaan listojen alkuun*/
	ptr = *pAlku;

	while(ptr != NULL) {														/*Lasketaan palautettujen pullojen määrä*/
		laskuri = laskuri+1;
		ptr=ptr->pnSeuraava;
	}

	haeAika(aikaleima);
	printf("\nKuitti %s\n", aikaleima);
	printf("Palautetut pullot ja tölkit yhteensä %d kappaletta.\n",laskuri);	/*Tulostetaan palautettujen pullojen lukumäärä*/

	while(ptrr != NULL) {														/*Käydään kaikki tuotevaihtoehdot läpi*/
		valisumma = 0;
		ptr = *pAlku;															/*Joka kierroksella aloitetaan palautuslistan alusta*/

		for(i = 0; i < laskuri; i++) {											/*Käydään kaikki palautuslistan alkiot läpi*/

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

	FILE* tiedosto;
	int i; 																		/*Laskuri oikean tuotemuodon tulostamista varten*/
	struct tLista *ptr;
	char aikaleima[20];

	if ((tiedosto=fopen("tilapaistiedosto.txt","a")) == NULL) {					/*Avataan tilapäisloki lisäys-tilaan*/
		perror("Tiedoston avaaminen epäonnistui");								/*Jos tiedoston avaaminen epäonnistuu*/
		exit(1);
	}

	ptr = *pA;

	for(i = 1; i<numero; i++) {													/*Etsitään tuotelistasta oikea kohta*/
		ptr = ptr->ptSeuraava;
	}

	haeAika(aikaleima);/*Kirjoitetaan tiedot tilapäislokiin*/
	fprintf(tiedosto, "%s:%s-%4.2fl:%4.2f€.\n",aikaleima, ptr->Ltyyppi, ptr->Ltilavuus, ptr->Lpantti);
	fclose(tiedosto);															/*Suljetan tiedosto*/
}


void loppuLoki(float summa, int kpl) {											/*Aliohjelma palautustietojen tallentamiseen päälokiin*/

	FILE* tiedosto;
	char aikaleima[20];

	if ((tiedosto = fopen("lokitiedosto.txt","a")) == NULL) {					/*Avataan lokitiedosto lisäys-tilaan*/
		perror("Tiedoston avaaminen epäonnistui");								/*Jos tiedoston avaaminen epäonnistuu*/
		exit(1);
	}

	haeAika(aikaleima);
	fprintf(tiedosto, "%s - Palautukset %d kpl. Pantit %4.2f€.\n", aikaleima, kpl, summa);
	fclose(tiedosto);
}

/*eof*/
