#ifndef MYSTRUCTURE_H
#define MYSTRUCTURE_H

typedef struct {
	char name[20];
	char gender;
	char dept[20];
	int ID;
	int group;
}STU;

typedef struct node {
	STU data;
	struct node *next;
}NODE;

typedef struct {
	int count;
	NODE* head;
}LIST;
#endif