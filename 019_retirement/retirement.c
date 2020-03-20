// retirement.c

// includes
#include <stdio.h>
#include <stdlib.h>

// structs & types
struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

/*********************************************
 retirement
*********************************************/
void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info_t working,  //info about working
                retire_info_t retired)  //info about being retired
{
  double working_balance = initial;
  double working_returns = 0;
  int total_month = startAge;
  for (; total_month < startAge + working.months; total_month++) {
    printf(
        "Age %3d month %2d you have $%.2lf\n", total_month / 12, total_month % 12, working_balance);
    working_returns = working_balance * working.rate_of_return;
    working_balance += working_returns + working.contribution;
  }
  double retired_balance = working_balance;
  double retired_returns = 0;
  int middle_age = total_month;
  for (; total_month < middle_age + retired.months; total_month++) {
    printf(
        "Age %3d month %2d you have $%.2lf\n", total_month / 12, total_month % 12, retired_balance);
    retired_returns = retired_balance * retired.rate_of_return;
    retired_balance += retired_returns + retired.contribution;
  }
}

/*********************************************
 main
*********************************************/
int main() {
  // printf("test for retirement program.\n");
  int start_age = 327;
  int start_savings = 21345;
  retire_info_t working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info_t retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(start_age, start_savings, working, retired);

  return EXIT_SUCCESS;
}
