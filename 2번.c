#define _CRT_SECURE_NO_WARNINGS // ����� ��Ʃ������� scanf �Լ� ����� ���� ��� ����
#include <stdio.h> 
#include <string.h> // strcpy, strtok ����� ����

void decrypt(char filename[]); // ��ȣȭ �Լ�

char plain[50]; // ���� ���ڿ�
char cipher[50]; // ��ȣȭ�� ���ڿ�
char fname[100]; // ���� ���


int main(void) {
	printf("������ ��θ� �Է��ϼ���: ");
	gets_s(fname, 100); // �Էµ� ���� ��� fname�� ����
	decrypt(fname); // txt ���Ͽ��� ��ȣŰ, ��ȣ�� �о ��ȣȭ
}

/*
�Լ��� : decrypt
���: txt ������ �о� ��ȣŰ�� ��ȣ���� ���
	  ��ȣ���� ��ȣŰ��ŭ �̵��Ͽ� ��ȣȭ�ϴ� �Լ�
- ���� �Ű�����
	1. filename = ���ϰ��(���ϸ�)
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

		fgets(buf1, 20, fp); // ù ��° �� �б�
		buf1[strlen(buf1) - 1] = '\0'; // ���๮�� ���� 
		fgets(buf2, 50, fp); // �� ��° �� �б� 

		//puts(buf1); // ù��°��
		//puts(buf2); // �ι�°��

		char* temp1 = strtok(buf1, " "); // ���� �������� ��ū �и� 
		while (temp1 != NULL) { // �ݺ����� ���� ��ȣŰ ȹ��
			strcpy(buf3, temp1);  // ������ ��ū�� buf3�� ����
			temp1 = strtok(NULL, " ");
		}

		shift = atoi(buf3); // ���ڸ� ������ ��ȯ
		strncpy(cipher, buf2 + 11, sizeof(buf2)); // buf2 �迭 cipher �迭���� ���� (ciphertext )�� ���ֱ� ���� 11�� ����
		
	}
	fclose(fp);	// ���� �ݱ�

	int i = 0;
	while (cipher[i] != '\0') { // null ���� �ƴ� ��� ���
		if (cipher[i] >= 'a' && cipher[i] <= 'z') { // �ҹ��� �������� Ȯ��
			plain[i] = cipher[i] - shift; //��ȣŰ ��ŭ �������� �̵���
			if (plain[i] < 'a') { // ���ĺ� ���� ��� ���
				plain[i] += 26; // ���ĺ� ������ ȸ��
			}
		}
		else { // �ҹ��� ���ĺ��� �ƴ� �͵鿡 ���ؼ� ���� ����
			plain[i] = cipher[i];
		}
		i++;
	}
	printf("��ȣȭ�� ���ڿ�: %s \n", plain);
}
