#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int N;
int count;
int primes[10000];
int is_prime;

int main(int argc, char *argv[]) {
	N = atoi(argv[1]);
	struct timeval start_tv, end_tv;

	printf("N = %d\n", N);

	gettimeofday(&start_tv, NULL);

	int curValue = 2;
	while (count < N) {
		is_prime = 1;
		for (int i = 2; i < curValue; i++) {
			if (curValue % i == 0) {
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
	gettimeofday(&end_tv, NULL);

	if (end_tv.tv_usec < start_tv.tv_usec) {
		end_tv.tv_sec--;
		end_tv.tv_usec += 1000000;
	}

	printf("걸린 시간 : %ld.%ld초\n", end_tv.tv_sec - start_tv.tv_sec, end_tv.tv_usec - start_tv.tv_usec);
	exit(0);
}
