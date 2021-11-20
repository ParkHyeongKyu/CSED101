# -*- coding: utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mystructure.h"
#include "player.h"
#include "group.h"

void play(FILE *infile, LIST **plist)
{
	NODE *select = NULL;
	NODE *select2 = NULL;
	NODE *where;
	NODE *where2;
	NODE *temp;
	NODE *temp2;
	NODE *fi;
	NODE *prev;
	NODE *prev2;
	int gn, ng, np, n, i, num;
	char filename[30] = { '\0' };

	for (gn = 0; gn < 5; gn++) //게임을 시작할 때 가장 첫 번째 술래를 정해준다.
	{
		if (plist[gn]->head != NULL)
		{
			select = plist[gn]->head;
			break;
		}
	}
	if (select == NULL) //플레이어가 한 명도 없을 경우
	{
		printf("And then there were none...\n");
		return;
	}

	printf("From						To\n");
	while (1)
	{
		n = fscanf(infile, "%d %d\n", &ng, &np);
		if (n == EOF) //파일의 끝에 도달하면 while문을 빠져나간다.
			break;

		if (plist[ng - 1]->head == NULL) //입력받은 조가 비어있을 경우 무시하고 그 다음 쿼리를 처리하도록 한다.
			continue;

		if (plist[select->data.group - 1]->head == select) //술래가 그룹의 head일 경우 술래는 그룹을 빠져나와야 하므로 head를 물려주고 원래있던 위치의 이전 위치를 prev에 저장한다.
		{
			for (prev = plist[select->data.group - 1]->head; prev->next != plist[select->data.group - 1]->head; prev = prev->next);
			plist[select->data.group - 1]->head = select->next;
			prev->next = plist[select->data.group - 1]->head;
		}

		if (plist[ng - 1]->head != NULL)
		{
			if (np > plist[ng - 1]->count && np % plist[ng - 1]->count != 0) //np를 그룹을 한 바퀴 이상 돌지 않도록 조정해준다.
			{
				np = np % plist[ng - 1]->count;
			}
			else if (np % plist[ng - 1]->count == 0)
			{
				np = plist[ng - 1]->count;
			}

			fi = plist[ng - 1]->head;
			i = 1;
			do { //다음턴에 술래가 될 사람을 찾는다.
				if (i == np)
				{
					select2 = fi;
					break;
				}
				i++;
				fi = fi->next;
			} while (fi != plist[ng - 1]->head);
		}


		printf("%-20s\t(Group %d)\t->\t%-20s\t(Group %d)\n", select->data.name, select->data.group, select2->data.name, select2->data.group);

		for (prev2 = plist[select2->data.group - 1]->head; prev2->next != plist[select2->data.group - 1]->head; prev2 = prev2->next); //다음턴에 술래가 될 사람이 있는 가장 마지막 그룹원을 prev2에 저장한다.

		if (select2 == plist[select2->data.group - 1]->head) //head가 술래라면 그룹의 가장 마지막 사람인 prev2가 다음턴에 술래가 될 사람의 이전 위치인 where2이다.
			where2 = prev2;
		else //술래가 head가 아닌 경우 where2를 찾는 방법이다.
		{
			temp2 = plist[select2->data.group - 1]->head;
			do {
				if (temp2->next == select2)
					break;
				temp2 = temp2->next;
			} while (temp2->next != plist[select2->data.group - 1]->head);

			if (temp2->next == select2)
				where2 = temp2;
			else
			{
				printf("No such position in this linked list!\n");
				return;
			}
		}

		if (select2 == plist[select2->data.group - 1]->head) //다음턴의 술래가 head일 경우 그 헤드를 현재 술래로 바꾸어준다.
			plist[select2->data.group - 1]->head = select;

		where2->next = select; //현재 술래를 다음턴의 술래의 위치로 옮겨준다.
		select->next = select2->next;

		select->data.group = select2->data.group; //현재 술래와 다음턴의 술래의 그룹이 바뀐다.

		select = select2; //현재의 다음턴의 술래는 다음턴에서는 현재의 술래가 되므로 바꾸어준다.
	}
	printf("\n\nGame over!\n");
	printf("%s (Group %d) is out.", select->data.name, select->data.group);

	remove_node(plist, select, select->data.group - 1);
}

void add_node(LIST **plist, NODE *temp)
{
	NODE *fi;
	if (plist[temp->data.group - 1]->count == 0) //사람이 없는 그룹에 들어갈 경우
	{
		temp->next = temp;
		plist[temp->data.group - 1]->head = temp;
	}
	else //사람이 있는 그룹에 들어갈 경우
	{
		for (fi = plist[temp->data.group - 1]->head; fi->next != plist[temp->data.group - 1]->head; fi = fi->next);
		fi->next = temp;
		temp->next = plist[temp->data.group - 1]->head;
	}
	(plist[temp->data.group - 1]->count)++;
}

void remove_node(LIST **plist, NODE *fi, int gn)
{
	NODE *temp;
	NODE *prev;
	if (plist[gn]->head == fi) //그룹에서 첫 번째 노드 삭제하는 경우
	{
		if (plist[gn]->count == 1) //그룹에 사람이 한 명 밖에 없을경우
		{
			plist[gn]->head = NULL;
			free(fi);
		}
		else //그룹에 사람이 2명 이상일 경우
		{
			plist[gn]->head = fi->next;
			for (prev = plist[gn]->head; prev->next != fi; prev = prev->next);
			prev->next = fi->next;
			free(fi);
		}
	}
	else //중간 노드 or 마지막 노드 삭제하는 경우
	{
		temp = plist[gn]->head;
		do {
			if (temp->next == fi)
				break;
			temp = temp->next;
		} while (temp->next != plist[gn]->head);

		if (temp->next == fi)
		{
			temp->next = fi->next;
			free(fi);
		}
	}
	(plist[gn]->count)--;
}
