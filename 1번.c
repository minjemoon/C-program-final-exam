#define _CRT_SECURE_NO_WARNINGS // 비쥬얼 스튜디오에서 scanf 함수 사용을 위한 경고 무시
#include <stdio.h> 

void encrypt(char plaintext[], int shift); // 암호화 함수
void createFile(char ciphertext[], int shift); // 파일 생성하는 함수

char plain[50]; // 원본 문자열
char cipher[50]; // 암호화된 문자열
char fname[100] = "C:\\Temp\\result.txt"; // 파일 경로 및 이름

int main(void) {
	int shift; // 암호키 변수(shift) & 모드 선택 변수(mode) 선언

	printf("암호키를 입력하세요(숫자1~9): ");
	scanf("%d", &shift); // 입력된 암호키 shift에 저장

	getchar(); // scanf의 남은 버퍼(\n)를 버림 -> gets_s 사용하기 위함
	
	printf("평문을 입력하세요: ");
	gets_s(plain, 50); // 입력된 평문 plain에 저장

	encrypt(plain, shift); // 평문(plain)을 암호키(shift)에 해당되게 암호화
	createFile(cipher, shift); //암호키(shift)와 암호문(cipher) txt 파일에 저장
}

/*
함수명 : encrypt
기능: 평문을 암호키만큼 이동하여 암호화를 하는 함수
- 사용된 매개변수
	1. plaintext = 평문
	2. shift = 암호키
*/
void encrypt(char plaintext[], int shift) { 

	/* plaintext[i]가 소문자인 경우 shift 만큼 더해서 암호화 진행
		a~z = 97~122(ASCII코드)  -> plaintext[i]에서 a를 빼면 a~z = 0~25의 범위를 갖게 됨
		이후 %(나머지연산)을 통해 알파벳 범위를 넘어가는 것을 방지할 수 있음
		임의로 변경한 범위를 원상태로 복구하기 위해 다시 a를 더함
	*/
	for (int i = 0; plaintext[i] != '\0'; i++) {
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
			cipher[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
		}
		else { // 알파벳 소문자가 아닌 것들은 원본 유지
			cipher[i] = plaintext[i]; 
		}
	}

	printf("암호화된 문자열: %s \n", cipher);
}

/*
함수명: createFile
기능: 암호키와 암호문을 txt 파일에 저장
- 사용된 매개변수
	1. ciphertext = 암호문
	2. shift = 암호키
*/
void createFile(char ciphertext[], int shift) {
	FILE* fp = NULL; // FILE을 가리키는 포인터 fp 선언
	fp = fopen(fname, "w"); // 쓰기 모드로 새로운 파일을 생성(이미 존재하는 경우 기존 내용 삭제)

	if (fp == NULL) {
		printf("파일 열기 실패\n");
		exit(1);
	}
	else {
		char buf1[10]; // 암호키를 문자로 바꾸기 위함
		itoa(shift, buf1, 10); // 암호키를 문자로 변환

		/* txt 파일에 암호키, 암호문 입력*/
		fputs("key", fp);
		fputc(' ', fp);
		fputs(buf1, fp); // 파일에 암호키 입력
		fputc('\n', fp);
		fputs("ciphertext", fp);
		fputc(' ', fp);
		fputs(cipher, fp); // 파일에 암호문 입력
	}
	fclose(fp);	// 파일 닫기
}