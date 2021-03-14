#include<stdio.h>
int n, digits = 0, powerOfTen = 1, preDigits = 0;

int main() {
  scanf("%d", &n);
  while(powerOfTen <= n) {
    preDigits = n - powerOfTen + 1;
    powerOfTen *= 10;
    digits += preDigits;
  }
  printf("%d\n", digits);
  return 0;
}