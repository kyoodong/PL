#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int** calendar;
int* month;

int* numOfDayOfMonth;
	//31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31

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
	calendar = malloc(sizeof(int *) * 12);
	numOfDayOfMonth = malloc(sizeof(int) * 12);
	month = numOfDayOfMonth;
	*numOfDayOfMonth++ = 31;
	*numOfDayOfMonth++ = 28;
	*numOfDayOfMonth++ = 31;
	*numOfDayOfMonth++ = 30;
	*numOfDayOfMonth++ = 31;
	*numOfDayOfMonth++ = 30;
	*numOfDayOfMonth++ = 31;
	*numOfDayOfMonth++ = 31;
	*numOfDayOfMonth++ = 30;
	*numOfDayOfMonth++ = 31;
	*numOfDayOfMonth++ = 30;
	*numOfDayOfMonth = 31;
	numOfDayOfMonth = month;

	int** tmp;
	tmp = calendar;
	for (int i = 0; i < 12; i++) {
		*calendar = malloc(sizeof(int) * 43);
		memset(*calendar, 0, sizeof(*calendar));
		calendar++;
	}
	calendar = tmp;
	int year;
	printf("년도 입력 : ");
	scanf("%d", &year);

	int firstDay = getFirstDayOfYear(year);
	int isLeapYear = (year % 4) == 0;
	int day = 0;
	month = *calendar;
	for (int i = 0; i < firstDay; i++)
		month++;

	for (int i = 0; i < 365; i++) {
		*month = day + 1;
		day++;
		month++;
		if (*numOfDayOfMonth <= day) {
			if (*month == 28 && isLeapYear) {
				*month = day + 1;	
				day++;
				month++;
			}
			firstDay = (firstDay + day) % 7;
			calendar++;
			month = *calendar;
			for (int i = 0; i < firstDay; i++)
				month++;
			numOfDayOfMonth++;
			day = 0;
		}
	}

	int** months;
	calendar = tmp;
	for (int i = 0; i < 4; i++) {
		printf("\n%d월\t\t\t\t\t\t\t\t", 3 * i + 1);
		printf("%d월\t\t\t\t\t\t\t\t", 3 * i + 2);
		printf("%d월\t\t\t\t\t\t\t\n", 3 * i + 3);
		printf("일\t월\t화\t수\t목\t금\t토\t\t");
		printf("일\t월\t화\t수\t목\t금\t토\t\t");
		printf("일\t월\t화\t수\t목\t금\t토\t\n");
		int j = 0;
		do {
			months = tmp;
			for (int t = 0; t < 3; t++) {
				month = *months;
				for (int k = 0; k < 7; k++) {
					if (*month != 0) {
						printf("%d\t", *month);
					} else {
						printf("\t");	
					}
					month++;	
				}
				*months = month;
				months++;
				printf("\t");
			}
			printf("\n");
			months = tmp;
		} while (**months++ || **months++ || **months++);
		tmp++;
		tmp++;
		tmp++;
	}
	return 0;
}
