# -*- coding: utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mystructure.h"
#include "player.h"
#include "group.h"

int main(int argc, char *argv[])
{
	LIST **plist;
	plist = (LIST**)malloc(sizeof(LIST*) * 5); //전체 링크드리스트를 총괄하는 역할을 한다.
	for (int i = 0; i < 5; i++) //그룹을 동적할당한다.
		plist[i] = (LIST*)malloc(sizeof(LIST));
	plist[0]->count = 0, plist[0]->head = NULL; //그룹의 count와 head를 초기화한다.
	plist[1]->count = 0, plist[1]->head = NULL;
	plist[2]->count = 0, plist[2]->head = NULL;
	plist[3]->count = 0, plist[3]->head = NULL;
	plist[4]->count = 0, plist[4]->head = NULL;
	FILE *infile;;
	if (argc == 1) //assn5.exe 옆에 아무것도 입력하지 않으면 자동으로 players.txt가 출력되게 한다.
	{
		infile = fopen("players.txt", "r");
		ent_player(infile, plist);
	}
	else
	{
		if (infile = fopen(argv[1], "r") == NULL) //입력받은 파일이 존재하지 않는 경우
		{
			printf("Cannot open file\n");
			return 1;
		}
		else //입력받은 파일이 존재 할 경우
		{
			infile = fopen(argv[1], "r");
			ent_player(infile, plist); //플레이어 목록 입력받기
		}
	}
	fclose(infile);
	printf("Name			Gender		Dept		StudentID\n");
	show_all_player(plist);// 전체 플레이어 목록 출력
	printf("\n");
	char *command;
	char real[20];

	while (1)
	{
		printf(">> ");
		scanf("%[^\n]", real);
		getchar();
		command = strtok(real, " "); //입력한 문자 중 공백문자 이전만을 command에 저장한다.

		if (strcmpi(command, "show") == 0) //strcmpi 함수를 통하여 대소문자 구분 없이 비교 가능하게 하였다.
		{
			int gn;
			printf("Which group? (0: all) ");
			scanf("%d", &gn);
			getchar();
			printf("Name			Gender		Dept		StudentID\n");
			if (gn == 0)
				show_all_player(plist);
			else
				show_player(plist, gn);
		}

		else if (strcmpi(command, "add") == 0)
		{
			add_player(plist);
		}

		else if (strcmpi(command, "remove") == 0)
		{
			remove_player(plist);
		}

		else if (strcmpi(command, "play") == 0)
		{
			char *play_what;
			play_what = strtok(NULL, " "); //strtok의 첫번째 인자를 NULL로 받음으로써 이전 strtok에서 사용하고 남은 문자를 불러들인다.
			if (play_what == NULL)
			{
				infile = fopen("game.txt", "r");
				if (infile == NULL) //열려는 파일이 존재하지 않는 경우
				{
					printf("Cannot open file!");
					continue;
				}
			}
			else
			{
				infile = fopen(play_what, "r");
				if (infile == NULL) //열려는 파일이 존재하지 않는 경우
				{
					printf("Cannot open file!");
					continue;
				}
			}
			play(infile, plist);
		}

		else if (strcmpi(command, "quit") == 0)
		{
			quit(plist);
			break;
		}
		printf("\n");
	}
	return 0;
}
