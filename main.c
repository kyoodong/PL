#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int calendar[12][42];

int numOfDayOfMonth[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/**
 * 주어진 연 1월 1일이 무슨 요일인지 알려주는 함수
 */
int getFirstDayOfYear(int year) {
	int allDay = (year - 1) * 365 + (year - 1) / 4;
	return allDay % 7;
}

/**
 * 달력을 출력하는 프로그램
 */
int main() {
	int year;
	printf("년도 입력 : ");
	scanf("%d", &year);

	int firstDay = getFirstDayOfYear(year);
	int isLeapYear = (year % 4) == 0;
	int month = 0;
	int day = 0;
	for (int i = 0; i < 365; i++) {
		calendar[month][firstDay + day] = day + 1;
		day++;
		if (numOfDayOfMonth[month] <= day) {
			if (month == 1 && isLeapYear) {
				calendar[month][firstDay + day] = day + 1;	
				day++;
			}
			firstDay = (firstDay + day) % 7;
			month++;
			day = 0;
		}
	}

	printf("%d년", year);
	for (int i = 0; i < 12; i++) {
		printf("%d월\n일\t월\t화\t수\t목\t금\t토\n", i + 1);
		int j = 0;
		do {
			for (int k = 0; k < 7; k++) {
				if (calendar[i][j] != 0) {
					printf("%d\t", calendar[i][j]);
				} else {
					printf("\t");	
				}	
				j++;
			}
			printf("\n");
		} while (calendar[i][j] != 0);
	}
	return 0;
}
