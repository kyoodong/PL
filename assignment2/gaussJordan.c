#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VAR_LEN 100
#define BUF_LEN 1024

int variable_num;
double eq_table[VAR_LEN + 1][VAR_LEN + 1];
int var_count_table[VAR_LEN + 1];
double rq_table[VAR_LEN + 1];
double result_table[VAR_LEN];
int marking_table[VAR_LEN];
int var_marking_table[VAR_LEN];

int queue[VAR_LEN];
int front, rear;

int push(int n) {
	queue[front++] = n;
}
int get() {
	return queue[rear];
}
int pop() {
	rear++;
	if (front == rear) {
		rear = 0;
		front = 0;
	}
}
int empty() {
	return front == rear;
}

void print_equation(int index) {
	for (int i = 0; i < variable_num; i++) {
		if (eq_table[index][i] != 0) {
			printf("%.2lfX%d ", eq_table[index][i], i + 1);
		} else {
			printf("\t");
		}
	}
	printf("= %.2lf\n", rq_table[index]);
}

void print_all() {

	printf("===================================\n");
	for (int j = 0; j < variable_num; j++) {
		print_equation(j);
	}
	printf("===================================\n");
}

int find_has_var_eq(int var) {
	for (int i = 0; i < variable_num; i++) {
		if (marking_table[i] == 0 && eq_table[i][var] != 0)
			return i;
	}
	return -1;
}

int get_var(int index) {
	for (int i = 0; i < variable_num; i++) {
		if (eq_table[index][i] != 0)
			return i;

	}
	return -1;
}

void set_var(int var_index) {
	for (int k = 0; k < variable_num; k++) {
		if (k == var_index)
			continue;
		if (eq_table[k][var_index] == 0 || var_marking_table[k] != 0)
			continue;

		rq_table[k] -= eq_table[k][var_index] * result_table[var_index];
		eq_table[k][var_index] = 0;
		var_count_table[k]--;

		if (var_count_table[k] == 1) {
			int i = get_var(k);
			result_table[i] = rq_table[k] / eq_table[k][i];
			eq_table[k][i] = 1;
			rq_table[k] = result_table[i];
			var_marking_table[i] = 1;
			push(i);
		}
	}
}

int main()
{
	int index = -1;

	printf("변수의 갯수를 입력하세요 : ");
	scanf("%d", &variable_num);
	if (variable_num > VAR_LEN) {
		fprintf(stderr, "최대 변수의 갯수는 %d개 입니다.\n", VAR_LEN);
		return 1;
	}

	for (int i = 0; i < variable_num; i++) {
		printf("수식의 계수만을 입력하세요 (예: 2X1 + 3X2 + 3X3 = 4 -> 2 3 4)\n");
		for (int j = 0; j < variable_num; j++) {
			scanf("%lf", eq_table[i] + j);
			
			if (eq_table[i] != 0) {
				var_count_table[i]++;
			}
		}
		scanf("%lf", rq_table + i);
		print_equation(i);
	}

	for (int i = 0; i < variable_num; i++) {
		index = find_has_var_eq(i);
		marking_table[index] = 1;
		for (int j = 0; j < variable_num; j++) {
			if (marking_table[j] != 0 || var_marking_table[j] != 0)
				continue;
			double factor = eq_table[j][i] / eq_table[index][i];
			int count = 0;
			int nIndex = -1;
			for (int k = 0; k < variable_num; k++) {
				eq_table[j][k] -= factor * eq_table[index][k];
				if (eq_table[j][k] != 0) {
					count++;
					nIndex = k;
				}
			}
			var_count_table[j] = count;
			rq_table[j] -= factor * rq_table[index];
			if (count == 1) {
				result_table[nIndex] = rq_table[j] / eq_table[j][nIndex];
				eq_table[j][nIndex] = 1;
				rq_table[j] = result_table[j];
				var_marking_table[nIndex] = 1;
				push(nIndex);
			}

			print_all();
		}

		while (!empty()) {
			index = get();
			pop();

			set_var(index);
			print_all();
		}

	}

	for (int i = 0; i < variable_num; i++) {
		printf("X%d = %lf\n", i + 1, result_table[i]);
	}

	return 0;
}
