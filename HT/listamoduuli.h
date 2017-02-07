/*CT60A0210 Käytännön ohjelmoinnin harkkatyö, kevät 2016*/

 #ifndef LISTAMODUULI
 #define LISTAMODUULI
 typedef struct tLista *pTiedot;
 typedef struct nLista *Maara;
 struct tLista {                                                                /*määritellään tarvittavat listat*/
     char* Ltyyppi;
     float Ltilavuus;
     float Lpantti;
     struct tLista *ptSeuraava;
 };

 typedef struct tLista *pTiedot;

 struct nLista {
     int numero;
     struct nLista *pnSeuraava;
 };

 typedef struct nLista *Maara;


extern int tVaraaMuisti(pTiedot *pA, char *tyyppi, float tilavuus, float pantti);
extern int pVaraaMuisti(Maara *pAlku, int luku);
extern void tVapautaMuisti(pTiedot pA);
extern void pVapautaMuisti(Maara pAlku);
#endif

/*eof*/
