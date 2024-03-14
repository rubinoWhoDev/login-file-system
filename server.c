#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "login.h"
//#define OPERATION_LENGTH 16
//#define STR_LENGTH 128
//#define REQUEST_FILE "request.txt"
//#define DATA_FILE "data.txt"
//#define RESPONCE_FILE "responce.txt"

/*
typedef struct {
	char operation[OPERATION_LENGTH];
	char name[STR_LENGTH];
	char password[STR_LENGTH];
} Package;
*/
Package readRequest(const char* filename){
	Package pkg;
	FILE* f_request = NULL;
	while (f_request == NULL) f_request = fopen(filename, "r");
	sleep(1);
	int read_arguments = fscanf(f_request, "%16s %128s %128s", pkg.operation, pkg.name, pkg.password);
	if ((read_arguments != 1 && read_arguments != 3) || (strcmp(pkg.operation, LOGIN_OPERATION) && 
			strcmp(pkg.operation, NEW_USER_OPERATION) && strcmp(pkg.operation, ABORT))){
		printf("Invalid request.\n");
		fclose(f_request);
		exit(EXIT_FAILURE);
	}
	fclose(f_request);
	remove(REQUEST_FILE);
	return pkg;
}

void login(Package rqst, const char* filename){
	FILE* f_data = fopen(filename, "r");
	FILE* f_out = fopen(RESPONSE_FILE, "w");	
	if (f_out == NULL){
		printf("Error in opening output file.\n");
		fclose(f_data);
		exit(EXIT_FAILURE);
	}
	if (f_data == NULL){
		fprintf(f_out, FAILURE);
		fclose(f_out);
		return;
	}
	
	char nameBuff[STR_LENGTH];
	char passBuff[STR_LENGTH];
	bool found = false;

	while (!feof(f_data)){
		if (fscanf(f_data, "%128s %128s\n", nameBuff, passBuff) != 2) continue;
		if (strcmp(rqst.name, nameBuff) == 0 && strcmp(rqst.password, passBuff) == 0) {
			found = true;	
			break;
		}
	}
	
	if (found) fprintf(f_out, SUCCESS);
	else fprintf(f_out, FAILURE);

	fclose(f_data);
	fclose(f_out);
}

void newAccount(Package rqst, const char* filename){
	FILE* f_data = fopen(filename, "r");
	FILE* f_out = fopen(RESPONSE_FILE, "w");
	if (f_out == NULL){
		printf("Error in opening output file.\n");
		fclose(f_data);
		exit(EXIT_FAILURE);
	}
	if (f_data != NULL){
                char nameBuff[STR_LENGTH];
		char passBuff[STR_LENGTH];
		while (!feof(f_data)){
			if (fscanf(f_data, "%128s %128s\n", nameBuff, passBuff) != 2) continue;
			if (strcmp(nameBuff, rqst.name) == 0){
				fprintf(f_out, FAILURE);
				fclose(f_out);
				fclose(f_data);
				return;
			}
		}
        }
	fclose(f_data);

	f_data = fopen(filename, "a");
	if (f_data == NULL){
		fprintf(f_out, FAILURE);
		fclose(f_out);
		return;
	}
	fprintf(f_data, "%s %s\n", rqst.name, rqst.password);
	fprintf(f_out, SUCCESS);
	fclose(f_data);
	fclose(f_out);
}

int main(){
	Package request;
	do{
		request = readRequest(REQUEST_FILE);
		if (strcmp(request.operation, LOGIN_OPERATION) == 0) login(request, DATA_FILE);
		else if (strcmp(request.operation, NEW_USER_OPERATION) == 0) newAccount(request, DATA_FILE);
	} while (strcmp(request.operation, ABORT));
	
	return EXIT_SUCCESS; 
}
