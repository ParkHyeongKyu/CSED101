# -*- coding: utf-8 -*-
#include <stdio.h>

int main(void)
{
	char big; // 입력받을 대문자 값 변수 설정
	printf("대문자 값을 입력해주십시오 :  "); // "대문자 값을 입력해주십시오 :  " 화면에 표시되도록 함
	scanf("%c", &big); // 입력값 받기
	char sum = big + 32; // 소문자 값 변수 설정
	printf("소문자 값은 다음과 같습니다 : %c\n", sum); // "소문자 값은 다음과 같습니다 :   " 화면에 표시되도록 함
	int letter = sum - 96; // 소문자 순서 변수 설정
	printf("알파벳 위치 순서는 다음과 같습니다 : %d\n", letter); //"알파벳 위치 순서는 다음과 같습니다 :  " 화면에 표시되도록 함
	return 0;
} //main
