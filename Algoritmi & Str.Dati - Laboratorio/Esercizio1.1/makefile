# programma : programma.o funzione1.o funzione2.o funzione3.o
#   gcc programma.o funzione1.o funzione2.o funzione3.o

# programma.o : header.h programma.c
#   gcc -c programma.c

# funzione1.o : funzione1.c
#   gcc -c funzione1.c

# funzione2.o : funzione2.c.
#   gcc -c funzione2.c

# funzione3.o : funzione3.c.
#   gcc -c funzione3.c 

esercizio1 : esercizio1.o funzioni.o
	gcc esercizio1.o funzioni.o -o esercizio1

esercizio1.o : funzioni.h esercizio1.c
	gcc -c esercizio1.c

funzioni.o : funzioni.c
	gcc -c funzioni.c

