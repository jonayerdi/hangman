#include "hangman.h"

int main(int argc, char *argv[])
{
	hangman_config_t config;
	int error;
	if (error = readConfig(argc > 1 ? argv[1] : DEFAULT_CONFIG_FILENAME, &config))
		return printError(error);
	return mainLoop(&config);
}

int printError(int error)
{
	if(error > 0 && error <= ERRORS_COUNT)
		printf("%s", errorMessages[error - 1]);
	return error;
}

int readConfig(const char *filename, hangman_config_t *config)
{
	FILE *file;
	size_t read;
	unsigned char configText[CONFIG_INPUT_BUFFER_SIZE];
	char *numberText, *numberTextEnd, *numberTextEndAlt;
	file = fopen(filename, "rb");
	if(!file || ferror(file))
		return 1;
	read = fread(configText, 1, CONFIG_INPUT_BUFFER_SIZE - 1, file);
	fclose(file);
	configText[read] = '\0';
	numberText = strstr(configText, "\n");
	if(!numberText)
		return 2;
	if(numberText == configText)
		return 3;
	if(*(numberText - 1) == '\r')
		*(numberText - 1) = '\0';//depends on \r\n or \n newlines
	*(numberText++) = '\0';
	numberTextEnd = strstr(numberText, "\r");
	numberTextEndAlt = strstr(numberText, "\n");
	numberTextEnd = numberTextEnd < numberTextEndAlt ? numberTextEnd : numberTextEndAlt; //depends on \r\n or \n newlines
	*numberTextEnd = '\0';
	config->retries = (unsigned int) strtol(numberText, NULL, 10);
	if(config->retries < 1)
		return 4;
	strncpy (config->word, configText, SECRET_WORD_SIZE);
	return 0;
}

int mainLoop(const hangman_config_t *config)
{
	unsigned int retries = config->retries;
	unsigned char guessedChar, found;
	unsigned char guessedWord[SECRET_WORD_SIZE + 1];
	size_t guessedWordLength = strlen(config->word);
	memset(guessedWord, '_', guessedWordLength);
	guessedWord[guessedWordLength] = '\0';
	while(retries)
	{
		if(!strcmp(guessedWord, config->word))
			break;
		printf("\n%s (%d letters)\n", guessedWord, guessedWordLength);
		printf("%d retries left\n", retries);
		printf("Guess a character >> ");
		guessedChar = getchar();
		if(guessedChar != '\n')
			while((getchar()) != '\n'); //empty stdin
		found = 0;
		for(size_t i = 0 ; i < guessedWordLength ; i++)
		{
			if(config->word[i] == guessedChar)
			{
				guessedWord[i] = guessedChar;
				found = 1;
			}
		}
		if(!found)
			retries--;
	}
	if(retries)
		printf("\nYou win :)\n");
	else
		printf("\nYou lose :(\n");
	return 0;
}

