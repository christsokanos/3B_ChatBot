
#include "functions.h"

conceptList* delete_node(conceptList* list, conceptList* node)
{
	conceptList* previous_node = list;
	conceptList* next_node = node->next;

	// an iparxei 1 monos komvos, to head, to diagrafo kai ligei i lista
	if (node == node->next)
	{
		free(node);
		return NULL;
	}

	// psaxno ton komvo prin apo afton pou tha sviso
	while (previous_node->next != node) previous_node = previous_node->next;

	previous_node->next = next_node; // o proigoumenos deixnei ston epomeno

	if (list == node) list = next_node; // an tha sviso tin kefali, kefali o epomenos

	free(node);

	return list;
}
conceptList* forgetConcept(conceptList* list, char* text, FILE *f)
{

	char *concept = NULL;
	char *token1 = NULL;
	char *token2 = NULL;
	conceptList* node = list;
	int i, node_deleted = 0;

	if (list == NULL)
	{
		printf("3B$ my concept list is empty!\n");
		fprintf(f, "3B$ my concept list is empty!\n");
		return list;
	}


	token1 = strtok(text, ">");
	token2 = strtok(NULL, ",");

	while (token2 != NULL)
	{
		while (*token2 == ' ') 
			token2++;

		for (i = 0 ; i < strlen(token2) ; i++) 
			token2[i] = tolower(token2[i]);

		do 
		{
			// kano adigrafo tou concept, gia na ta kano ola peza kai na meinei
			// os exei ston komvo
			concept = strdup(node->concept);
			for (i = 0 ; i < strlen(concept) ; i++)
			 concept[i] = tolower(concept[i]);

			// an to token2 iparxei os kommati sto concept, svino ton komvo
			if (strstr(concept, token2) != NULL)
			{
				showRandomMessage(conceptDeletedMessage, node->concept, f);
				list = delete_node(list, node);

				if (list == NULL)
				{
					printf("3B$ all concepts deleted, so I stop!\n");
					fprintf(f, "3B$ all concepts deleted, so I stop!\n");
					return NULL;
				}
				node_deleted++;
				break; // an sviso 1 komvo den sinexizo gia na vro kai allon pou tairiazei
			}

			node = node->next;
		}while (node != list);

		if (node_deleted == 0)
			showRandomMessage(conceptNotDeletedMessage, token2, f);
		token2 = strtok(NULL, ","); // pairno to epomeno pou edoseo xristis
		node = list;
		node_deleted = 0;
	}
	
	return list;
}
void free_mem(conceptList* list)
{
 conceptList* node = list;

 if (list == NULL)
  return;

 node->next = NULL;
 list = list->next; // kano ti lista grammiki

 while (list != NULL) 
 {
  node = list;
  list = list->next;
  free(node);
 }
 
}
void showNodesMore(conceptList* list, FILE* f)
{
	conceptList* node = list;

	if (node == NULL)
	{
		printf("3B$ I know nothing\n");
		fprintf(f, "3B$ I know nothing\n");
		return;
	}

	do
	{
		printf("3B$ I talk about: %s (%d times)\n", node->concept, node->timesUsed);
		fprintf(f, "3B$ I talk about: %s (%d times)\n", node->concept, node->timesUsed);
		node = node->next;
	}while (node != list);
}
void showNodes(conceptList* list, FILE* f)
{
	conceptList* node = list;

	if (node == NULL)
	{
		printf("3B$ I know nothing\n");
		fprintf(f, "3B$ I know nothing\n");
		return;
	}

	do
	{
		printf("3B$ I know about: %s\n", node->concept);
		fprintf(f, "3B$ I know about: %s\n", node->concept);
		node = node->next;
	}while (node != list);
}

int concept_exists(char *concept, conceptList* list)
{
	conceptList* node = list;

	if (node == NULL) 
		return 0; // an den iparxei lista den iparxei kai to concept

	// sarono oli ti lista
	do
	{
		if (strcmp(concept, node->concept) == 0) 
			return 1;
		node = node->next;
	}while (node != list);

	return 0;
}
void showRandomMessage(const char *msg[5], char *concept, FILE *f)
{
	int i = rand() % MESSAGES;
	printf(msg[i], concept);
	fprintf(f, msg[i], concept);
}
conceptList* make_new(char* concept, char* sentence, char learnedFrom[5], FILE *f)
{
	conceptList* neos_komvos = (conceptList*)malloc(sizeof(conceptList));
	if (neos_komvos == NULL)
	{
		printf("3B$ Your PC sucks! There is no RAM available!\n");
		fprintf(f, "3B$ Your PC sucks! There is no RAM available!\n");
		exit(1);
	}

	// exo strdup, giati o deiktis neos_komvos->concept den exei mnimi
	neos_komvos->concept = strdup(concept);
	neos_komvos->sentence = strdup(sentence);
	neos_komvos->timesUsed = 0;

	// exo strcpy, giati o pinakas neos_komvos->learnedFrom exei idi mnimi
	strcpy(neos_komvos->learnedFrom, learnedFrom);
	neos_komvos->next = neos_komvos;

	return neos_komvos;
}

conceptList* addNode(conceptList* list, conceptList* newNode)
{
	conceptList* node = list;

	if (node == NULL) 
		return newNode; // an den  iparxxei lista, o neos komvos einai kefali

	// anazito ton teleftaio komvo
	while (node->next != list) 
		node = node->next;

	node->next = newNode;
	newNode->next = list;

	return list;
}
conceptList* readFile(conceptList* list, char* text, FILE *fout)
{
	conceptList* newNode;
	char line[SIZE];
	FILE *fin;


	char *token1 = NULL;
	char *token2 = NULL;

	token1 = strtok(text, ">");
	token2 = strtok(NULL, "\n");

	while (*token2 == ' ') 
		token2++;

	fin = fopen(token2, "r");
	if (fin == NULL)
	{
		printf("3B$ Damn! I can't find %s file!\n", token2);
		return list;
	}

	printf("3B$ opened file %s\n", token2);
	fprintf(fout, "3B$ opened file %s\n", token2);

	// oso iparxoun stoixeia sto arxeio pou anoiksa
	while (!feof(fin))
	{
	  fgets(line, SIZE, fin);
		token1 = strtok(line, ":");
		token2 = strtok(NULL, "\n");

		while (*token2 == ' ') 
			token2++;

		newNode = make_new(token1, token2, "file", fout);

		if (concept_exists(token1, list) == 1)
		{
			free(newNode);
			showRandomMessage(conceptExistsMessage, token1, fout);
		}
		else
		{
			list = addNode(list, newNode);
			showRandomMessage(conceptNewMessage, token1, fout);
		}
	}
	
	fclose(fin);
	return list;
}
// learn this > egg: food
conceptList* addSentence(conceptList* list, char* text,  char learnedFrom[5], FILE *f)
{
	conceptList* newNode;

	char *token1 = NULL;
	char *token2 = NULL;
	token1 = strtok(text, ">");
    token1 = strtok(NULL, ":");


	while (*token1 == ' ') 
		token1++;

	token2 = strtok(NULL, "\n");
	while (*token2 == ' ') 
		token2++;

	newNode = make_new(token1, token2, learnedFrom, f);

	if (concept_exists(token1, list) == 1)
  {
		free(newNode);
		showRandomMessage(conceptExistsMessage, token1, f);
		return list;
	}

	list = addNode(list, newNode);
	showRandomMessage(conceptNewMessage, token1, f);
	return list;


}
