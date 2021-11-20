# -*- coding: utf-8 -*-
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

void image_load(CUBIC **images, int i) //이미지 파일을 불러들이는 함수이다.
{
	images[i] = (CUBIC*)malloc(sizeof(CUBIC));
	char fname[100] = { '\0' };
	printf("Enter image filename: ");
	scanf("%s", fname);

	FILE *infile;
	infile = fopen(fname, "r");
	if (infile == NULL) //파일이 없다면 ERROR을 띄운다.
	{
		printf("Could not open file\n");
		return;
	}

	int k = 0;
	while (fname[k] != '\0') //k는 불러들인 이름의 맨 끝보다 한칸 더 까지의 칸 수를 나타내게 된다.
	{
		k++;
	}
	fname[k - 1] = '\0'; //.ppm을 지우는 역할을 한다.
	fname[k - 2] = '\0';
	fname[k - 3] = '\0';
	fname[k - 4] = '\0';
	for (int t = 0; t < k - 1; t++)
		images[i]->name[t] = fname[t];
	char P;
	int integ;
	fscanf(infile, "%c%d %d %d %d", &P, &images[i]->C, &images[i]->W, &images[i]->H, &integ); //파일에서 C, W, H 값을 받아들인다.

	images[i]->data = (float***)malloc(sizeof(float**) * (images[i]->H)); //필요한 만큼의 데이터를 위해 동적할당을 한다.
	{
		for (int a = 0; a < (images[i]->H); a++)
		{
			images[i]->data[a] = (float**)malloc(sizeof(float*) * (images[i]->W));
			for (int b = 0; b < images[i]->W; b++)
			{
				images[i]->data[a][b] = (float*)malloc(sizeof(float) * (images[i]->C));
			}
		}
	}

	for (int a = 0; a < (images[i]->H); a++) //동적할당 한 공간에 데이터 값을 넣는다.
	{
		for (int b = 0; b < (images[i]->W); b++)
		{
			for (int c = 0; c < (images[i]->C); c++)
			{
				fscanf(infile, "%f", &(images[i]->data[a][b][c]));
			}
		}
	}
	images[i]->is_normalized = 0; //처음에 is_normalized값은 0이다.
	fclose(infile);
}

void show_il(CUBIC **images, int i)
{
	for (int a = 0; a < i; a++)
	{
		if (images[a]->is_normalized == 0)
		{
			int t = 0;
			printf("%d. ", a);
			while (images[a]->name[t] != '\0') //파일의 이름을 출력해준다.
			{
				printf("%c", images[a]->name[t]);
				t++;
			}
			printf(" [H: %d, W: %d, C:%d]\n", images[a]->H, images[a]->W, images[a]->C);
		}
		else
		{
			int t = 0;
			printf("%d. ", a);
			while (images[a]->name[t] != '\0')
			{
				printf("%c", images[a]->name[t]);
				t++;
			}
			printf(" [H: %d, W: %d, C:%d] - normalized\n", images[a]->H, images[a]->W, images[a]->C); // normalized 된 경우 맨 뒤에 -normalized가 붙는다.
		}
	}
}

void show_fl(CUBIC **filters, int j)
{
	for (int i = 0; i < j; i++)
	{
		int t = 0;
		printf("%d. ", i);
		while (filters[i]->name[t] != '\0') //필터의 이름을 출력해준다.
		{
			printf("%c", filters[i]->name[t]);
			t++;
		}
		printf(" [H: %d, W: %d, C:%d]\n", filters[i]->H, filters[i]->W, filters[i]->C);
	}
}

void image_save(CUBIC **images, int i)
{
	int num;
	char ofname[100];
	show_il(images, i);
	printf("Enter the number of image to save: ");
	scanf("%d", &num);

	if (num < 0 || num >= i) //해당되는 인덱스 이외의 값을 입력하면 ERROR을 띄운다.
	{
		printf("ERROR print right number\n");
		return;
	}
	printf("Enter filename for save image : ");
	scanf("%s", ofname);

	FILE *outfile;
	outfile = fopen(ofname, "w");
	fprintf(outfile, "P%d %d %d 255\n", images[num]->C, images[num]->W, images[num]->H);
	for (int a = 0; a < (images[num]->H); a++) //동적할당된 공간에 있는 데이터 값을 int형으로 입력한다.
	{
		for (int b = 0; b < (images[num]->W); b++)
		{
			for (int c = 0; c < (images[num]->C); c++)
			{
				if (images[num]->data[a][b][c] < 0)
				{
					images[num]->data[a][b][c] = 0;
				}
				else if (images[num]->data[a][b][c] > 255)
				{
					images[num]->data[a][b][c] = 255;
				}
				fprintf(outfile, "%d ", (int)images[num]->data[a][b][c]);
			}
		}
	}
	fclose(outfile);
}

void filter_load(CUBIC **filters, int j)
{
	filters[j] = (CUBIC*)malloc(sizeof(CUBIC));
	char fname[100] = { '\0' };
	printf("Enter filter filename: ");
	scanf("%s", fname);

	FILE *infile;
	infile = fopen(fname, "r");
	if (infile == NULL)
	{
		printf("Could not open file\n");
		return;
	}

	int k = 0;
	while (fname[k] != '\0') //filter의 이름보다 1이 많은 수가 k이다.
	{
		k++;
	}
	fname[k - 1] = '\0'; //맨 뒤의 .ppm을 제거하는 역할을 한다.
	fname[k - 2] = '\0';
	fname[k - 3] = '\0';
	fname[k - 4] = '\0';
	for (int t = 0; t < k - 1; t++)
		filters[j]->name[t] = fname[t];
	char P;
	int integ;
	fscanf(infile, "%c%d %d %d %d", &P, &filters[j]->C, &filters[j]->W, &filters[j]->H, &integ); //filter의 C, H, W값을 입력받는다.

	filters[j]->data = (float***)malloc(sizeof(float**) * (filters[j]->H)); //filter에 필요한 데이터를 위하여 동적할당 해준다.
	{
		for (int a = 0; a < (filters[j]->H); a++)
		{
			filters[j]->data[a] = (float**)malloc(sizeof(float*) * (filters[j]->W));
			for (int b = 0; b < filters[j]->W; b++)
			{
				filters[j]->data[a][b] = (float*)malloc(sizeof(float) * (filters[j]->C));
			}
		}
	}

	for (int a = 0; a < (filters[j]->H); a++) // 동적할당 해준 메모리에 데이터 값을 입력한다.
	{
		for (int b = 0; b < (filters[j]->W); b++)
		{
			for (int c = 0; c < (filters[j]->C); c++)
			{
				fscanf(infile, "%f", &(filters[j]->data[a][b][c]));
			}
		}
	}
	fclose(infile);
}

void image_remove(CUBIC **images, int i)
{
	int num;
	show_il(images, i);
	printf("Enter the number of image to remove: ");
	scanf("%d", &num);
	if (num < 0 || num >= i) //해당되는 인덱스 이외의 값을 입력하였을 경우 ERROR을 띄운다.
	{
		printf("ERROR print right number\n");
		return;
	}

	move_image_index(images, i, num);

	for (int a = 0; a < (images[i - 1]->H); a++) //데이터를 동적할당 해준 것을 해제시킨다.
	{
		for (int b = 0; b < (images[i - 1]->W); b++)
		{
			free(images[i - 1]->data[a][b]);
		}
		free(images[i - 1]->data[a]);
	}
	free(images[i - 1]->data);
	free(images[i - 1]);
}

void filter_remove(CUBIC **filters, int j)
{
	int num;
	show_fl(filters, j);
	printf("Enter the number of filter to remove: ");
	scanf("%d", &num);
	if (num < 0 || num >= j) //해당되는 인덱스 이외의 값을 입력하였을 경우 ERROR을 띄운다.
	{
		printf("ERROR print right number\n");
		return;
	}

	move_filter_index(filters, j, num);

	for (int a = 0; a < (filters[j - 1]->H); a++) //데이터를 동적할당 해준 것을 해제시킨다.
	{
		for (int b = 0; b < (filters[j - 1]->W); b++)
		{
			free(filters[j - 1]->data[a][b]);
		}
		free(filters[j - 1]->data[a]);
	}
	free(filters[j - 1]->data);
	free(filters[j - 1]);
}

void move_image_index(CUBIC **images, int i, int num)
{
	for (int a = num; a < i - 1; a++) //temp를 하나 더 선언하여서 swap기술을 이용하여 제거된 부분부터 그 이후의 파일들이 차례대로 swap되어 인덱스가 당겨지게 된다.
	{
		CUBIC *temp;
		temp = images[a];
		images[a] = images[a + 1];
		images[a + 1] = temp;
	}
}

void move_filter_index(CUBIC **filters, int j, int num)
{
	for (int a = num; a < j - 1; a++) //temp를 하나 더 선언하여서 swap기술을 이용하여 제거된 부분부터 그 이후의 파일들이 차례대로 swap되어 인덱스가 당겨지게 된다.
	{
		CUBIC *temp;
		temp = filters[a];
		filters[a] = filters[a + 1];
		filters[a + 1] = temp;
	}
}

void normalize(CUBIC **images, int i)
{
	int num;
	show_il(images, i);
	printf("Enter the number of image to normalize: ");
	scanf("%d", &num);
	if (num < 0 || num >= i) //인덱스 이외의 값을 입력하면 ERROR을 띄운다.
	{
		printf("ERROR print right number\n");
		return;
	}
	if (images[num]->is_normalized == 1) //정규화 된 파일을 다시 정규화 시키려고 하면 ERROR을 띄운다.
	{
		printf("ERROR already normalized\n");
		return;
	}
	images[num]->is_normalized = 1;
	for (int a = 0; a < (images[num]->H); a++) //정규화 하는 계산을 해준다.
	{
		for (int b = 0; b < (images[num]->W); b++)
		{
			for (int c = 0; c < (images[num]->C); c++)
			{
				images[num]->data[a][b][c] = images[num]->data[a][b][c] / 128 - 1;
			}
		}
	}
}

void denormalize(CUBIC **images, int i)
{
	int num;
	show_il(images, i);
	printf("Enter the number of image to denormalize: ");
	scanf("%d", &num);
	if (num < 0 || num >= i) //인덱스 이외의 값을 입력하면 ERROR을 띄운다.
	{
		printf("ERROR print right number\n");
		return;
	}
	if (images[num]->is_normalized == 0) //역정규화 된 파일(정규화 하지 않은 파일)을 다시 정규화 시키려고 하면 ERROR을 띄운다.
	{
		printf("ERROR already denormalized\n");
		return;
	}
	images[num]->is_normalized = 0;
	for (int a = 0; a < (images[num]->H); a++) //역정규화 하는 계산을 해준다.
	{
		for (int b = 0; b < (images[num]->W); b++)
		{
			for (int c = 0; c < (images[num]->C); c++)
			{
				images[num]->data[a][b][c] = 128 * ((images[num]->data[a][b][c]) + 1);
			}
		}
	}
}

void image_convolution(CUBIC **images, CUBIC **filters, int i, int j)
{
	if (i == 0)
	{
		printf("ERROR NO IMAGE FILE\n");
		return;
	}
	else if (j == 0)
	{
		printf("ERROR NO FILTER FILE\n");
		return;
	}
	int ic, fc;
	int rh, rw;
	float sum = 0;
	show_il(images, i);
	printf("Enter the number of image to convolve: ");
	scanf("%d", &ic);
	if (ic < 0 || ic >= i) //해당되는 인덱스 이외의 값을 입력하면 ERROR을 띄운다.
	{
		printf("ERROR print right number\n");
		return;
	}
	show_fl(filters, j);
	printf("Enter the number of filter to convolve: ");
	scanf("%d", &fc);
	if (fc < 0 || fc >= j) //해당되는 인덱스 이외의 값을 입력하면 ERROR을 띄운다.
	{
		printf("ERROR print right number\n");
		return;
	}

	rh = images[ic]->H - filters[fc]->H + 1;
	rw = images[ic]->W - filters[fc]->W + 1;

	images[i] = (CUBIC*)malloc(sizeof(CUBIC));

	images[i]->data = (float***)malloc(sizeof(float**) * rh); //새로운 데이터 값을 위하여 동적할당 해준다.
	{
		for (int a = 0; a < rh; a++)
		{
			images[i]->data[a] = (float**)malloc(sizeof(float*) * rw);
			for (int b = 0; b < rw; b++)
			{
				images[i]->data[a][b] = (float*)malloc(sizeof(float) * (images[ic]->C));
			}
		}
	}

	for (int c = 0; c < 3; c++) //convolution연산을 진행한다.
	{
		for (int arh = 0; arh < rh; arh++)
		{
			for (int arw = 0; arw < rw; arw++)
			{
				for (int h = 0; h < filters[fc]->H; h++)
				{
					for (int w = 0; w < filters[fc]->W; w++)
					{
						sum += (images[ic]->data[arh + h][arw + w][c]) * (filters[fc]->data[h][w][0]);
						images[i]->data[arh][arw][c] = sum;
					}
				}
				sum = 0;
			}
		}
	}
	if (images[ic]->is_normalized == 0) //기존의 파일의 is_normalized가 0이면 컨볼루젼한 파일의 is_normalized값도 0이다.
	{
		images[i]->is_normalized = 0;
	}
	else //기존의 파일의 is_normalized가 1이면 컨볼루젼한 파일의 is_normalized값도 1이다.
	{
		images[i]->is_normalized = 1;
	}

	images[i]->H = rh;
	images[i]->W = rw;
	images[i]->C = images[ic]->C;

	char* new_name;
	char* real_name;
	char icname[100];
	char* copy_name = strcpy(icname, images[ic]->name); //이미지의 이름을 icname으로 복사한다.
	char bar[] = "_";
	new_name = strcat(icname, bar);//이미지의 이름과 _를 연결시킨다.
	real_name = strcat(new_name, filters[fc]->name);//이미지의 이름과 _를 연결시킨 것을 filter의 이름과 연결시킨다.

	int leng;
	leng = strlen(images[ic]->name) + strlen(filters[fc]->name) + 1; //컨볼루젼한 파일의 이름 길이를 나타낸다.

	for (int t = 0; t < leng; t++)
		images[i]->name[t] = real_name[t];
	images[i]->name[leng] = NULL;
}
