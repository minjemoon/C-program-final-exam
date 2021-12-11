#define _CRT_SECURE_NO_WARNINGS // ����� ��Ʃ������� scanf �Լ� ����� ���� ��� ����
#include <stdio.h> 
#include <string.h>

void decrypt(char ciphertext[], int shift); // ��ȣȭ �Լ�
void readFile(char readfile[]); // ���� �д� �Լ�

char plain[50]; // ���� ���ڿ�
char cipher[50]; // ��ȣȭ�� ���ڿ�
char fname[100]; // ���� ���
int shift; // ��ȣŰ

int main(void) {
	printf("������ ��θ� �Է��ϼ���: ");
	gets_s(fname, 100); // �Էµ� ���� ��� fname�� ����
	readFile(fname); // ���� �о� ��ȣŰ(shift)�� ��ȣ��(cipher) ȹ��
	decrypt(cipher, shift);
}

/*
�Լ��� : decrypt
���: ��ȣ���� ��ȣŰ��ŭ �̵��Ͽ� ��ȣȭ�ϴ� �Լ�
- ���� �Ű�����
	1. ciphertext = ��ȣ��
	2. shift = ��ȣŰ
*/
void decrypt(char ciphertext[], int shift) {
	for (int i = 0; ciphertext[i] != '\0'; i++) {
		if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
			plain[i] = (ciphertext[i] - 'a' - shift) % 26 + 'a';
		}
		else { // �ҹ��� ���ĺ��� �ƴ� �͵鿡 ���ؼ� ���� ����
			plain[i] = ciphertext[i];
		}
	}

	printf("��ȣȭ�� ���ڿ�: %s \n", plain);
}

/*
�Լ���: readFile
���: ��ȣŰ�� ��ȣ���� txt ���Ͽ� ����
- ���� �Ű�����
	1. ciphertext = ��ȣ��
	2. shift = ��ȣŰ
*/
void readFile(char filename[]) {
	FILE* fp = NULL; // FILE�� ����Ű�� ������ fp ����
	fp = fopen(filename, "r"); // �б� ���� ������ ���� (������ �������� ���� ��� ���� �߻�)
	
	if (fp == NULL) {// ������ ���� ���
		printf("���� ���� ����\n");
		printf("��ȣȰ ������ �����ϴ�. ���α׷��� �����մϴ�.\n");
		exit(1); // ���α׷� ����
	}
	else { // ������ �����ϴ� ���
		char buf1[20], buf2[100], buf3[10], buf4[100]; // ������ �ϱ� ���� �ӽ� ����

		fgets(buf1, 20, fp);
		buf1[strlen(buf1) - 1] = '\0'; // ���๮�� ���� 
		fgets(buf2, 50, fp);
		
		puts(buf1); // ù��°��
		puts(buf2); // �ι�°��

		char *temp1 = strtok(buf1, " "); // ���� �������� ��ū �и� 
		while (temp1 != NULL) {
			strcpy(buf3, temp1);
			temp1 = strtok(NULL, " ");
		}
		
		shift = atoi(buf3); // ���ڸ� ������ ��ȯ
		printf("%d\n", shift);


		// ciphertext�� �о���� ���� 
		
	fclose(fp);	// ���� �ݱ�
}