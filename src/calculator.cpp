// calculator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int calculator(int n);

int numbers[11] = { 0 };
int operation[6] = { 0 };

int main() {
	srand(time(0));
	int times;
	printf("How many exercises do you want?  ");
	scanf("%d", &times);
	for (int i = 0; i < times; i++) {
		int op = rand() % 3 + 2;
		calculator(op);
	}
	FILE *fp = fopen("calculator.txt", "at+");
	fprintf(fp, "1753485,刘雍熙\n");
	printf("1753485 刘雍熙");
}

int calculator(int n) {
	FILE *fp = fopen("result.txt", "at+");
	for (int i = 1; i <= n; i++) {
		numbers[i] = rand() % 100;
		printf("%d", numbers[i]);
		int ope = rand();
		if (ope % 4 == 0) {
			fprintf(fp, "%d+", numbers[i]);
			printf("+");
			operation[i] = 1;
		}
		else if (ope % 4 == 1) {
			fprintf(fp, "%d-", numbers[i]);
			printf("-");
			operation[i] = 2;
		}
		else if (ope % 4 == 2) {
			fprintf(fp, "%d*", numbers[i]);
			printf("*");
			operation[i] = 3;
		}
		else if (ope % 4 == 3) {
			fprintf(fp, "%d/", numbers[i]);
			printf("/");
			operation[i] = 4;
		}
	}
	numbers[n + 1] = rand() % 100;
	fprintf(fp, "%d=", numbers[n+1]);
	printf("%d=", numbers[n + 1]);
	int index = 0;
	for (int i = 1; i <= n; i++) {
		if (operation[i - 1] != 5) {
			if (operation[i] == 3) {
				numbers[i] = numbers[i] * numbers[i + 1];
				operation[i] = 5;
				numbers[i + 1] = 0;
				index++;
			}
			else if (operation[i] == 4) {
				numbers[i] = numbers[i] / numbers[i + 1];
				operation[i] = 5;
				numbers[i + 1] = 0;
				index++;
			}
		}
		else if (operation[i - 1] == 5) {
			if (operation[i] <= 2) {
				continue;
			}
			int t = 0;
			for (t = 0; t < index; t++) {
				if (operation[i - t - 1] != 5) {
					break;
				}
			}
			if (operation[i] == 3) {
				numbers[i - t] = numbers[i - t] * numbers[i + 1];
				operation[i] = 5;
				numbers[i + 1] = 0;
				index++;
			}
			else if (operation[i] == 4) {
				numbers[i - t] = numbers[i - t] / numbers[i + 1];
				operation[i] = 5;
				numbers[i + 1] = 0;
				index++;
			}
		}
	}
	numbers[0] = numbers[1];
	for (int i = 1; i < n + 1; i++) {
		if (operation[i] == 1 || operation[i] == 5) {
			numbers[0] = numbers[0] + numbers[i + 1];
		}
		else if (operation[i] == 2) {
			numbers[0] = numbers[0] - numbers[i + 1];
		}
	}
	fprintf(fp, "%d\n", numbers[0]);
	printf("%d\n", numbers[0]);
	fclose(fp);
	for (int i = 0; i < n; i++) {
		numbers[i] = 0;
		operation[i] = 0;
	}
	return 0;
}
