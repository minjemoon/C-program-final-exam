#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // C 표준 유틸리티 함수들을 모아놓은 헤더파일 (rand 사용을 위함)

void randNum(int maxnumber); // 난수 발생 함수
void readFile(char readfile[]); // 파일 읽는 함수
void compareNum(int lotto[], int mylotto[]); // 로또 당첨 여부 확인

char fname[100]; // 파일 경로
int type, random_num, lotto[6], mylotto[6]; 
// type(로또 유형 = 최대 숫자), random_num(난수), lotto(난수 6개), mylotto(파일속 숫자 6개)

int main(void) {
	printf("로또 결과 저장 경로를 입력하세요: "); // 파일 경로 입력받음
	gets_s(fname, 100); // 입력된 파일 경로 fname에 저장
	readFile(fname); // 파일 읽기

	printf("로또 유형을 입력하세요(숫자를입력하세요): "); // 최대 숫자를 입력받음
	scanf("%d", &type); // type 변수에 할당
	randNum(type); // 난수 생성

	compareNum(lotto, mylotto); // 생성된 난수 6개와 파일 속 숫자 6개를 비교
}

/*
함수명: randNum
기능: 중복되지 않는 난수 6개 생성
- 매개변수
	1. maxnumber = 사용자가 입력한 로또 유형(최대 숫자)
*/
void randNum(int maxnumber) {
	int i, count = 0; // 난수 중복 체크와 할당을 위한 변수 
	srand(202112); // seed 값을 202112로 설정하여 난수식 결정 
				   // seed 값이 안 정해졌을 경우 자동으로 1로 설정됨
	while (1) {
		random_num = rand() % maxnumber + 1; // 1을 더해 rand() % type + 1 = 1 ~ type 까지의 난수 생성
											 // 1을 더하지 않은 경우 rand() % type = 0 ~ (type - 1)까지의 난수 생성

		/* 중복된 수 있는지 검사하는 반복문 */
		for (i = 0; i < count; i++) { // 이미 생성된 개수만큼만 중복됬는지 검사
			if (lotto[i] == random_num) { // 이미 나왔던 번호인지 검사 (중복 체크)
				break;  // 중복된 경우 for문 종료
			}			// 중복이 되기 때문에 i 값이랑 count 값이랑 다르게 됨
		}
		if (count == i) { // 중복되지 않은 경우에만 count번째 인덱스에 난수 할당
			lotto[count] = random_num;
			count++; // 값이 들어왔음으로 count를 1 증가
		}
		if (count == 6) { // count가 6이 되는 경우 while문 종료
			break;		  // 숫자를 6개만 뽑아야 하기 때문
		}
	}

	printf("이번주차 당첨번호는: ");
	for (int j = 0; j < 6; j++) {
		printf("%d ", lotto[j]); // 생성된 6개의 숫자 출력
	}
	printf("\n"); 
}

/*
함수명: readFile
기능: 파일에서 6개의 숫자를 읽어옴
- 사용된 매개변수
	1. filename = 파일경로(파일명)
*/
void readFile(char filename[]) {
	FILE* fp = NULL; // FILE을 가리키는 포인터 fp 선언
	fp = fopen(filename, "r"); // 읽기 모드로 파일을 열음 (파일이 존재하지 않을 경우 오류 발생)

	if (fp == NULL) {// 파일이 없는 경우
		printf("파일 열기 실패\n");
		printf("해당되는 파일이 없습니다. 프로그램을 종료합니다.\n");
		exit(1); // 프로그램 종료
	}
	else { // 파일이 존재하는 경우
		char buf1[20], buf2[20], buf3[20], buf4[20]; // 앞쪽에 있는 단어를 받는 변수
		int a, b, c, d, e, f; // 6개의 숫자를 받는 변수

		fscanf(fp, "%s %s %s %s %d %d %d %d %d %d", buf1, buf2, buf3, buf4, &a, &b, &c, &d, &e, &f); // 형식에 맞게 단어를 출력

		/* mylotto 리스트에 파일에서 읽은 숫자 6개 할당 */
		mylotto[0] = a;
		mylotto[1] = b;
		mylotto[2] = c;
		mylotto[3] = d;
		mylotto[4] = e;
		mylotto[5] = f;	
	}
	fclose(fp);	// 파일 닫기
}

/*
함수명: compareNum
기능: lotto와 mylotto를 비교하여 당첨 여부 출력
- 매개변수
	1. lotto = 생성한 난수 6개
	2. mylotto = 파일에서 읽어온 숫자 6개
*/
void compareNum(int lotto[], int mylotto[]) {
	int result[6], sum = 0; // 당첨 확인용 변수

	/* lotto와 mylotto에 있는 수들을 비교하는 반복문
	   lotto의 i 인덱스에 있는 값과 mylotto의 j 인덱스에 있는 값이 같은 경우
	   result의 i 인덱스에 1을 할당함 => result 리스트에 요소의 합이 6이 된다면 비교한 숫자가 전부 일치함*/
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (lotto[i] == mylotto[j]) { 
				result[i] = 1; 
			}
		}
	}
	for (int i = 0; i < 6; i++) {
		sum += result[i]; // result 리스트에 요소 합 계산
	}

	printf("고객님의 번호는 : ");
	for (int i = 0; i < 6; i++) {
		printf("%d ", mylotto[i]); // 파일에서 읽어 온 숫자 6개 출력
	}
	printf("입니다\n");

	if (sum == 6) { // result 리스트에 요소 합이 6인 경우
		printf("축하합니다 당첨입니다");
	}
	else { // result 리스트에 요소 합이 6이 아닌 경우
		printf("아쉽습니다 낙첨입니다");
	}
}