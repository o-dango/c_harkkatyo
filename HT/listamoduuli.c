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

struct tLista;
struct nLista;
typedef struct tLista *pTiedot;
typedef struct nLista *Maara;


 int tVaraaMuisti(pTiedot *pA, char *tyyppi, float tilavuus, float pantti) {    /*tyyppilistan teko*/

    struct tLista *ptrUusi = NULL;
    struct tLista *ptr = NULL;

    if ((ptrUusi=(struct tLista*)malloc(sizeof(struct tLista))) == NULL ) {
        return 0;                                                               /*jos muistinvaraus epäonnistuu*/
    }

    else {
        ptrUusi->Ltyyppi = malloc(strlen(tyyppi)+1);                            /*lisätään listalle asiat*/
        strcpy(ptrUusi->Ltyyppi, tyyppi);
        ptrUusi->Ltilavuus = tilavuus;
        ptrUusi->Lpantti = pantti;
        ptrUusi->ptSeuraava = NULL;

        if (*pA == NULL) {                                                      /*jos lisättävät jutut on ensimmäisiä*/
            *pA = ptrUusi;
        }
        else {
            ptr = *pA;

            while ( ptr->ptSeuraava != NULL) {                                  /*muulloin*/
                ptr = ptr->ptSeuraava;
            }

            ptr->ptSeuraava = ptrUusi;
        }
        return 1;
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
            *pAlku = ptrUusi;
        }
        else {                                                                  /*muulloin*/
            ptr = *pAlku;

            while ( ptr->pnSeuraava != NULL) {
                ptr = ptr->pnSeuraava;
            }

            ptr->pnSeuraava = ptrUusi;
        }
        return 1;
    }
}


void tVapautaMuisti(pTiedot pA) {                                               /*tyyppilistan tyhjennys*/

    struct tLista *ptr = pA;

    if (ptr == NULL) {                                                          /*jos lista on tyhjä*/

    }

    else {

        while(ptr != NULL) {
            pA = ptr->ptSeuraava;
            free(ptr->Ltyyppi);
            free(ptr);
            ptr = pA;
        }
    }
}


void pVapautaMuisti(Maara pAlku) {                                              /*numerolistan tyhjennys*/

    struct nLista *ptr = pAlku;                                                 /*jos lista on tyhjä*/

    if (ptr == NULL) {

    }

    else {

        while(ptr != NULL) {
            pAlku = ptr->pnSeuraava;
            free(ptr);
            ptr = pAlku;
        }
    }
}

/*eof*/
