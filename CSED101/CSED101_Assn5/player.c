# -*- coding: utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mystructure.h"
#include "player.h"
#include "group.h"

void ent_player(FILE *infile, LIST **plist)
{
	NODE *fi;
	int n;
	while (1)
	{
		NODE *temp = (NODE*)malloc(sizeof(NODE));
		n = fscanf(infile, "%[^\t]\t", temp->data.name); //fscanf함수를 통하여 플레이어의 데이터를 받아들인다.
		fscanf(infile, "%c\t", &temp->data.gender);
		fscanf(infile, "%[^\t]\t", temp->data.dept);
		fscanf(infile, "%d\t", &temp->data.ID);
		fscanf(infile, "%d\n", &temp->data.group);
		if (n == EOF)
			break;
		switch (temp->data.group) //switch-case문을 통하여 플레이어의 그룹에 따라 링크드리스트에 삽입한다.
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			add_node(plist, temp);
			break;
		default:
			printf("ERROR GROUP NUMBER\n");
			return;
		}
	}
}

void show_all_player(LIST **plist)
{//모든 플레이어의 목록을 보여준다.
	show_player(plist, 1);
	show_player(plist, 2);
	show_player(plist, 3);
	show_player(plist, 4);
	show_player(plist, 5);
}

void show_player(LIST **plist, int gn) //gn에 해당되는 플레이어의 목록을 보여준다.
{
	NODE *pr = plist[gn - 1]->head;
	printf("============================== GROUP %d ============================\n", gn);
	if (plist[gn - 1]->head == NULL)
		return;
	else
	{
		do {
			printf("%-20s	%c	%-20s	%d\n", pr->data.name, pr->data.gender, pr->data.dept, pr->data.ID);
			pr = pr->next;
		} while (pr != plist[gn - 1]->head);
	}
}

void add_player(LIST **plist)
{
	NODE *temp = (NODE*)malloc(sizeof(NODE)); //추가할 노드를 동적할당 해준다.
	NODE *fi;
	printf("StudenrID: ");
	scanf("%d", &temp->data.ID);
	getchar();

	for (int gn = 0; gn < 5; gn++) //입력한 ID가 이미 존재하는지를 검사한다.
	{
		fi = plist[gn]->head;
		do
		{
			if (fi == NULL)
			{
				break;
			}
			else
			{
				if (temp->data.ID == fi->data.ID)
				{
					printf("Player already exists\n");
					printf("Name			Gender		Dept		StudentID		Group\n");
					printf("%-20s	%c	%-20s	%d		%d\n", fi->data.name, fi->data.gender, fi->data.dept, fi->data.ID, fi->data.group);
					return;
				}
				fi = fi->next;
			}
		} while (fi != plist[gn]->head);
	}

	printf("Name: ");
	scanf("%[^\n]", temp->data.name);
	getchar();
	printf("Gender: ");
	scanf("%c", &temp->data.gender);
	getchar();
	printf("Dept: ");
	scanf("%[^\n]", temp->data.dept);
	getchar();
	printf("Group: ");
	scanf("%d", &temp->data.group);
	getchar();

	add_node(plist, temp);
	printf("Player successfully added to group %d\n", temp->data.group);
}

void remove_player(LIST **plist)
{
	NODE *temp;
	NODE *prev;
	int rID;
	printf("StudentID: "); //삭제할 학생의 ID를 입력받는다.
	scanf("%d", &rID);
	getchar();

	for (int gn = 0; gn < 5; gn++)
	{
		NODE *fi = plist[gn]->head;
		if (fi != NULL)
		{
			do //삭제할 ID가 있는 경우 node를 삭제한다.
			{
				if (rID == fi->data.ID)
				{
					remove_node(plist, fi, gn);
					printf("Player successfully removed from group %d\n", gn + 1);
					return;
				}
				fi = fi->next;
			} while (fi != plist[gn]->head);
		}
	}

	printf("Players does not exist!\n"); //삭제할 ID가 없는 경우
}

void quit(LIST **plist)
{
	FILE *outfile;
	NODE *pr;
	NODE *fr;
	outfile = fopen("result_game.txt", "w");
	for (int gn = 0; gn < 5; gn++) //현재까지의 플레이어 목록을 result_game.txt 파일에 출력한다.
	{
		pr = plist[gn]->head;
		if (pr != NULL)
		{
			do {
				fprintf(outfile, "%-20s	%c	%-20s	%d	%d\n", pr->data.name, pr->data.gender, pr->data.dept, pr->data.ID, pr->data.group);
				pr = pr->next;
			} while (pr != plist[gn]->head);
		}
	}

	NODE *fr2;
	for (int gn = 0; gn < 5; gn++) //링크드리스트에 사용된 노드들을 동적할당 해제시킨다.
	{
		fr = plist[gn]->head;
		if (fr != NULL)
		{
			do {
				fr2 = fr->next;
				free(fr);
				fr = fr2;
			} while (fr != plist[gn]->head);
		}
	}

	for (int gn = 0; gn < 5; gn++) //링크드리스트에 사용된 그룹들을 동적할당 해제시킨다.
		free(plist[gn]);
	free(plist); //plist를 동적할당 해제시킨다.
	fclose(outfile);

	printf("File saved. Bye!");
	return;
}
