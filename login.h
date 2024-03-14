#ifndef LOGIN_H
#define LOGIN_H
#define OPERATION_LENGTH 16
#define STR_LENGTH 128
#define REQUEST_FILE "request.txt"
#define DATA_FILE "data.txt"
#define RESPONSE_FILE "response.txt"
#define LOGIN_OPERATION "login"
#define NEW_USER_OPERATION "register"
#define SUCCESS "success"
#define FAILURE "failure"
#define RESPONSE_LENGTH 7
#define ABORT "abort"

typedef struct {
	char operation[OPERATION_LENGTH];
	char name[STR_LENGTH];
	char password[STR_LENGTH];
} Package;

#endif
