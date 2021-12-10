#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // C ǥ�� ��ƿ��Ƽ �Լ����� ��Ƴ��� ������� (rand ����� ����)

void randNum(int maxnumber); // ���� �߻� �Լ�
void createFile(int numberlist[]); // ���� �����ϴ� �Լ�

char fname[100] = "C:\\Temp\\lotto.txt"; // ���� ��� �� �̸�
int type, random_num, lotto[6]; // type = �ζ� ����(�ִ� ����), random_num(����), lotto(���� 6��)

int main(void) {
	
	int i, count = 0; // ���� �ߺ��� �Ҵ��� ���� ���� 

	printf("�ζ� ������ �Է��ϼ���(���ڸ��Է��ϼ���): "); // �ִ� ���ڸ� �Է¹���
	scanf("%d", &type); // type ������ �Ҵ�

	randNum(type);
	createFile(lotto);
}

/*
�Լ���: randNum
���: �ߺ����� �ʴ� ���� 6�� ����
- �Ű�����
	1. maxnumber = ����ڰ� �Է��� �ζ� ����(�ִ� ����)
*/

void randNum(int maxnumber) {
	int i, count = 0; // ���� �ߺ��� �Ҵ��� ���� ���� 

	while (1) {
		random_num = rand() % maxnumber + 1; // 1�� ���� rand() % type + 1 = 1 ~ type ������ ���� ����
										// 1�� ������ ���� ��� rand() % type = 0 ~ (type - 1)������ ���� ����
		
		/* �ߺ��� �� �ִ��� �˻��ϴ� �ݺ��� */
		for (i = 0; i < count; i++) { // �̹� ������ ������ŭ�� �ߺ����� �˻�
			if (lotto[i] == random_num) { // �̹� ���� ��ȣ���� �˻� (�ߺ� üũ)
				break;  // �ߺ��� ��� for�� ����
			}			// �ߺ��� �Ǳ� ������ i ���̶� count ���̶� �ٸ��� ��
		}
		if (count == i) { // �ߺ����� ���� ��쿡�� count��° �ε����� �Ҵ�
			lotto[count] = random_num;
			count++; // ���� ���������� count�� 1 ����
		}
		if (count == 6) { // count�� 6�� �Ǵ� ��� while�� ����
			break;		  // ���ڸ� 6���� �̾ƾ� �ϱ� ����
		}
	}

	printf("���õ� ��ȣ�� ������ �����ϴ�: ");
	for (int j = 0; j < 6; j++) {
		printf("%d ", lotto[j]); // ������ 6���� ���� ���
	}
}

/*
�Լ���: createFile
���: ������ ���� 6���� txt ���Ͽ� ����
- ���� �Ű�����
	1. numberlist = ���� ����Ʈ
*/
void createFile(int numberlist[]) {
	FILE* fp = NULL; // FILE�� ����Ű�� ������ fp ����
	fp = fopen(fname, "w"); // ���� ���� ���ο� ������ ����(�̹� �����ϴ� ��� ���� ���� ����)

	if (fp == NULL) {
		printf("���� ���� ����\n");
		exit(1);
	}
	else {
		int buf1;
		char buf2[10];

		/* txt ���Ͽ� ������ 6���� ���� �Է� */
		fputs("���õ� ��ȣ�� ������ �����ϴ�: ", fp);
		for (int j = 0; j < 6; j++) {
			buf1 = numberlist[j];		   
			snprintf(buf2,10, "%d", buf1); //������ ������ ���ڿ��� �����ؼ� ����
			fputs(buf2, fp); //���� �Է�
			fputc(' ', fp);
		}
	}
	fclose(fp);	// ���� �ݱ�
}