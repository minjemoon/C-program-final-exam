#define _CRT_SECURE_NO_WARNINGS // ����� ��Ʃ������� scanf �Լ� ����� ���� ��� ����
#include <stdio.h> 

void encrypt(char plaintext[], int shift); // ��ȣȭ �Լ�
void createFile(char ciphertext[], int shift); // ���� �����ϴ� �Լ�
void decrypt(char filename[]); // ��ȣȭ �Լ�

char plain[50]; // ���� ���ڿ�
char cipher[50]; // ��ȣȭ�� ���ڿ�
char fname[100]; // ���� ��� �� �̸�
int shift; // ��ȣŰ ����(shift)

int main(void) {
	int mode; // ��� ���� ����

	printf("��ȣȭ ���, ��ȣȭ ��带 �����ϼ���(��ȣȭ = 1, ��ȣȭ = 0): ");
	scanf("%d", &mode);

	if (mode == 1) { // ��ȣȭ ��� ����

		printf("��ȣŰ�� �Է��ϼ���(����1~9): ");
		scanf("%d", &shift); // �Էµ� ��ȣŰ shift�� ����

		getchar(); // scanf�� ���� ����(\n)�� ���� -> gets_s ����ϱ� ����

		printf("���� �Է��ϼ���: ");
		gets_s(plain, 50); // �Էµ� �� plain�� ����

		encrypt(plain, shift); // ��(plain)�� ��ȣŰ(shift)�� �ش�ǰ� ��ȣȭ
		createFile(cipher, shift); //��ȣŰ(shift)�� ��ȣ��(cipher) txt ���Ͽ� ����
	}
	else if (mode == 0) { // ��ȣȭ ��� ����
		getchar(); // ���� ����(\n)�� ���� -> gets_s ����ϱ� ����

		printf("������ ��θ� �Է��ϼ���: ");
		gets_s(fname, 100); // �Էµ� ���� ��� fname�� ����
		decrypt(fname); // ���Ͽ��� ��ȣŰ ��ȣ�� �а� ��ȣȭ
	}
	else
		printf("�������� ���� ��ȣ�Դϴ�.");
	
}

/*
�Լ��� : encrypt
���: ���� ��ȣŰ��ŭ �̵��Ͽ� ��ȣȭ�� �ϴ� �Լ�
- ���� �Ű�����
	1. plaintext = ��
	2. shift = ��ȣŰ
*/
void encrypt(char plaintext[], int shift) {
	int i = 0;
	/* plaintext[i]�� �ҹ����� ��� shift ��ŭ ���ؼ� ��ȣȭ ����
		a~z = 97~122(ASCII�ڵ�)  -> plaintext[i]���� a�� ���� a~z = 0~25�� ������ ���� ��
		���� %(����������)�� ���� ���ĺ� ������ �Ѿ�� ���� ������ �� ����
		���Ƿ� ������ ������ �����·� �����ϱ� ���� �ٽ� a�� ����
	*/
	while (plaintext[i] != '\0') {
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
			cipher[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
		}
		else { // ���ĺ� �ҹ��ڰ� �ƴ� �͵��� ���� ����
			cipher[i] = plaintext[i];
		}
		i++;
	}
	printf("��ȣȭ�� ���ڿ�: %s \n", cipher);
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

	FILE* fp1 = NULL; // FILE�� ����Ű�� ������ fp ����
	fp1 = fopen(filename, "r"); // �б� ���� ������ ���� (������ �������� ���� ��� ���� �߻�)

	if (fp1 == NULL) {// ������ ���� ���
		printf("���� ���� ����\n");
		printf("��ȣȭ�� ������ �����ϴ�. ���α׷��� �����մϴ�.\n");
		exit(1); // ���α׷� ����
	}
	else { // ������ �����ϴ� ���
		char buf1[20], buf2[100], buf3[10], buf4[100]; // ������ �б� ���� �ӽ� ����

		fgets(buf1, 20, fp1); // ù ��° �� �б�
		buf1[strlen(buf1) - 1] = '\0'; // ���๮�� ���� 
		fgets(buf2, 50, fp1); // �� ��° �� �б� 

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
	fclose(fp1);	// ���� �ݱ�

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

/*
�Լ���: createFile
���: ��ȣŰ�� ��ȣ���� txt ���Ͽ� ����
- ���� �Ű�����
	1. ciphertext = ��ȣ��
	2. shift = ��ȣŰ
*/
void createFile(char ciphertext[], int shift) {
	char fname1[100] = "C:\\Temp\\result.txt";
	FILE *fp2; // FILE�� ����Ű�� ������ fp ����
	fp2 = fopen(fname1, "w"); // ���� ���� ���ο� ������ ����(�̹� �����ϴ� ��� ���� ���� ����)

	if (fp2 == NULL) {
		printf("���� ���� ����\n");
		exit(1);
	}
	else {
		fprintf(fp2, "%s %d\n", "key", shift);
		fputs("ciphertext ", fp2);
		fputs(cipher, fp2);
	}
	fclose(fp2);	// ���� �ݱ�
}
