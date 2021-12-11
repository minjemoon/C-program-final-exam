#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // C ǥ�� ��ƿ��Ƽ �Լ����� ��Ƴ��� ������� (rand ����� ����)

void randNum(int maxnumber); // ���� �߻� �Լ�
void readFile(char readfile[]); // ���� �д� �Լ�
void compareNum(int lotto[], int mylotto[]); // �ζ� ��÷ ���� Ȯ��

char fname[100]; // ���� ���
int type, random_num, lotto[6], mylotto[6]; 
// type(�ζ� ���� = �ִ� ����), random_num(����), lotto(���� 6��), mylotto(���ϼ� ���� 6��)

int main(void) {
	printf("�ζ� ��� ���� ��θ� �Է��ϼ���: "); // ���� ��� �Է¹���
	gets_s(fname, 100); // �Էµ� ���� ��� fname�� ����
	readFile(fname); // ���� �б�

	printf("�ζ� ������ �Է��ϼ���(���ڸ��Է��ϼ���): "); // �ִ� ���ڸ� �Է¹���
	scanf("%d", &type); // type ������ �Ҵ�
	randNum(type); // ���� ����

	compareNum(lotto, mylotto); // ������ ���� 6���� ���� �� ���� 6���� ��
}

/*
�Լ���: randNum
���: �ߺ����� �ʴ� ���� 6�� ����
- �Ű�����
	1. maxnumber = ����ڰ� �Է��� �ζ� ����(�ִ� ����)
*/
void randNum(int maxnumber) {
	int i, count = 0; // ���� �ߺ� üũ�� �Ҵ��� ���� ���� 
	srand(202112); // seed ���� 202112�� �����Ͽ� ������ ���� 
				   // seed ���� �� �������� ��� �ڵ����� 1�� ������
	while (1) {
		random_num = rand() % maxnumber + 1; // 1�� ���� rand() % type + 1 = 1 ~ type ������ ���� ����
											 // 1�� ������ ���� ��� rand() % type = 0 ~ (type - 1)������ ���� ����

		/* �ߺ��� �� �ִ��� �˻��ϴ� �ݺ��� */
		for (i = 0; i < count; i++) { // �̹� ������ ������ŭ�� �ߺ������ �˻�
			if (lotto[i] == random_num) { // �̹� ���Դ� ��ȣ���� �˻� (�ߺ� üũ)
				break;  // �ߺ��� ��� for�� ����
			}			// �ߺ��� �Ǳ� ������ i ���̶� count ���̶� �ٸ��� ��
		}
		if (count == i) { // �ߺ����� ���� ��쿡�� count��° �ε����� ���� �Ҵ�
			lotto[count] = random_num;
			count++; // ���� ���������� count�� 1 ����
		}
		if (count == 6) { // count�� 6�� �Ǵ� ��� while�� ����
			break;		  // ���ڸ� 6���� �̾ƾ� �ϱ� ����
		}
	}

	printf("�̹����� ��÷��ȣ��: ");
	for (int j = 0; j < 6; j++) {
		printf("%d ", lotto[j]); // ������ 6���� ���� ���
	}
	printf("\n"); 
}

/*
�Լ���: readFile
���: ���Ͽ��� 6���� ���ڸ� �о��
- ���� �Ű�����
	1. filename = ���ϰ��(���ϸ�)
*/
void readFile(char filename[]) {
	FILE* fp = NULL; // FILE�� ����Ű�� ������ fp ����
	fp = fopen(filename, "r"); // �б� ���� ������ ���� (������ �������� ���� ��� ���� �߻�)

	if (fp == NULL) {// ������ ���� ���
		printf("���� ���� ����\n");
		printf("�ش�Ǵ� ������ �����ϴ�. ���α׷��� �����մϴ�.\n");
		exit(1); // ���α׷� ����
	}
	else { // ������ �����ϴ� ���
		char buf1[20], buf2[20], buf3[20], buf4[20]; // ���ʿ� �ִ� �ܾ �޴� ����
		int a, b, c, d, e, f; // 6���� ���ڸ� �޴� ����

		fscanf(fp, "%s %s %s %s %d %d %d %d %d %d", buf1, buf2, buf3, buf4, &a, &b, &c, &d, &e, &f); // ���Ŀ� �°� �ܾ ���

		/* mylotto ����Ʈ�� ���Ͽ��� ���� ���� 6�� �Ҵ� */
		mylotto[0] = a;
		mylotto[1] = b;
		mylotto[2] = c;
		mylotto[3] = d;
		mylotto[4] = e;
		mylotto[5] = f;	
	}
	fclose(fp);	// ���� �ݱ�
}

/*
�Լ���: compareNum
���: lotto�� mylotto�� ���Ͽ� ��÷ ���� ���
- �Ű�����
	1. lotto = ������ ���� 6��
	2. mylotto = ���Ͽ��� �о�� ���� 6��
*/
void compareNum(int lotto[], int mylotto[]) {
	int result[6], sum = 0; // ��÷ Ȯ�ο� ����

	/* lotto�� mylotto�� �ִ� ������ ���ϴ� �ݺ���
	   lotto�� i �ε����� �ִ� ���� mylotto�� j �ε����� �ִ� ���� ���� ���
	   result�� i �ε����� 1�� �Ҵ��� => result ����Ʈ�� ����� ���� 6�� �ȴٸ� ���� ���ڰ� ���� ��ġ��*/
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (lotto[i] == mylotto[j]) { 
				result[i] = 1; 
			}
		}
	}
	for (int i = 0; i < 6; i++) {
		sum += result[i]; // result ����Ʈ�� ��� �� ���
	}

	printf("������ ��ȣ�� : ");
	for (int i = 0; i < 6; i++) {
		printf("%d ", mylotto[i]); // ���Ͽ��� �о� �� ���� 6�� ���
	}
	printf("�Դϴ�\n");

	if (sum == 6) { // result ����Ʈ�� ��� ���� 6�� ���
		printf("�����մϴ� ��÷�Դϴ�");
	}
	else { // result ����Ʈ�� ��� ���� 6�� �ƴ� ���
		printf("�ƽ����ϴ� ��÷�Դϴ�");
	}
}