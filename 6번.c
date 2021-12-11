#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // C 표준 유틸리티 함수들을 모아놓은 헤더파일 (rand 사용을 위함)
#include <time.h> // rand함수 초기화를 위함 - seed 설정

void randNum(int maxnumber, int runtimes); // 난수 발생 함수
void statistics(int statmaxnum, int n[], int statlist[]); // 로또 수행횟수에 대한 통계내는 함수

int type, runtime, random_num, lotto[6], stats[500] = {0,};
// type(로또 유형 = 최대 숫자), runtime(수행 횟수), random_num(난수), lotto(난수 6개), stats(통계자료스택) -> 임의로 크기 500 설정

int main(void) {
	printf("로또 유형을 입력하세요(숫자를입력하세요): "); // 최대 숫자를 입력받음
	scanf("%d", &type); // type 변수에 할당

	printf("로또 수행 횟수를 입력하세요(숫자를입력하세요): "); // 로또 수행할 횟수 입력받음
	scanf("%d", &runtime); // runtime 변수에 할당 

	randNum(type, runtime); // 난수 생성
	statistics(type, runtime, stats); // 통계 자료 출력
}

/*
함수명: randNum
기능: 중복되지 않는 난수 6개를 로또 수행 횟수만큼 생성
- 매개변수
	1. maxnumber = 사용자가 입력한 로또 유형(최대 숫자)
	2. runtimes = 로또 수행 횟수
*/
void randNum(int maxnumber, int runtimes) {
	int tnumber = 1; // tnumber(로또 수행 횟수 확인용 변수)
	srand((unsigned int)time(NULL)); // rand 함수에 무작위 시드값 설정 , time(NULL)로 1초마다 다른 시드값 호출 가능

	while (tnumber <= runtimes) { // 로또 수행횟수만큼 반복문 실행
		int i, count = 0; // i & count(난수 중복과 할당을 위한 변수)
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

		/* 아래 주석으로 된 코드 실행시 생성되는 숫자 확인 가능 */
		//printf("선택된 번호는 다음과 같습니다: ");
		//for (int j = 0; j < 6; j++) {
		//	printf("%d ", lotto[j]); // 생성된 6개의 숫자 출력
		//}
		//printf("\n");
		
		/* 생성된 숫자와 똑같은 인덱스에 값을 1씩 추가*/
		for (int j = 1; j <= type; j++) {
			for (int k = 0; k < 6; k++) {
				if (j == lotto[k]) { // 생성된 숫자와 인덱스가 같은 경우
					stats[j] += 1;  // 해당 인덱스에 1 더함
				}
			}
		}
		tnumber++; // 수행횟수 1씩 증가
	}
}

/*
함수명: statistics
기능: 로또를 n회 수행한 결과의 통계를 출력
- 매개변수
	1. statmaxnum = 로또 유형(스택의 크기)
	2. n = 로또 수행 횟수
	3. statlist = 생성된 숫자에 횟수 통계 스택
*/
void statistics(int statmaxnum, int n, int statlist[]) {
	int max = 0; // max(가장 많이 나온 횟수 받는 변수)
	
	/* 로또 n회 수행 결과 출력하는 반복문 */
	printf("로또를 %d회 수행한 결과 통계입니다\n", n);
	for (int j = 1; j <= statmaxnum; j++) {
		printf("%d은 %d번 나왔습니다\n", j, stats[j]); 
	}

	/* 로또를 n회 수행하면서 가장 많이 출현한 숫자를 출력하는 반복문 */
	printf("가장 많이 출현한 숫자는 ");
	for (int j = 1; j <= statmaxnum; j++) { // 가장 많이 나온 횟수 받기
		if (max < stats[j]) {
			max = stats[j];
		}
	}

	for (int j = 1; j <= statmaxnum; j++) {
		if (max == stats[j]) {
			printf("%d ", j); // 가장 많이 나온 수 (공동 1등 모두 출력)
		}
	}
	printf("입니다");
}