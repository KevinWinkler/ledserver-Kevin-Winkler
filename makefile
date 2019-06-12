prog: Led-Ansteuerung.o
	gcc -o prog Led-Ansteuerung.o -lpthread -lwiringPi
	
Led-Ansteuerung.o: Led-Ansteuerung.c
	gcc -c Led-Ansteuerung.c
