
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _HEADERFILE_

#define MESSAGES 5
#define SIZE 1000


typedef struct cList
{
	char *sentence;
	char *concept;
	int timesUsed;
	char learnedFrom[5];
	struct cList* next;
}conceptList;

const char* list1Message = "What do you know about?";
const char* list2Message = "What do you talk about?";
const char* exitMessage = "exit";
const char* learnMessage = "learn this > ";
const char* readMessage = "read this > ";
const char* forgetMessage = "forget this > ";

const char* conceptExistsMessage[MESSAGES] = { "3B$  I already know about %s \n",
										"3B$ I know about %s dude!\n",
										"3B$ Sorry ,but I know about %s \n",
										"3B$ Don't talk to me about %s again!\n",
										"3B$ Dude you really must stop telling me about %s \n"};
const char* conceptNewMessage[MESSAGES] = {"3B$ Good!!! Now I know about %s \n",
										"3B$ Interesting to know about %s \n",
										"3B$ Appreciate to know about %s \n",
										"3B$ My pleasure to know about %s \n",
										"3B$ Cool,now I know about %s \n"};
const char* conceptDeletedMessage[MESSAGES] = {"3B$ I delete %s \n",
										"3B$ Okay dude,I delete  %s \n",
										"3B$ This thing about %s is not important anyway! \n",
										"3B$ Iam bored deleting items...Okay I delete %s \n",
										"3B$ Really?Again?...I delete %s \n"};
const char* conceptNotDeletedMessage[MESSAGES] = {"3B$ I don't delete %s \n",
										"3B$ Usefull information anyway...I don't delete  %s \n",
										"3B$ I will remember this!!!I don't delete  %s \n",
										"3B$ I hope this is good...I don't delete %s \n",
										"3B$ Alright boss!!I don't delete %s \n"};


conceptList* make_new(char* concept, char* sentence, char learnedFrom[5], FILE *f);
conceptList* addSentence(conceptList* list, char* text, char learnedFrom[5], FILE *f);
int concept_exists(char *concept, conceptList* list);
void showRandomMessage(const char *msg[MESSAGES], char *concept, FILE *f);
conceptList* addNode(conceptList* list, conceptList* newNode);
void showNodes(conceptList* list, FILE* f);
void showNodesMore(conceptList* list, FILE* f);
conceptList* readFile(conceptList* list, char* text, FILE *f);
void free_mem(conceptList* list);
conceptList* forgetConcept(conceptList* list, char* text, FILE *f);
