# -*- coding: utf-8 -*-
#include <stdio.h>

int main(void)
{
	int a, b, c, d, e, f, g, h;
	printf("운반 가능한 물의 양은? : "); //운반 가능한 물의 양은? :  을 출력해주도록 함
	scanf("%d", &a); // 이용자가 원하는 물의 양을 입력받음
	b = a / 29; // b는 29L의 물통 개수
	c = a - b * 29; // c는 29L의 물통을 채우고 남은 물의 양
	d = c / 11; // d는 11L의 물통 개수
	e = c - d * 11; // e는 11L의 물통을 채우고 남은 물의 양
	f = e / 3; // f는 3L의 물통 개수
	g = e - f * 3; // g는 1L의 물통 개수
	h = (b + d + f + g) * 1000; // 물통 개수에 따른 가격값
	printf("생수통 %d개, 약수통 %d개, 큰 물통 %d개, 작은 물통 %d개로 총 운반 비용은 %d원입니다.\n", b, d, f, g, h); // 마지막 결과값을 출력해주도록 함
	return 0;
} //main
