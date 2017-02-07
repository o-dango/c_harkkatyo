/*
 * CT60A0210 Käytännön ohjelmoinnin harkkatyö.
 * Päivämäärä: kevät 16
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: stackoverflow.com
 */

 typedef struct tLista *pTiedot;
 typedef struct nLista *Maara;
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>
 #include <ctype.h>
 #include "listamoduuli.h"
 #include "tiedostomoduli.h"
 #include "apufunktiot.h"


int main(void) {

    FILE* tiedosto;
    pTiedot pA;
    Maara pAlku;
    int lopetus = 1;
    int inttivalinta;

    do {
        pA = NULL;
        pAlku = NULL;

        if((tiedosto = fopen("tilapaistiedosto.txt", "w")) != NULL) {           /*tyhjennetään edellinen tilapäislokijuttu*/
            fprintf(tiedosto, "Tilapäinen lokitiedosto.\n\n");
            fflush(tiedosto);
            fclose(tiedosto);
        }

        else {
            printf("Tiedoston avaus epäonnistui!\n");                           /*jos tiedoston avaus epäonnistuu*/
            fclose(tiedosto);
            exit(1);
        }

        tiedostoLuku(&pA);                                                      /*luetaan tuotetiedot listaan*/

        inttivalinta = PaaValikko();                                            /*ajetaan päävalikko*/

            switch(inttivalinta) {

                case 1:
                PalautusValikko(&pA, &pAlku);                                   /*ajetaan palautusohjelma*/
                break;

                case 0:
                printf("Suljetaan pullonpalautusautomaatti.\n");                /*lopetus*/
                tVapautaMuisti(pA);                                            	/*vapautetaan käytetty muisti*/
                pVapautaMuisti(pAlku);
                lopetus = 0;
                break;

                default:                                                        /*virheellinen syöte*/
                printf("Väärä valinta!\n");
                tVapautaMuisti(pA);                                             /*vapautetaan käytettyä muistia*/
                break;
        }

    } while(lopetus != 0);

    return 0;

}

/*eof*/
