# -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int show_menu(); // 처음 메뉴 띄워주는 함수
void print_tutorial(); // 게임 방법 설명해주는 함수
void start_game(); // 게임 시작 함수
int get_user_card(int select, int i, int j, int* Eis_selected, int* Sis_selected, int* ms, int* cs); // 사용자가 무슨 카드를 고를지 선택하는 함수
void show_table(int j, int select, int Eis_selected, int Sis_selected); // 남은 카드가 무엇이 있는지 보여주는 함수
int get_computer_card(); // 컴퓨터가 무슨 카드를 고를지 선택하는 함수
int compare_card(int a, int x, int y, int* ms, int* cs); // 사용자와 컴퓨터의 카드를 비교하는 함수
void calc_score(int select, int a, int b, int* ms, int* cs); // 결과를 통해 점수를 계산하는 함수

int main()
{
	show_menu();

	return 0;
}

int show_menu()
{
	int num;
	printf("************ E - Card ************\n");
	printf("           1. 게임 설명           \n");
	printf("           2. 게임 시작           \n");
	printf("           3. 게임 종료           \n");
	printf("**********************************\n");
	printf("입력: ");
	scanf("%d", &num);
	getchar();

	switch (num)
	{
	case 1: system("cls"); // 1을 입력하면 게임 방법 설명
			print_tutorial();
			break;
	case 2: start_game(); // 2를 입력하면 게임 시작
			break;
	case 3: printf("프로그램을 종료합니다..."); // 3을 입력하면 게임 종료
			exit(0); // 처음 게임에 들어와서 3번을 눌러 종료 할 때나, 게임을 하던 중 메뉴로 와서 3번을 눌러서 종료 할 때 모두 프로그램이 정상적으로 종료할 수 있도록 exit()를 사용함.
	default: printf("올바른 메뉴를 선택하세요..."); // 1,2,3 이외의 수를 입력하면 올바른 수를 입력하라는 메시지가 뜨고 1초후에 다시 고를 수 있음
			Sleep(1000);
			system("cls");
			show_menu();
	}
	return 0;
}


void print_tutorial()
{
	char c;
	printf("************* E - Card 게임 설명 ***************************************\n");
	printf("                                                                        \n");
	printf("본 게임은 도박묵시록 카이지의 E - Card 게임을 기반으로 한다.            \n");
	printf("                                                                        \n");
	printf("1. 두 플레이어는 황제패와 노예패 중 하나의 패를 각각 선택한다.          \n");
	printf("   황제패 = 황제 카드 1장 + 시민 카드 4장                               \n");
	printf("   노예패 = 노예 카드 1장 + 시민 카드 4장                               \n");
	printf("                                                                        \n");
	printf("2. 두 사용자는 매 턴마다 한 장의 카드를 안보이게 내밀고, 함께 뒤집는다. \n");
	printf("                                                                        \n");
	printf("3. 아래의 카드 간 상성 관계에 따라 승패를 결정한다.                     \n");
	printf("   단, 두 플레이어가 시민 카드를 냈다면, 무승부로 처리한다.             \n");
	printf("                                                                        \n");
	printf("4. 내밀었던 카드는 소모되고 승패가 결정될 때까지 2로 돌아가 반복한다.   \n");
	printf("                                                                        \n");
	printf("상성관계 : 황제 > 시민 > 노예 > 황제                                    \n");
	printf("                                                                        \n");
	printf("************************************************************************\n");
	printf("메뉴로 돌아가려면 Enter키를 입력하세요...");

	scanf("%c", &c);
	system("cls");
	show_menu();
}

void start_game()
{

	int select; // 황제패를 골랐는지 노예패를 골랐는지 구분
	int i, j; // i는 게임 횟수, j는 한 횟수 안에서 반복되는 횟수(무승부 때문에)
	int ms = 0; // 나의 점수
	int cs = 0; // 컴퓨터의 점수
	i = 1;
	while(1)
	{
		int a, b, c, d, e, f, g, h, k;
		int m = 0; // j = 1일 때, 승리, 패배, 무승부를 구분하는 변수
		int n = 0; // j != 1일 때, 승리, 패배, 무승부를 구분하는 변수
		system("cls");
		printf("[게임횟수: %d, 컴퓨터: %d점, 나: %d점]   \n", i, cs, ms);
		printf("                                      \n");
		printf("[카드 패 선택]                        \n");
		printf("**************************************\n");
		printf("                                      \n");
		printf("0. 황제패 (황제 1장, 시민 4장)        \n");
		printf("1. 노예패 (노예 1장, 시민 4장)        \n");
		printf("                                      \n");
		printf("**************************************\n");
		printf("입력: ");
		scanf("%d", &select);
		getchar();

		switch (select)
		{
		case 0: for (j = 1; j < 6; j++)
		{
			if (j == 1) // 첫 반복에는 황제가 선택되지 않았으므로 Eis_selected를 0으로 설정해주기 위해 따로 빼냄
			{
				int Eis_selected = 0;
				int Sis_selected = 0;
				system("cls");
				a = get_user_card(select, i, j, &Eis_selected, &Sis_selected, &ms, &cs); // user의 카드패
				b = get_computer_card(); // computer의 카드패
				m = compare_card(select, a, b, &ms, &cs);
				if (m == 0) // 무승부였을 경우 같은 회차에서 반복
				{
					continue;
				}
				else // 무승부 이외의 경우 다음 회차로 넘어감
				{
					break;
				}
			}
			else // 두번째 횟수 이상에서는 Eis_selected가 앞에서 선택 여부에 따라 달라짐
			{
				int Eis_selected;
				int Sis_selected = 0;
				system("cls");
				g = get_user_card(select, i, j, &Eis_selected, &Sis_selected, &ms, &cs); // user의 카드패
				h = get_computer_card(); // computer의 카드패
				n = compare_card(select, g, h, &ms, &cs);
				if (n == 0) // 무승부였을 경우 같은 회차에서 반복
				{
					continue;
				}
				else // 무승부 이외의 경우 다음 회차로 넘어감
				{
					break;
				}
			}
		}
				break;
		case 1: for (j = 1; j < 6; j++)
		{
			if (j == 1) // 첫 반복에는 노예가 선택되지 않았으므로 Sis_selected를 0으로 설정해주기 위해 따로 빼냄
			{
				int Eis_selected = 0;
				int Sis_selected = 0;
				system("cls");
				a = get_user_card(select, i, j, &Eis_selected, &Sis_selected, &ms, &cs); // user의 카드패
				b = get_computer_card(); // computer의 카드패
				m = compare_card(select, a, b, &ms, &cs);
				if (m == 0) // 무승부였을 경우 같은 회차에서 반복
				{
					continue;
				}
				else // 무승부 이외의 경우 다음 회차로 넘어감
				{
					break;
				}
			}
			else // 두번째 횟수 이상에서는 Sis_selected가 앞에서 선택 여부에 따라 달라짐
			{
				int Eis_selected = 0;
				int Sis_selected;
				system("cls");
				g = get_user_card(select, i, j, &Eis_selected, &Sis_selected, &ms, &cs); // user의 카드패
				h = get_computer_card(); // computer의 카드패
				n = compare_card(select, g, h, &ms, &cs);
				if (n == 0) // 무승부였을 경우 같은 회차에서 반복
				{
					continue;
				}
				else
				{
					break;
				}
			}
		}
				break;
		default: printf("올바른 메뉴를 선택하세요...\n");
			Sleep(1000);
			system("cls");
			start_game();
		}
		i++; // 함수의 마지막에서 while문으로 반복할 때, i가 횟수를 의미하므로 함수가 한 번 종료될 때마다 i를 1씩 키워줌
	}
}

int get_user_card(int select, int i, int j, int* Eis_selected, int* Sis_selected, int* ms, int* cs)
{
	int numb;
	if (select == 0)
	{
		int king, city;
		printf("[게임횟수: %d  , 컴퓨터: %d점, 나: %d점]   \n", i, *cs, *ms);
		printf("                                      \n");
		printf("**************************************\n");
		show_table(j, select, &Eis_selected, &Sis_selected);
		printf("**************************************\n");
		printf("                                      \n");
		printf("[카드 선택]                           \n");
		printf("*******************                   \n");
		printf("                                      \n");
		if (*Eis_selected == 1)
		{
			king = 0;
			city = 6 - j;
		}
		else
		{
			king = 1;
			city = 5 - j;
		}
		printf("0. 황제 (%d장)                         \n", king);
		printf("1. 시민 (%d장)                         \n", city);
		printf("                                      \n");
		printf("*******************                   \n");
		if (j != 5) // 한 회차의 승부에서 무승부가 4번 연속 나온 경우가 아니라면 scanf함수를 통해 사용자에게 값을 입력받는다.
		{
			printf("입력: ");
			scanf("%d", &numb);
			getchar();
		}
		else // 한 회차의 승부에서 무승부가 4번 연속 나오면 낼 카드는 한장밖에 없으므로 자동으로 승부가 나도록 한다.
		{
			printf("입력: ", numb = 0);
		}
		if (numb == 0) // 0이 입력되면 다음부터 Eis_selected의 값은 1이 됨
		{
			*Eis_selected = 1;
		}
		else
		{
			if (king == 0) // 이전에 king의 값이 0이면, 그 이전에 이미 Eis_selected값이 1이었다는 의미임
			{
				*Eis_selected = 1;
			}
			else if (king == 1) // king의 값이 1이면, 아직 황제 카드가 쓰이지 않았다는 의미임
			{
				*Eis_selected = 0;
			}
		}
	}
	else
	{
		int slave, city;
		printf("[게임횟수: %d  , 컴퓨터: %d점, 나: %d점]   \n", i, *cs, *ms);
		printf("                                      \n");
		printf("**************************************\n");
		show_table(j, select, &Eis_selected, &Sis_selected);
		printf("**************************************\n");
		printf("                                      \n");
		printf("[카드 선택]                           \n");
		printf("*******************                   \n");
		printf("                                      \n");
		if (*Sis_selected == 1)
		{
			slave = 0;
			city = 6 - j;
		}
		else
		{
			slave = 1;
			city = 5 - j;
		}
		printf("0. 노예 (%d장)                         \n", slave);
		printf("1. 시민 (%d장)                         \n", city);
		printf("                                      \n");
		printf("*******************                   \n");
		if (j != 5) // 한 회차의 승부에서 무승부가 4번 연속 나온 경우가 아니라면 scanf함수를 통해 사용자에게 값을 입력받는다.
		{
			printf("입력: ");
			scanf("%d", &numb);
			getchar();
		}
		else // 한 회차의 승부에서 무승부가 4번 연속 나오면 낼 카드는 한장밖에 없으므로 자동으로 승부가 나도록 한다.
		{
			printf("입력: ", numb = 0);
		}
		if (numb == 0) // 0이 입력되면 다음부터 Sis_selected의 값은 1이 됨
		{
			*Sis_selected = 1;
			if (*Sis_selected = 1)
			{
				*Sis_selected = 1;
			}
		}
		else
		{
			if (slave == 0) // 이전에 slave의 값이 0이면, 그 이전에 이미 Sis_selected값이 1이었다는 의미임
			{
				*Sis_selected = 1;
			}
			else // slave의 값이 1이면, 아직 노예 카드가 쓰이지 않았다는 의미임
			{
				*Sis_selected = 0;
			}
		}
	}
	return numb;
}

void show_table(int j, int select, int Eis_selected, int Sis_selected)
{
	if (select == 0)
	{
			char name1;
			for (int b = 5; b > j - 1; b--)
			{
				printf(" ┌─┐ ");
			}
			printf("\n");
			for (int c = 5; c > j - 1; c--)
			{
				printf(" │? │ ");
			}
			printf("\n");
			for (int d = 5; d > j - 1; d--)
			{
				printf(" └─┘ ");
			}
			printf("\n");
			for (int e = 5; e > j - 1; e--)
			{
				printf(" ┌─┐ ");
			}
			printf("\n");
			for (int f = 5; f > j - 1; f--)
			{
				if (f == 5)
				{
					if (Eis_selected == 1)
					{
						name1 = 'C';
					}
					else
					{
						name1 = 'E';
					}
				}
				else
				{
					name1 = 'C';
				}
				printf(" │%c │ ", name1);
			}
			printf("\n");
			for (int g = 5; g > j - 1; g--)
			{
				printf(" └─┘ ");
			}
			printf("\n");
		}
	else
	{
		char name1;
		for (int b = 5; b > j - 1; b--)
		{
			printf(" ┌─┐ ");
		}
		printf("\n");
		for (int c = 5; c > j - 1; c--)
		{
			printf(" │? │ ");
		}
		printf("\n");
		for (int d = 5; d > j - 1; d--)
		{
			printf(" └─┘ ");
		}
		printf("\n");
		for (int e = 5; e > j - 1; e--)
		{
			printf(" ┌─┐ ");
		}
		printf("\n");
		for (int f = 5; f > j - 1; f--)
		{
			if (f == 5)
			{
				if (Sis_selected == 1)
				{
					name1 = 'C';
				}
				else
				{
					name1 = 'S';
				}
			}
			else
			{
				name1 = 'C';
			}
			printf(" │%c │ ", name1);
		}
		printf("\n");
		for (int g = 5; g > j - 1; g--)
		{
			printf(" └─┘ ");
		}
		printf("\n");
	}
} // 카드제작

int get_computer_card()
{
	int seed;
	seed = time(NULL);
	srand(seed);
	int card = rand() % 2;

	return card;
} // 컴퓨터의 카드 선택

int compare_card(int a, int x, int y, int* ms, int* cs)
{
	int result;
	printf("\n[선택 결과]\n");
	printf("**********************\n");
	printf("\n");
	if (a == 0)
	{
		if (x == 0)
		{
			printf("* 나의 카드     : 황제\n");
		}
		else
		{
			printf("* 나의 카드     : 시민\n");
		}
		if (y == 0)
		{
			printf("* 컴퓨터의 카드 : 노예\n");
		}
		else
		{
			printf("* 컴퓨터의 카드 : 시민\n");
		}
		if (x == 0 && y == 0) // 패배하였을 때는 결과값이 2로 나옴
		{
			printf("* 결과 : 나의 패배         \n");
			result= 2;
		}
		else if (x == 0 && y == 1) // 승리하였을 때는 결과값이 1로 나옴
		{
			printf("* 결과 : 나의 승리         \n");
			result= 1;
		}
		else if (x == 1 && y == 0)
		{
			printf("* 결과 : 나의 승리         \n");
			result= 1;
		}
		else // 무승부일 때는 결과값이 0으로 나옴
		{
			printf("* 결과 : 무승부         \n");
			result= 0;
		}
	}
	else if (a == 1)
	{
		if (x == 0)
		{
			printf("* 나의 카드     : 노예\n");
		}
		else
		{
			printf("* 나의 카드     : 시민\n");
		}
		if (y == 0)
		{
			printf("* 컴퓨터의 카드 : 황제\n");
		}
		else
		{
			printf("* 컴퓨터의 카드 : 시민\n");
		}
		if (x == 0 && y == 0)
		{
			printf("* 결과 : 나의 승리         \n");
			result= 1;
		}
		else if (x == 0 && y == 1)
		{
			printf("* 결과 : 나의 패배         \n");
			result = 2;
		}
		else if (x == 1 && y == 0)
		{
			printf("* 결과 : 나의 패배         \n");
			result= 2;
		}
		else
		{
			printf("* 결과 : 무승부         \n");
			result= 0;
		}
	}
	printf("                                \n");
	printf("**********************\n");
	printf("                                \n");


	if (a == 0)
	{
		if (x == 1 && y == 1) // 무승부일 때는 같은 회차에서 반복 실행
		{
			printf("다음 턴 (Enter키를 입력하세요...)");
			char c;
			scanf("%c", &c);
			system("cls");
		}
		else if (x == 0 && y == 1) // 무승부가 아닐 때는 calc_score함수로 가서 점수를 구함
		{
			calc_score(a, x, y, ms, cs);
		}
		else if (x == 1 && y == 0)
		{
			calc_score(a, x, y, ms, cs);
		}
		else
		{
			calc_score(a, x, y, ms, cs);
		}
	}
	else
	{
		if (x == 1 && y == 1)
		{
			printf("다음 턴 (Enter키를 입력하세요...)");
			char c;
			scanf("%c", &c);
			system("cls");
		}
		else if (x == 0 && y == 1)
		{
			calc_score(a, x, y, ms, cs);
		}
		else if (x == 1 && y == 0)
		{
			calc_score(a, x, y, ms, cs);
		}
		else
		{
			calc_score(a, x, y, ms, cs);
		}
	}
	return result;
}

void calc_score(int select, int a, int b, int* ms, int* cs)
{
	char q;
	printf("[현재 점수]\n");
	printf("***********************\n");
	printf("\n");
	if (select == 0)
	{
		if (a == 0 && b == 1)
		{
			*ms = *ms + 200;
			*cs = *cs - 300;
		}
		else if (a == 1 && b == 0)
		{
			*ms = *ms + 200;
			*cs = *cs - 300;
		}
		else if (a == 0 && b == 0)
		{
			*ms = *ms - 500;
			*cs = *cs + 700;
		}
		else
		{
			*ms = *ms;
			*cs = *cs;
		}
	}
	else
	{
		if (a == 0 && b == 0)
		{
			*ms = *ms + 700;
			*cs = *cs - 500;
		}
		else if (a == 1 && b == 0)
		{
			*ms = *ms - 300;
			*cs = *cs + 200;
		}
		else if (a == 0 && b == 1)
		{
			*ms = *ms - 300;
			*cs = *cs + 200;
		}
		else
		{
			*ms = *ms;
			*cs = *cs;
		}
	}
	printf("*나의 점수     : %d\n", *ms);
	printf("*컴퓨터의 점수 : %d\n", *cs);
	printf("\n");
	printf("***********************\n");
	printf("\n");
	if (*ms >= 2000) // 나의 점수가 2000점 이상이면 내가 승리함
	{
		printf("[최종 결과]\n");
		printf("*********************");
		printf("\n");
		printf("* 당신의 승리 !");
		printf("\n");
		printf("*********************");
		printf("\n");
		printf("Enter키를 입력하세요...");
		char c;
		scanf("%c", &c);
		system("cls");
		show_menu();
	}
	else if (*cs >= 2000) // 컴퓨터의 점수가 2000점 이상이면 컴퓨터가 승리함
	{
		printf("[최종 결과]\n");
		printf("*********************");
		printf("\n");
		printf("* 당신의 패배 !");
		printf("\n");
		printf("*********************");
		printf("\n");
		printf("Enter키를 입력하세요...");
		char c;
		scanf("%c", &c);
		system("cls");
		show_menu();
	}
	else // 나와 컴퓨터 모두가 2000점이 되지 않으면 y/n의 여부에 따라 게임을 더 할지 말지 결정함
	{
		printf("게임을 계속하시겠습니까? (y/n): ");
		scanf("%c", &q);
		getchar();
		if (q == 'y' || q == 'Y')
		{
			system("cls");

		}
		else
		{
			system("cls");
			show_menu();
		}
	}
}
