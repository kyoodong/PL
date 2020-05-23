#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

// 소수의 갯수
int N;

// 현재까지 구한 소수의 갯수
int count;

// 구해진 소수 모음
int primes[10000];

// 현재 평가중인 수가 소수인지 아닌지 표현
int is_prime;

int main(int argc, char *argv[]) {
	N = atoi(argv[1]);
	struct timeval start_tv, end_tv;

	printf("N = %d\n", N);

	// 시간 측정 시작
	gettimeofday(&start_tv, NULL);

	// 2부터 소수인지 판별
	int curValue = 2;
	while (count < N) {
		is_prime = 1;

		// 자기 자신보다 작은 소수로 나누어봤을 때
		// 나누어진다면 소수가 아님
		for (int i = 0; i < count; i++) {
			if (curValue % primes[i] == 0) {
				is_prime = 0;
				break;
			}
		}

		if (is_prime) {
			primes[count++] = curValue;
		}
		curValue++;
	}

	   // 출력문이 수행시간에 영향을 미치므로 삭제
	/*
	printf("소수 리스트\n");
	for (int i = 0; i < N; i++) {
		printf("%d\t", primes[i]);
	}
	printf("\n");
	*/

	// 끝나는 시간 측정
	gettimeofday(&end_tv, NULL);

	if (end_tv.tv_usec < start_tv.tv_usec) {
		end_tv.tv_sec--;
		end_tv.tv_usec += 1000000;
	}

	printf("걸린 시간 : %ld.%ld초\n", end_tv.tv_sec - start_tv.tv_sec, end_tv.tv_usec - start_tv.tv_usec);
	exit(0);
}
