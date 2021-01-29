

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "functions.c"

int main(void)
{
	conceptList* list = NULL;
	char text[SIZE];
	FILE *saveFile = NULL;

	srand(time(NULL));

	saveFile = fopen("dialogue.txt", "w");
	if (saveFile == NULL)
	{
		printf("3B$ Damn! Someone removed my HDD!\n");
		return 1;
	}
	printf("Press '%s' to exit!\n", exitMessage);

	do 
	{
		printf("me$ ");
		fgets(text, sizeof(text), stdin);
		fprintf(saveFile, "me$ %s", text);

		// i fgets den adikathista ton teleftaio xaraktira me '\0'
		// diladi krataei tin allagi grammis '\n' opote prepei na to allakso
		text[strlen(text) - 1] = '\0';


		// an ta prota grammata einai "learn this > "
		if (strncmp(text, learnMessage, strlen(learnMessage)) == 0 && strchr(text,':') && text[strlen(text)-1]!=':')
			list = addSentence(list, text, "kbrd", saveFile);
		else if (strncmp(text, readMessage, strlen(readMessage)) == 0)
			list = readFile(list, text, saveFile);
		else if (strncmp(text, forgetMessage, strlen(forgetMessage)) == 0)
			list = forgetConcept(list, text, saveFile);
		else if (strcmp(text, list1Message) == 0)
			showNodes(list, saveFile);
		else if (strcmp(text, list2Message) == 0)
			showNodesMore(list, saveFile);
		else if (strcmp(text, exitMessage) == 0)
			break;
		else
      printf("3B$ I can't understand what are you talking about dude!!!!\n");

	}while (strncmp(text, exitMessage, strlen(exitMessage)) != 0);


	fclose(saveFile);

	free_mem(list);

	return 0;
}
