#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // C 표준 유틸리티 함수들을 모아놓은 헤더파일 (rand 사용을 위함)

void randNum(int maxnumber); // 난수 발생 함수
void createFile(int numberlist[]); // 파일 생성하는 함수

char fname[100] = "C:\\Temp\\lotto.txt"; // 파일 경로 및 이름
int type, random_num, lotto[6]; // type = 로또 유형(최대 숫자), random_num(난수), lotto(난수 6개)

int main(void) {
	
	int i, count = 0; // 난수 중복과 할당을 위한 변수 

	printf("로또 유형을 입력하세요(숫자를입력하세요): "); // 최대 숫자를 입력받음
	scanf("%d", &type); // type 변수에 할당

	randNum(type);
	createFile(lotto);
}

/*
함수명: randNum
기능: 중복되지 않는 난수 6개 생성
- 매개변수
	1. maxnumber = 사용자가 입력한 로또 우형(최대 숫자)
*/

void randNum(int maxnumber) {
	int i, count = 0; // 난수 중복과 할당을 위한 변수 

	while (1) {
		random_num = rand() % maxnumber + 1; // 1을 더해 rand() % type + 1 = 1 ~ type 까지의 난수 생성
										// 1을 더하지 않은 경우 rand() % type = 0 ~ (type - 1)까지의 난수 생성
		
		/* 중복된 수 있는지 검사하는 반복문 */
		for (i = 0; i < count; i++) { // 이미 생성된 개수만큼만 중복된지 검사
			if (lotto[i] == random_num) { // 이미 나온 번호인지 검사 (중복 체크)
				break;  // 중복된 경우 for문 종료
			}			// 중복이 되기 때문에 i 값이랑 count 값이랑 다르게 됨
		}
		if (count == i) { // 중복되지 않은 경우에만 count번째 인덱스에 할당
			lotto[count] = random_num;
			count++; // 값이 들어왔음으로 count를 1 증가
		}
		if (count == 6) { // count가 6이 되는 경우 while문 종료
			break;		  // 숫자를 6개만 뽑아야 하기 때문
		}
	}

	printf("선택된 번호는 다음과 같습니다: ");
	for (int j = 0; j < 6; j++) {
		printf("%d ", lotto[j]); // 생성된 6개의 숫자 출력
	}
}

/*
함수명: createFile
기능: 생성된 난수 6개를 txt 파일에 저장
- 사용된 매개변수
	1. numberlist = 난수 리스트
*/
void createFile(int numberlist[]) {
	FILE* fp = NULL; // FILE을 가리키는 포인터 fp 선언
	fp = fopen(fname, "w"); // 쓰기 모드로 새로운 파일을 생성(이미 존재하는 경우 기존 내용 삭제)

	if (fp == NULL) {
		printf("파일 열기 실패\n");
		exit(1);
	}
	else {
		int buf1;
		char buf2[10];

		/* txt 파일에 생성된 6개의 난수 입력 */
		fputs("선택된 번호는 다음과 같습니다: ", fp);
		for (int j = 0; j < 6; j++) {
			buf1 = numberlist[j];		   
			snprintf(buf2,10, "%d", buf1); //생성된 난수를 문자열로 변경해서 복사
			fputs(buf2, fp); //난수 입력
			fputc(' ', fp);
		}
	}
	fclose(fp);	// 파일 닫기
}