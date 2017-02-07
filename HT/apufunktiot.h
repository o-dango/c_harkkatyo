/*CT60A0210 Käytännön ohjelmoinnin harkkatyö, kevät 2016*/

typedef struct tLista *pTiedot;
typedef struct nLista *Maara;
extern int PaaValikko(void);
extern void PalautusValikko(pTiedot *pA, Maara *pAlku);
extern int TarkistaPaa(char *valinta);
extern int TarkistaPalautus(char *valinta, int a);

/*eof*/
