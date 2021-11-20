# -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>
#define MaxArr 9
#define GRAY "\x1b[90m"
#define ORANGE "\x1b[91m"
#define GREEN "\x1b[92m"
#define YELLOW "\x1b[93m"
#define BLUE "\x1b[94m"
#define PURPLE "\x1b[95m"
#define SKY "\x1b[96m"
#define WHITE "\x1b[97m"
#define RESET "\x1b[0m"

int ReadBoard(int board[MaxArr][MaxArr], int* row, int* col);
void PrintBoard(int board[MaxArr][MaxArr], int row, int col);
int RemoveChunk(int board[MaxArr][MaxArr], int sub[MaxArr][MaxArr], int row, int col);
void UpdateBoard(int board[MaxArr][MaxArr], int row, int col);
void swap(int* x, int* y);
void Checkcell(FILE *infile, int row, int col);
void Checkseq(FILE *infile, int row, int col);

int main()
{
	int board[MaxArr][MaxArr] = { 0 };
	int sub[MaxArr][MaxArr];
	int row, col;
	int deter;
	char c;
	ReadBoard(board, &row, &col);
	FILE *outfile;
	outfile = fopen("result.txt", "w"); // result.txt 파일을 쓰기 모드로 염.
	do // do - while 문을 통하여 PrintBoard, RemoveChunk, UpdateBoard 함수를 deter값이 0이 되지 않을 때까지 반복하여 호출함.
	{
		system("clear"); // 화면을 지워주는 역할
		PrintBoard(board, row, col); //화면에 보드를 띄워주는 역할
		getchar();

		deter = RemoveChunk(board, sub, row, col); // 3개 이상 중복되는 숫자를 0으로 지워주는 역할
		if (deter == 0)
		{
			break;
		}

		system("clear"); // 화면을 지워주는 역할
		PrintBoard(board, row, col); //화면에 보드를 띄워주는 역할
		getchar();

		UpdateBoard(board, row, col); // 제거 된 자리의 윗쪽의 무늬들이 순서대로 내려와 채우는 역할
	} while (deter);
	int i, j;
	for (i = 0; i < row; i++) // for문을 두번 사용하여 result.txt에 결과값을 저장함
	{
		for (j = 0; j < col; j++)
		{
			fprintf(outfile, "%2d", board[i][j]);
		}
		fprintf(outfile, "\n");
	}
	fclose(outfile);
	return 0;
}

int ReadBoard(int board[MaxArr][MaxArr], int* row, int* col)
{
	int i, j;
	int test = 0;
	FILE *infile;
	if ((infile = fopen("board.txt", "r")) == NULL) // board.txt 파일이 없으면 ERROR을 표시해줌
	{
		printf("ERROR opening board.txt\n");
		exit(100);
	}
	fscanf(infile, "%d %d\n", row, col); //row와 col을 fscanf함수를 통해 받음
	for (i = 0; i < *row; i++)
	{
		for (j = 0; j < *col; j++)
		{
			fscanf(infile, "%d", &board[i][j]); //fscanf함수를 통해 board를 채우는 값들을 받음
			if (board[i][j] - 7 < -6 || board[i][j] - 7 > 0) //1부터 7이외의 무늬가 있을때는 에러메세지를 출력함
			{
				printf("ERROR pattern\n");
				exit(101);
			}
		}
	}
	Checkcell(infile, *row, *col); //셀의 개수가 다른지 확인해주는 함수
	Checkseq(infile, *row, *col); // row와 col이 뒤집어지지 않았는지 확인해주는 함수
}

void PrintBoard(int board[MaxArr][MaxArr], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++) // 두번의 for문을 이용하여 화면에 board를 출력함
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == 0) // 매크로를 통하여 숫자에 따른 색을 지정함
				printf(GRAY);
			else if (board[i][j] == 1)
				printf(ORANGE);
			else if (board[i][j] == 2)
				printf(GREEN);
			else if (board[i][j] == 3)
				printf(YELLOW);
			else if (board[i][j] == 4)
				printf(BLUE);
			else if (board[i][j] == 5)
				printf(PURPLE);
			else if (board[i][j] == 6)
				printf(SKY);
			else if (board[i][j] == 7)
				printf(WHITE);
			printf("%2d", board[i][j]);
			printf(RESET);
		}
		printf("\n");
	}
}

int RemoveChunk(int board[MaxArr][MaxArr], int sub[MaxArr][MaxArr], int row, int col)
{
	int result = 0;
	int sum = 0;
	int i, j;
	for (i = 0; i < row; i++) // board에 있는 값들을 sub로 옮김
		for (j = 0; j < col; j++)
		{
			sub[i][j] = board[i][j];
		}

	for (i = 0; i < row; i++) //이 함수가 시작될때 board를 기준으로 하여 가로로 3개 중복되는 값이 있으면 같은 위치의 sub에 값을 0으로 바꿈
	{
		for (j = 0; j < col - 2; j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2])
			{
				sub[i][j] = 0;
				sub[i][j + 1] = 0;
				sub[i][j + 2] = 0;
				result = 1; // 바뀌는 값이 있을 경우 결과값을 1로 설정함
			}
		}
	}
	for (j = 0; j < col; j++)
		for (i = 0; i < row - 2; i++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j])
			{
				sub[i][j] = 0;
				sub[i + 1][j] = 0;
				sub[i + 2][j] = 0;
				result = 1; // 바뀌는 값이 있을 경우 결과값을 1로 설정함
			}
		}
	for (i = 0; i < row; i++) // 바뀌는 값이 없을 경우에는 board와 sub의 같은 위치에 있는 모든 수가 동일할 것이므로 이를 검사하는 장치임
		for (j = 0; j < col; j++)
		{
			if (sub[i][j] == board[i][j])
				sum++;
		}
	if (sum == row * col) // 바뀌는 값이 없을 경우에는 sum의 값이 row * col의 값과 같은 것이므로 이를 검사함. 
	{
		return 0; // 0을 return하여 main함수의 do-while문을 종료시킴
	}
	for (i = 0; i < row; i++) // sub에서 바뀐 값들을 다시 board로 넣어주는 역할을 함
		for (j = 0; j < col; j++)
		{
			board[i][j] = sub[i][j];
		}
	return result;
}

void UpdateBoard(int board[MaxArr][MaxArr], int row, int col)
{
	int i, j, num;
	for (num = 0; num < row - 1; num++) // row만큼의 줄이 있을때 가장 최대로 필요한 swap이 row-1번이므로 이를 for문으로 반복해줌
		for (i = 1; i < row; i++) // 두번째 줄부터 0이 있다면 위의 숫자와 바꿔줌
			for (j = 0; j < col; j++)
			{
				if (board[i][j] == 0)
					swap(&board[i][j], &board[i - 1][j]);
			}
}

void swap(int* x, int* y) // 받아온 두 address를 swap해줌
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void Checkcell(FILE *infile, int row, int col)
{
	int i, j;
	int test = 0;
	int arr[MaxArr][MaxArr] = { 0 }; // 배열 내부의 초기값들을 모두 0으로 설정함
	infile = fopen("board.txt", "r");
	fscanf(infile, "%d %d", &row, &col);
	for (i = 0; i < MaxArr; i++)
	{
		for (j = 0; j < MaxArr; j++)
		{
			fscanf(infile, "%d", &arr[i][j]);
			if (arr[i][j] != 0) // 입력된 값은 1에서 7사이의 값이므로(0이 아니므로) 배열의 값이 0이 아니면 입력된 값으로 취급함.
				test++;
		}
	}
	if (test != row * col) // test의 값(입력된 값의 개수)이 row와 col의 값과 같지 않다면 필요한 셀 이외의 값을 가진다는 의미이므로 ERROR을 표시함.
	{
		printf("ERROR number of cells\n");
		exit(102);
	}
}

void Checkseq(FILE *infile, int row, int col) // row와 col을 거꾸로 생각하여 셀의 개수는 같지만 행과 열이 뒤집어졌을때 ERROR을 출력한다.
{
	infile = fopen("board.txt", "r");
	fscanf(infile, "%d %d", &row, &col);
	int arr[MaxArr][MaxArr];
	char ent;
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			fscanf(infile, "%d", &arr[i][j]);
		}
		ent = fgetc(infile);
		if (ent != '\n')
		{
			printf("ERROR row and col are changed\n");
			exit(103);
		}
	}
}
