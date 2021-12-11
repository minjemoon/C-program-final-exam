#define _CRT_SECURE_NO_WARNINGS // 비쥬얼 스튜디오에서 scanf 함수 사용을 위한 경고 무시
#include <stdio.h> 

void encrypt(char plaintext[], int shift); // 암호화 함수
void createFile(char ciphertext[], int shift); // 파일 생성하는 함수
void decrypt(char filename[]); // 복호화 함수

char plain[50]; // 원본 문자열
char cipher[50]; // 암호화된 문자열
char fname[100]; // 파일 경로 및 이름
int shift; // 암호키 변수(shift)

int main(void) {
	int mode; // 모드 선택 변수

	printf("암호화 모드, 복호화 모드를 선택하세요(암호화 = 1, 복호화 = 0): ");
	scanf("%d", &mode);

	if (mode == 1) { // 암호화 모드 선택

		printf("암호키를 입력하세요(숫자1~9): ");
		scanf("%d", &shift); // 입력된 암호키 shift에 저장

		getchar(); // scanf의 남은 버퍼(\n)를 버림 -> gets_s 사용하기 위함

		printf("평문을 입력하세요: ");
		gets_s(plain, 50); // 입력된 평문 plain에 저장

		encrypt(plain, shift); // 평문(plain)을 암호키(shift)에 해당되게 암호화
		createFile(cipher, shift); //암호키(shift)와 암호문(cipher) txt 파일에 저장
	}
	else if (mode == 0) { // 복호화 모드 선택
		getchar(); // 남은 버퍼(\n)를 버림 -> gets_s 사용하기 위함

		printf("파일의 경로를 입력하세요: ");
		gets_s(fname, 100); // 입력된 파일 경로 fname에 저장
		decrypt(fname); // 파일에서 암호키 암호문 읽고 복호화
	}
	else
		printf("선택지에 없는 번호입니다.");
	
}

/*
함수명 : encrypt
기능: 평문을 암호키만큼 이동하여 암호화를 하는 함수
- 사용된 매개변수
	1. plaintext = 평문
	2. shift = 암호키
*/
void encrypt(char plaintext[], int shift) {
	int i = 0;
	/* plaintext[i]가 소문자인 경우 shift 만큼 더해서 암호화 진행
		a~z = 97~122(ASCII코드)  -> plaintext[i]에서 a를 빼면 a~z = 0~25의 범위를 갖게 됨
		이후 %(나머지연산)을 통해 알파벳 범위를 넘어가는 것을 방지할 수 있음
		임의로 변경한 범위를 원상태로 복구하기 위해 다시 a를 더함
	*/
	while (plaintext[i] != '\0') {
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
			cipher[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
		}
		else { // 알파벳 소문자가 아닌 것들은 원본 유지
			cipher[i] = plaintext[i];
		}
		i++;
	}
	printf("암호화된 문자열: %s \n", cipher);
}


/*
함수명 : decrypt
기능: txt 파일을 읽어 암호키와 암호문을 얻고
	  암호문을 암호키만큼 이동하여 복호화하는 함수
- 사용된 매개변수
	1. filename = 파일경로(파일명)
*/
void decrypt(char filename[]) {
	int shift; // 암호키

	FILE* fp1 = NULL; // FILE을 가리키는 포인터 fp 선언
	fp1 = fopen(filename, "r"); // 읽기 모드로 파일을 열음 (파일이 존재하지 않을 경우 오류 발생)

	if (fp1 == NULL) {// 파일이 없는 경우
		printf("파일 열기 실패\n");
		printf("복호화할 파일이 없습니다. 프로그램을 종료합니다.\n");
		exit(1); // 프로그램 종료
	}
	else { // 파일이 존재하는 경우
		char buf1[20], buf2[100], buf3[10], buf4[100]; // 파일을 읽기 위한 임시 변수

		fgets(buf1, 20, fp1); // 첫 번째 줄 읽기
		buf1[strlen(buf1) - 1] = '\0'; // 개행문자 제거 
		fgets(buf2, 50, fp1); // 두 번째 줄 읽기 

		//puts(buf1); // 첫번째줄
		//puts(buf2); // 두번째줄

		char* temp1 = strtok(buf1, " "); // 공란 기준으로 토큰 분리 
		while (temp1 != NULL) { // 반복문을 통해 암호키 획득
			strcpy(buf3, temp1);  // 마지막 토큰을 buf3에 복사
			temp1 = strtok(NULL, " ");
		}

		shift = atoi(buf3); // 문자를 정수로 변환
		strncpy(cipher, buf2 + 11, sizeof(buf2)); // buf2 배열 cipher 배열에다 복사 (ciphertext )을 없애기 위해 11을 더함

	}
	fclose(fp1);	// 파일 닫기

	int i = 0;
	while (cipher[i] != '\0') { // null 값이 아닌 경우 계속
		if (cipher[i] >= 'a' && cipher[i] <= 'z') { // 소문자 범위인지 확인
			plain[i] = cipher[i] - shift; //암호키 만큼 왼쪽으로 이동함
			if (plain[i] < 'a') { // 알파벳 범위 벗어난 경우
				plain[i] += 26; // 알파벳 끝으로 회귀
			}
		}
		else { // 소문자 알파벳이 아닌 것들에 대해서 원본 유지
			plain[i] = cipher[i];
		}
		i++;
	}
	printf("복호화된 문자열: %s \n", plain);
}

/*
함수명: createFile
기능: 암호키와 암호문을 txt 파일에 저장
- 사용된 매개변수
	1. ciphertext = 암호문
	2. shift = 암호키
*/
void createFile(char ciphertext[], int shift) {
	char fname1[100] = "C:\\Temp\\result.txt";
	FILE *fp2; // FILE을 가리키는 포인터 fp 선언
	fp2 = fopen(fname1, "w"); // 쓰기 모드로 새로운 파일을 생성(이미 존재하는 경우 기존 내용 삭제)

	if (fp2 == NULL) {
		printf("파일 열기 실패\n");
		exit(1);
	}
	else {
		fprintf(fp2, "%s %d\n", "key", shift);
		fputs("ciphertext ", fp2);
		fputs(cipher, fp2);
	}
	fclose(fp2);	// 파일 닫기
}
