/* Led-Ansteuerung in C mit Threads */
/* Kompilieren mit:
 * gcc Led-Ansteuerung.c -o Led-Ansteuerung -Wall -lpthread -lwiringPi
 * (Linken mit pthread Libary)
 * Version: 3.6 (11.06.2019)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <wiringPi.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1000
#define PORT 4000

#define Pin_Led1 25		//1
#define Pin_Led2 24		//4
#define Pin_Led3 23		//5
#define Pin_Led4 18		//6


// Warteschlangenlaenge fuer ankommende Verbindungen
#define QUEUE 3

// *** Mirror-Funktion (Prototyp für pthread_create) ***
// arg: Pointer auf rec_socket
void *mirror(void* arg)
{
	wiringPiSetupGpio();
	pinMode(Pin_Led1, OUTPUT);
	pinMode(Pin_Led2, OUTPUT);
	pinMode(Pin_Led3, OUTPUT);
	pinMode(Pin_Led4, OUTPUT);
	
	/*

	// Test ob die LEDs ansteuerbar sind
	// Sollte abgeschalten werden, wenn sich mehrere Clients verbinden

	digitalWrite(Pin_Led1, HIGH);
	digitalWrite(Pin_Led2, HIGH);
	digitalWrite(Pin_Led3, HIGH);
	digitalWrite(Pin_Led4, HIGH);
	for (volatile long j = 0; j < 1000000; j++) // tue nichts
			;
	digitalWrite(Pin_Led1, LOW);
	digitalWrite(Pin_Led2, LOW);
	digitalWrite(Pin_Led3, LOW);
	digitalWrite(Pin_Led4, LOW);
	
	*/
	
	int clientfd = *(int *)arg; // typecast
	int Zahl;
	char inbuffer[BUFSIZE];

	// Begrüßung mit Befehlsbeschreibung
	write(clientfd, "Hallo - LEDs vom Raspberry(winkler.local) steuern\n\n", 53);
	write(clientfd, "Befehle: \n", 11);
	write(clientfd, "\tSteuerung mit Dezimalzahl (0...15)\n", 39);
	write(clientfd, "\tBeenden: q\n\n", 14);
	
	while(TRUE) {
	
		// Lesen der Zeichen aus dem Clientsocket (Empfangssocket) in den inbuffer
		// count: Anzahl der gelesenen Bytes
		int count = read(clientfd, inbuffer, sizeof(inbuffer));
		
		// Wandelt den String in Integer um
		Zahl = atoi (inbuffer);
		
		// Abhängig welche Zahl ich geschrieben habe, lechten andere
		// Leds auf oder ich beende die Verbindung
		
		if (Zahl == 0)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Keine Led ist jetzt an \n\n", 25);
		}
		if (Zahl == 1)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Led1 ist jetzt an \n\n", 22);
		}
		if (Zahl == 2)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Led2 ist jetzt an \n\n", 22);
		}
		if (Zahl == 3)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Led1 und LED2 sind jetzt an \n\n", 32);
		}
		if (Zahl == 4)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Led3 ist jetzt an \n\n", 22);
		}
		if (Zahl == 5)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Led1 und LED43 sind jetzt an \n\n", 32);
		}
		if (Zahl == 6)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Led2 und LED3 sind jetzt an \n\n", 32);
		}
		if (Zahl == 7)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Led1, LED2 und LED3 sind jetzt an \n\n", 39);
		}
		if (Zahl == 8)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "Led4 ist jetzt an \n\n", 22);
		}
		if (Zahl == 9)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "Led1 und LED4 sind jetzt an \n\n", 32);
		}
		if (Zahl == 10)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "Led2 und LED4 sind jetzt an \n\n", 32);
		}
		if (Zahl == 11)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "Led1, LED2 und LED4 sind jetzt an \n\n", 39);
		}
		if (Zahl == 12)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "Led3 und LED4 sind jetzt an \n\n", 32);
		}
		if (Zahl == 13)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "Led1, LED3 und LED4 sind jetzt an \n\n", 39);
		}
		if (Zahl == 14)
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "Led2, LED3 und LED4 sind jetzt an \n\n", 39);
		}
		if (Zahl == 15)
		{
			digitalWrite(Pin_Led1, HIGH);
			digitalWrite(Pin_Led2, HIGH);
			digitalWrite(Pin_Led3, HIGH);
			digitalWrite(Pin_Led4, HIGH);
			write(clientfd, "LED1, Led2, LED3 und LED4 sind jetzt an \n\n", 45);
		}
		if (*inbuffer == 'q')
		{
			digitalWrite(Pin_Led1, LOW);
			digitalWrite(Pin_Led2, LOW);
			digitalWrite(Pin_Led3, LOW);
			digitalWrite(Pin_Led4, LOW);
			write(clientfd, "Verbindung wurde getrennt! \n\n", 31);
			
			// Verbindung zum Client getrennt
			// Wichtig, weil sonst die Verbindung erhalten bleiben und sie keiner mehr braucht.
			close(clientfd);
		}
		if (Zahl > 15)
		{
			write(clientfd, "Schreiben Sie eine Zahl kleiner als 16 \n\n", 43);
		}		
		if (Zahl < 0)
		{
		write(clientfd, "Schreiben Sie eine Zahl beginnnend mit 0 \n\n", 45);
		}
	}
}

// *** MAIN ****
// Wenn zwei Clients auf einem Raspberry sind, einen eigenen (andern) Port angeben
int main()
{

	int server_socket, rec_socket;
	unsigned int len;
	struct sockaddr_in serverinfo, clientinfo;
	
	// Serversocket konfigurieren: 
	server_socket = socket(AF_INET, SOCK_STREAM, 0); // TCP
	serverinfo.sin_family = AF_INET; //IPv4
	
	// Man hoert auf allen Interfaces: 0.0.0.0 beziehungsweise ::::
	serverinfo.sin_addr.s_addr = htonl(INADDR_ANY);
	serverinfo.sin_port = htons(PORT);

	// Verbinde Socket mit IP-Addrese und Port
	if (bind(server_socket, (struct sockaddr *)&serverinfo, sizeof(serverinfo)) != 0) {
			printf("Fehler Socket\n");
			return 1; // Rueckgabe Fehlercode, eigentlich sollte ein Fehlercode stehen
	}
	
	// Server wartet auf connect vom Client
	listen(server_socket, QUEUE); 
	
	//Endlosschleife Server zur Abarbeitung der Client-Anfragen
	while(1) {
		printf("Server wartet...\n");
		
		// Verbindung vom Client eingetroffen
		rec_socket = accept(server_socket, (struct sockaddr *)&clientinfo, &len);
		printf("Verbindung vom %s:%d\n", inet_ntoa(clientinfo.sin_addr), ntohs(clientinfo.sin_port));
		
		pthread_t child; // Thread-Stuktur
		// Thread mit Funktion mirror(rec_socket)
		if (pthread_create(&child, NULL, mirror, &rec_socket) != 0) {
			perror("child error"); // Fehlerfall: Abbruch
			return 1;
		}
		
		else { // Kind erzeugt:
			printf("Abgekoppelt!\n");
			pthread_detach(child); // abkoppeln vom Hauptprozess
		}
	}
	return 0;
}
