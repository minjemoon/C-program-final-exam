#define _CRT_SECURE_NO_WARNINGS // ����� ��Ʃ������� scanf �Լ� ����� ���� ��� ����
#include <stdio.h> 

void encrypt(char plaintext[], int shift); // ��ȣȭ �Լ�
void createFile(char ciphertext[], int shift); // ���� �����ϴ� �Լ�

char plain[50]; // ���� ���ڿ�
char cipher[50]; // ��ȣȭ�� ���ڿ�
char fname[100] = "C:\\Temp\\result.txt"; // ���� ��� �� �̸�

int main(void) {
	int shift; // ��ȣŰ ����(shift) & ��� ���� ����(mode) ����

	printf("��ȣŰ�� �Է��ϼ���(����1~9): ");
	scanf("%d", &shift); // �Էµ� ��ȣŰ shift�� ����

	getchar(); // scanf�� ���� ����(\n)�� ���� -> gets_s ����ϱ� ����
	
	printf("���� �Է��ϼ���: ");
	gets_s(plain, 50); // �Էµ� �� plain�� ����

	encrypt(plain, shift); // ��(plain)�� ��ȣŰ(shift)�� �ش�ǰ� ��ȣȭ
	createFile(cipher, shift); //��ȣŰ(shift)�� ��ȣ��(cipher) txt ���Ͽ� ����
}

/*
�Լ��� : encrypt
���: ���� ��ȣŰ��ŭ �̵��Ͽ� ��ȣȭ�� �ϴ� �Լ�
- ���� �Ű�����
	1. plaintext = ��
	2. shift = ��ȣŰ
*/
void encrypt(char plaintext[], int shift) { 

	/* plaintext[i]�� �ҹ����� ��� shift ��ŭ ���ؼ� ��ȣȭ ����
		a~z = 97~122(ASCII�ڵ�)  -> plaintext[i]���� a�� ���� a~z = 0~25�� ������ ���� ��
		���� %(����������)�� ���� ���ĺ� ������ �Ѿ�� ���� ������ �� ����
		���Ƿ� ������ ������ �����·� �����ϱ� ���� �ٽ� a�� ����
	*/
	for (int i = 0; plaintext[i] != '\0'; i++) {
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
			cipher[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
		}
		else { // ���ĺ� �ҹ��ڰ� �ƴ� �͵��� ���� ����
			cipher[i] = plaintext[i]; 
		}
	}

	printf("��ȣȭ�� ���ڿ�: %s \n", cipher);
}

/*
�Լ���: createFile
���: ��ȣŰ�� ��ȣ���� txt ���Ͽ� ����
- ���� �Ű�����
	1. ciphertext = ��ȣ��
	2. shift = ��ȣŰ
*/
void createFile(char ciphertext[], int shift) {
	FILE* fp = NULL; // FILE�� ����Ű�� ������ fp ����
	fp = fopen(fname, "w"); // ���� ���� ���ο� ������ ����(�̹� �����ϴ� ��� ���� ���� ����)

	if (fp == NULL) {
		printf("���� ���� ����\n");
		exit(1);
	}
	else {
		char buf1[10]; // ��ȣŰ�� ���ڷ� �ٲٱ� ����
		itoa(shift, buf1, 10); // ��ȣŰ�� ���ڷ� ��ȯ

		/* txt ���Ͽ� ��ȣŰ, ��ȣ�� �Է�*/
		fputs("key", fp);
		fputc(' ', fp);
		fputs(buf1, fp); // ���Ͽ� ��ȣŰ �Է�
		fputc('\n', fp);
		fputs("ciphertext", fp);
		fputc(' ', fp);
		fputs(cipher, fp); // ���Ͽ� ��ȣ�� �Է�
	}
	fclose(fp);	// ���� �ݱ�
}