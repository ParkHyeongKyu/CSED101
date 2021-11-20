# -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

int main()
{
	CUBIC **images = NULL;
	CUBIC **filters = NULL;

	int i = 0; // image 파일 전체개수
	int j = 0; // filter 파일 전체개수
	int num;

	do { //do-while문을 통하여 사용자가 선택한 번호로 입력한 작업이 모두 끝나면 quit를 누르지 않는 이상 계속 새로운 작업을 선택하여 진행할 수 있도록 해준다.
		num = show_menu();
		if (i == 0) // 처음에 num값으로 1이나 9를 입력하면 images에 한 칸이 필요하게 되므로 동적할당 해준다.
		{
			if (num == 1 || num == 9)
			{
				images = (CUBIC**)malloc(sizeof(CUBIC*) * (i + 1));
			}
		}
		else // num값으로 1이나 9를 입력하면 images에 한 칸이 추가로 필요하게 되므로 동적할당 해준다.
		{
			if (num == 1 || num == 9)
			{
				images = (CUBIC**)realloc(images, sizeof(CUBIC*) * (i + 1));
			}
		}
		if (j == 0) // 처음에 num값으로 4를 입력하면 filters에 한 칸이 필요하게 되므로 동적할당 해준다.
		{
			if (num == 4)
			{
				filters = (CUBIC**)malloc(sizeof(CUBIC*) * (j + 1));
			}
		}
		else // num값으로 4를 입력하면 filters에 한 칸이 필요하게 되므로 동적할당 해준다.
		{
			if (num == 4)
			{
				filters = (CUBIC**)realloc(filters, sizeof(CUBIC*) * (j + 1));
			}
		}
		switch (num)
		{
		case 1: image_load(images, i);
			i++;
			break;
		case 2: image_save(images, i);
			break;
		case 3: image_remove(images, i);
			images = (CUBIC**)realloc(images, sizeof(CUBIC*) * (i - 1)); //이미지를 제거한 후 압축해준다.
			i--;
			break;
		case 4: filter_load(filters, j);
			j++;
			break;
		case 5: filter_remove(filters, j);
			filters = (CUBIC**)realloc(filters, sizeof(CUBIC*) * (j - 1)); //filter을 제거한 후 압축해준다.
			j--;
			break;
		case 6: print(images, filters, i, j);
			break;
		case 7: normalize(images, i);
			break;
		case 8: denormalize(images, i);
			break;
		case 9: image_convolution(images, filters, i, j);
			if (i == 0)
			{
				break;
			}
			else
			{
				i++;
				break;
			}
		case 10: quit(images, filters, i, j);
			break;
		default: printf("Please enter one of the 1 - 10 number");
			return 0;
			break;
		}
	} while (num != 10);

	return 0;
}


int show_menu()
{
	int num;
	printf("===================================\n");
	printf("I        IMAGE CONVOLUTION        I\n");
	printf("I   1. Image load                 I\n");
	printf("I   2. Image save                 I\n");
	printf("I   3. Image remove               I\n");
	printf("I   4. Filter load                I\n");
	printf("I   5. Filter remove              I\n");
	printf("I   6. Print                      I\n");
	printf("I   7. Normalize                  I\n");
	printf("I   8. Denormalize                I\n");
	printf("I   9. Image convolution          I\n");
	printf("I   10. Quit                      I\n");
	printf("===================================\n");
	printf("Enter number: ");
	scanf("%d", &num);
	return num;
}

void print(CUBIC **images, CUBIC **filters, int i, int j) // 지금까지 있는 이미지와 필터의 목록을 출력해준다.
{
	printf("============ IMAGE LIST ===========\n");
	show_il(images, i);
	printf("============ FILTER LIST ==========\n");
	show_fl(filters, j);
}

void quit(CUBIC **images, CUBIC **filters, int i, int j) //프로그램을 종료해주는 함수이다.
{
	for (int q = 0; q < i; q++) //for문을 통하여 images안에 있는 데이터들을 해제시킨다.
	{
		for (int a = 0; a < (images[q]->H); a++)
		{
			for (int b = 0; b < (images[q]->W); b++)
			{
				free(images[q]->data[a][b]);
			}
			free(images[q]->data[a]);
		}
		free(images[q]->data);
		free(images[q]);
	}
	free(images);
	for (int p = 0; p < j; p++) //for문을 통하여 filters안에 있는 데이터들을 해제시킨다.
	{
		for (int a = 0; a < (filters[p]->H); a++)
		{
			free(filters[p]->data[a]);
		}
		free(filters[p]->data);
		free(filters[p]);
	}
	free(filters);
}
