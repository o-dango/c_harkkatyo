/*
 * CT60A0210 Käytännön ohjelmointi -kurssin ohjelmien otsikkotiedot.
 * Päivämäärä: kevät 16
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <limits.h>
 #include <ctype.h>
 #include "listamoduuli.h"
 #include "tiedostomoduli.h"
 #include "apufunktiot.h"


 int tVaraaMuisti(pTiedot *pA, char *tyyppi, float tilavuus, float pantti) {    /*tyyppilistan teko*/

    struct tLista *ptrUusi = NULL;
    struct tLista *ptr = NULL;

    if ((ptrUusi=(struct tLista*)malloc(sizeof(struct tLista))) == NULL ) {
        return 0;                                                               /*jos muistinvaraus epäonnistuu*/
    }

    else {
        ptrUusi->Ltyyppi = malloc(strlen(tyyppi)+1);                            /*lisätään listalle tiedot*/
        strcpy(ptrUusi->Ltyyppi, tyyppi);
        ptrUusi->Ltilavuus = tilavuus;
        ptrUusi->Lpantti = pantti;
        ptrUusi->ptSeuraava = NULL;                                             /*tiedoista seuraava solmu alustetaan tyhjäksi*/

        if (*pA == NULL) {                                                      /*jos lisättävät tiedot ovat ensimmäisiä*/
            *pA = ptrUusi;
        }
        else {                                                                  /*muulloin*/
            ptr = *pA;

            while ( ptr->ptSeuraava != NULL) {
                ptr = ptr->ptSeuraava;                                          /*siirretään apupointeri listan seuraavaan solmuun*/
            }

            ptr->ptSeuraava = ptrUusi;                                          /*lisätään tiedot listalle*/
        }
        return 1;                                                               /*palauttaa ykkösen jos kaikki onnistuu*/
    }
}


int pVaraaMuisti(Maara *pAlku, int luku) {                                      /*numerolistan varaus*/

    struct nLista *ptrUusi = NULL;
    struct nLista *ptr = NULL;

    if ((ptrUusi=(struct nLista*)malloc(sizeof(struct nLista))) == NULL ) {     /*jos muistinvaraus epäonnistuu*/
        return 0;
    }

    else {
        ptrUusi->numero = luku;
        ptrUusi->pnSeuraava = NULL;

        if (*pAlku == NULL) {                                                   /*jos listan ensimmäinen alkio*/
            *pAlku = ptrUusi;                                                   /*lisätään suoraan listan ensimmäiseksi*/
        }
        else {                                                                  /*muulloin*/
            ptr = *pAlku;

            while ( ptr->pnSeuraava != NULL) {
                ptr = ptr->pnSeuraava;                                          /*siirretään apupointeri listan seuraavaan solmuun*/
            }

            ptr->pnSeuraava = ptrUusi;                                          /*lisätään tiedot listalle*/
        }
        return 1;                                                               /*palauttaa ykkösen jos kaikki onnistuu*/
    }
}


void tVapautaMuisti(pTiedot pA) {                                               /*tyyppilistan tyhjennys*/

    struct tLista *ptr = pA;

    if (ptr == NULL) {
        //lista on tyhjä
    }

    else {

        while(ptr != NULL) {
            pA = ptr->ptSeuraava;
            free(ptr->Ltyyppi);                                                 /*vapautetaan tyypin muistipaikka*/
            free(ptr);                                                          /*vapautetaan solmun muistipaikka*/
            ptr = pA;                                                           /*siirretään apupointeri takaisin alkuun*/
        }
    }
}


void pVapautaMuisti(Maara pAlku) {                                              /*numerolistan tyhjennys*/

    struct nLista *ptr = pAlku;

    if (ptr == NULL) {
        //lista on tyhjä
    }

    else {

        while(ptr != NULL) {
            pAlku = ptr->pnSeuraava;
            free(ptr);                                                          /*vapautetaan solmun muistipaikka*/
            ptr = pAlku;                                                        /*siirretään apupointeri takaisin alkuun*/
        }
    }
}

/*eof*/
