#define _CRT_SECURE_NO_WARNINGS // ����� ��Ʃ������� scanf �Լ� ����� ���� ��� ����
#include <stdio.h> 
#include <string.h>

void decrypt(char filename[]); // ��ȣȭ �Լ�

char plain[50]; // ���� ���ڿ�
char cipher[50]; // ��ȣȭ�� ���ڿ�
char fname[100]; // ���� ���


int main(void) {
	printf("������ ��θ� �Է��ϼ���: ");
	gets_s(fname, 100); // �Էµ� ���� ��� fname�� ����
	decrypt(fname);
}

/*
�Լ��� : decrypt
���: ��ȣ���� ��ȣŰ��ŭ �̵��Ͽ� ��ȣȭ�ϴ� �Լ�
- ���� �Ű�����
	1. 
*/
void decrypt(char filename[]) {
	int shift; // ��ȣŰ

	FILE* fp = NULL; // FILE�� ����Ű�� ������ fp ����
	fp = fopen(filename, "r"); // �б� ���� ������ ���� (������ �������� ���� ��� ���� �߻�)

	if (fp == NULL) {// ������ ���� ���
		printf("���� ���� ����\n");
		printf("��ȣȭ�� ������ �����ϴ�. ���α׷��� �����մϴ�.\n");
		exit(1); // ���α׷� ����
	}
	else { // ������ �����ϴ� ���
		char buf1[20], buf2[100], buf3[10], buf4[100]; // ������ �б� ���� �ӽ� ����
		char space[10] = " ";

		fgets(buf1, 20, fp);
		buf1[strlen(buf1) - 1] = '\0'; // ���๮�� ���� 
		fgets(buf2, 50, fp);

		puts(buf1); // ù��°��
		puts(buf2); // �ι�°��

		char* temp1 = strtok(buf1, " "); // ���� �������� ��ū �и� 
		while (temp1 != NULL) {
			strcpy(buf3, temp1);
			temp1 = strtok(NULL, " ");
		}

		shift = atoi(buf3); // ���ڸ� ������ ��ȯ
		printf("%d\n", shift); // ���� ���� (Ȯ�� �Ϸ�)

		strncpy(cipher, buf2 + 11, sizeof(buf2));
		printf("%s\n", cipher);
		
	}
	fclose(fp);	// ���� �ݱ�

	for (int i = 0; cipher[i] != '\0'; i++) {
		if (cipher[i] >= 'a' && cipher[i] <= 'z') {
			plain[i] = (cipher[i] - 'a' - shift) % 26 + 'a';
		}
		else { // �ҹ��� ���ĺ��� �ƴ� �͵鿡 ���ؼ� ���� ����
			plain[i] = cipher[i];
		}
	}

	printf("��ȣȭ�� ���ڿ�: %s \n", plain);
}
