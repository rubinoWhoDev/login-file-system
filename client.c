#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "login.h"
//#define OPERATION_LENGTH 16
//#define STR_LENGTH 128
//#define REQUEST_FILE "request.txt"


int menu(){
	printf("- - - M E N U - - -\n\n1. Effettua login\n2. Registrati\n0. Esci\n\nScelta: ");
	int scelta;
	scanf("%d", &scelta);
	printf("\n");
	return scelta;
}

void inputData(char* name, char* password){
	printf("Inserire nome utente: ");
        scanf("%128s", name);
        printf("Inserire password: ");
        scanf("%128s", password);
}

void newRequest(const char* operation_type, bool need_data){
	Package request;
	strcpy(request.operation, operation_type);
	if (need_data) inputData(request.name, request.password);
	else {
		strcpy(request.name, "");
		strcpy(request.password, "");
	}
	FILE* f_request;
        f_request = fopen(REQUEST_FILE, "w");
        if (f_request == NULL){
                printf("Impossibile creare un file di richiesta.\n");
                exit(EXIT_FAILURE);
        }
	fprintf(f_request, "%s %s %s", request.operation, request.name, request.password);
	fclose(f_request);
}

char* readResponse(const char* filename){
	char* response = malloc(sizeof(char) * RESPONSE_LENGTH);
	FILE* f_response = NULL;
	while (f_response == NULL) f_response = fopen(filename, "r");
	sleep(1);
	fscanf(f_response, "%7s", response);
	fclose(f_response);
	remove(filename);
	return response;
}

int main(){
	int scelta;
	char* response;
	do {
		scelta = menu();
		switch (scelta){
			case 1:
				newRequest(LOGIN_OPERATION, true);
				response = readResponse(RESPONSE_FILE);
				if (strcmp(response, SUCCESS) == 0) printf("Accesso eseguito con successo.\n\n");
				else printf("Impossibile accedere.\n\n");
				break;
			case 2:
				newRequest(NEW_USER_OPERATION, true);
				response = readResponse(RESPONSE_FILE);
				if (strcmp(response, SUCCESS) == 0) printf("Registrazione avvenuta con successo.\n\n");
				else printf("Impossibile registrare il nuovo utente.\n\n");
				break;
			case 0:
				printf("Chiusura server in corso.\n\n");
				newRequest(ABORT, false);
				break;
			default:
				printf("Inserire un valore valido.\n\n");
				break;
		}
	} while (scelta != 0);

	return EXIT_SUCCESS;
}
