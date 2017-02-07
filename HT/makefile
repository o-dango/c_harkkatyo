harkkatyö: listamoduuli.o tiedostomoduli.o apufunktiot.o main.o
	gcc main.o listamoduuli.o tiedostomoduli.o apufunktiot.o -o harkkatyö -Wall
listamoduuli.o: listamoduuli.c listamoduuli.h
	gcc listamoduuli.c -c -Wall -std=c99
apufunktiot.o: apufunktiot.c apufunktiot.h listamoduuli.h
	gcc apufunktiot.c -c -Wall -std=c99
tiedostomoduli.o: tiedostomoduli.c tiedostomoduli.h listamoduuli.h
	gcc tiedostomoduli.c -c -Wall -std=c99
main.o: main.c tiedostomoduli.h apufunktiot.h listamoduuli.h
	gcc main.c -c -Wall -std=c99
