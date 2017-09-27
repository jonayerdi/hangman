#pragma once

#include <stdio.h>	//fopen, fread, printf, getchar, fflush
#include <stdlib.h>	//strtol
#include <string.h>	//strstr, strncpy, strlen, memset

#define ERROR_CONFIG_FOPEN 1
#define ERROR_CONFIG_NO_REPETITIONS 2
#define ERROR_CONFIG_NO_WORD 3
#define ERROR_CONFIG_WRONG_RETRIES 4

#define ERRORS_COUNT 4

const char *errorMessages[] = { "Configuration file not found (pass via args)", "Configuration format error"
								, "Configuration format error", "Configuration format error" };

#define DEFAULT_CONFIG_FILENAME "hangman.ini"
#define SECRET_WORD_SIZE 20

typedef struct hangman_config
{
	unsigned char word[SECRET_WORD_SIZE + 1];
	unsigned int retries;
} hangman_config_t;

#define CONFIG_INPUT_BUFFER_SIZE (SECRET_WORD_SIZE + 2 + 7 + 1) /* secret word + newline + 7 digit number + \0 */

int printError(int error);
int readConfig(const char *filename, hangman_config_t *config);
int mainLoop(const hangman_config_t *config);
