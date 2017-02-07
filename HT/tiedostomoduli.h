/*CT60A0210 Käytännön ohjelmoinnin harkkatyö, kevät 2016*/

typedef struct tLista *pTiedot;
typedef struct nLista *Maara;
extern void tiedostoLuku(pTiedot *pA);
extern void tulostaKuitti(pTiedot *pA, Maara *pAlku);
extern void valiLoki(pTiedot *pA, int numero);
extern void loppuLoki(float summa, int kpl);

/*eof*/
