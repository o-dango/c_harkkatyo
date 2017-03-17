/*CT60A0210 Käytännön ohjelmoinnin harkkatyö, kevät 2016*/

 #ifndef LISTAMODUULI
 #define LISTAMODUULI
 struct tLista {                                                                /*määritellään tarvittavat listat*/
     char* Ltyyppi;
     float Ltilavuus;
     float Lpantti;
     struct tLista *ptSeuraava;
 };

 typedef struct tLista *pTiedot;                                                /*lista tuotetiedoille*/

 struct nLista {
     int numero;
     struct nLista *pnSeuraava;
 };

 typedef struct nLista *Maara;                                                  /*lista palautuksille*/


int tVaraaMuisti(pTiedot *pA, char *tyyppi, float tilavuus, float pantti);
int pVaraaMuisti(Maara *pAlku, int luku);
void tVapautaMuisti(pTiedot pA);
void pVapautaMuisti(Maara pAlku);
#endif

/*eof*/
