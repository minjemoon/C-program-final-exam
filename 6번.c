#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // C ǥ�� ��ƿ��Ƽ �Լ����� ��Ƴ��� ������� (rand ����� ����)
#include <time.h> // rand�Լ� �ʱ�ȭ�� ���� - seed ����

void randNum(int maxnumber, int runtimes); // ���� �߻� �Լ�
void statistics(int statmaxnum, int n[], int statlist[]); // �ζ� ����Ƚ���� ���� ��賻�� �Լ�

int type, runtime, random_num, lotto[6], stats[500] = {0,};
// type(�ζ� ���� = �ִ� ����), runtime(���� Ƚ��), random_num(����), lotto(���� 6��), stats(����ڷὺ��) -> ���Ƿ� ũ�� 500 ����

int main(void) {
	printf("�ζ� ������ �Է��ϼ���(���ڸ��Է��ϼ���): "); // �ִ� ���ڸ� �Է¹���
	scanf("%d", &type); // type ������ �Ҵ�

	printf("�ζ� ���� Ƚ���� �Է��ϼ���(���ڸ��Է��ϼ���): "); // �ζ� ������ Ƚ�� �Է¹���
	scanf("%d", &runtime); // runtime ������ �Ҵ� 

	randNum(type, runtime); // ���� ����
	statistics(type, runtime, stats); // ��� �ڷ� ���
}

/*
�Լ���: randNum
���: �ߺ����� �ʴ� ���� 6���� �ζ� ���� Ƚ����ŭ ����
- �Ű�����
	1. maxnumber = ����ڰ� �Է��� �ζ� ����(�ִ� ����)
	2. runtimes = �ζ� ���� Ƚ��
*/
void randNum(int maxnumber, int runtimes) {
	int tnumber = 1; // tnumber(�ζ� ���� Ƚ�� Ȯ�ο� ����)
	srand((unsigned int)time(NULL)); // rand �Լ��� ������ �õ尪 ���� , time(NULL)�� 1�ʸ��� �ٸ� �õ尪 ȣ�� ����

	while (tnumber <= runtimes) { // �ζ� ����Ƚ����ŭ �ݺ��� ����
		int i, count = 0; // i & count(���� �ߺ��� �Ҵ��� ���� ����)
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

		/* �Ʒ� �ּ����� �� �ڵ� ����� �����Ǵ� ���� Ȯ�� ���� */
		//printf("���õ� ��ȣ�� ������ �����ϴ�: ");
		//for (int j = 0; j < 6; j++) {
		//	printf("%d ", lotto[j]); // ������ 6���� ���� ���
		//}
		//printf("\n");
		
		/* ������ ���ڿ� �Ȱ��� �ε����� ���� 1�� �߰�*/
		for (int j = 1; j <= type; j++) {
			for (int k = 0; k < 6; k++) {
				if (j == lotto[k]) { // ������ ���ڿ� �ε����� ���� ���
					stats[j] += 1;  // �ش� �ε����� 1 ����
				}
			}
		}
		tnumber++; // ����Ƚ�� 1�� ����
	}
}

/*
�Լ���: statistics
���: �ζǸ� nȸ ������ ����� ��踦 ���
- �Ű�����
	1. statmaxnum = �ζ� ����(������ ũ��)
	2. n = �ζ� ���� Ƚ��
	3. statlist = ������ ���ڿ� Ƚ�� ��� ����
*/
void statistics(int statmaxnum, int n, int statlist[]) {
	int max = 0; // max(���� ���� ���� Ƚ�� �޴� ����)
	
	/* �ζ� nȸ ���� ��� ����ϴ� �ݺ��� */
	printf("�ζǸ� %dȸ ������ ��� ����Դϴ�\n", n);
	for (int j = 1; j <= statmaxnum; j++) {
		printf("%d�� %d�� ���Խ��ϴ�\n", j, stats[j]); 
	}

	/* �ζǸ� nȸ �����ϸ鼭 ���� ���� ������ ���ڸ� ����ϴ� �ݺ��� */
	printf("���� ���� ������ ���ڴ� ");
	for (int j = 1; j <= statmaxnum; j++) { // ���� ���� ���� Ƚ�� �ޱ�
		if (max < stats[j]) {
			max = stats[j];
		}
	}

	for (int j = 1; j <= statmaxnum; j++) {
		if (max == stats[j]) {
			printf("%d ", j); // ���� ���� ���� �� (���� 1�� ��� ���)
		}
	}
	printf("�Դϴ�");
}