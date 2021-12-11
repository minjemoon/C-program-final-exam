#define _CRT_SECURE_NO_WARNINGS // 비쥬얼 스튜디오에서 scanf 함수 사용을 위한 경고 무시
#include <stdio.h> 
#include <string.h>

void decrypt(char filename[]); // 복호화 함수

char plain[50]; // 원본 문자열
char cipher[50]; // 암호화된 문자열
char fname[100]; // 파일 경로


int main(void) {
	printf("파일의 경로를 입력하세요: ");
	gets_s(fname, 100); // 입력된 파일 경로 fname에 저장
	decrypt(fname);
}

/*
함수명 : decrypt
기능: 암호문을 암호키만큼 이동하여 복호화하는 함수
- 사용된 매개변수
	1. 
*/
void decrypt(char filename[]) {
	int shift; // 암호키

	FILE* fp = NULL; // FILE을 가리키는 포인터 fp 선언
	fp = fopen(filename, "r"); // 읽기 모드로 파일을 열음 (파일이 존재하지 않을 경우 오류 발생)

	if (fp == NULL) {// 파일이 없는 경우
		printf("파일 열기 실패\n");
		printf("복호화할 파일이 없습니다. 프로그램을 종료합니다.\n");
		exit(1); // 프로그램 종료
	}
	else { // 파일이 존재하는 경우
		char buf1[20], buf2[100], buf3[10], buf4[100]; // 파일을 읽기 위한 임시 변수
		char space[10] = " ";

		fgets(buf1, 20, fp);
		buf1[strlen(buf1) - 1] = '\0'; // 개행문자 제거 
		fgets(buf2, 50, fp);

		puts(buf1); // 첫번째줄
		puts(buf2); // 두번째줄

		char* temp1 = strtok(buf1, " "); // 공란 기준으로 토큰 분리 
		while (temp1 != NULL) {
			strcpy(buf3, temp1);
			temp1 = strtok(NULL, " ");
		}

		shift = atoi(buf3); // 문자를 정수로 변환
		printf("%d\n", shift); // 정수 맞음 (확인 완료)

		strncpy(cipher, buf2 + 11, sizeof(buf2));
		printf("%s\n", cipher);
		
	}
	fclose(fp);	// 파일 닫기

	for (int i = 0; cipher[i] != '\0'; i++) {
		if (cipher[i] >= 'a' && cipher[i] <= 'z') {
			plain[i] = (cipher[i] - 'a' - shift) % 26 + 'a';
		}
		else { // 소문자 알파벳이 아닌 것들에 대해서 원본 유지
			plain[i] = cipher[i];
		}
	}

	printf("복호화된 문자열: %s \n", plain);
}
