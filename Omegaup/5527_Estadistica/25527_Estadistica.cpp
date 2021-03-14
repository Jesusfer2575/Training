#include<stdio.h>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;
typedef long long int lli;

int n, m, s, v;

int chooseNumberToZero(int a, int b, int lowerA, int lowerB) {
  if (lowerA <= b && lowerA >= a) {
    return lowerA;
  } else if (lowerB <= b && lowerB >= a) {
    return lowerB;
  } else if (lowerA > b && lowerA > a) {
    return lowerA;
  } else {
    return lowerB;
  }
}

vector<int> getIndexesDifferentZero(vector<int> gaps) {
  vector<int> indexes_not_cero;
  for (int i=0; i<n; ++i) {
    if (gaps[i] != 0) {
      if ( (( i == 0 ) && ( gaps[i+1] == 0 )) || 
          ( ( i == (n-1) ) && ( gaps[i-1] == 0 )) ||
          ( ( i < (n-1) && i > 0 ) && ( gaps[i-1] == 0 || gaps[i+1] == 0 ) )
      ) {
        indexes_not_cero.push_back(i);
      }
    }
  }
  return indexes_not_cero;
}

vector<int> getFilledGaps(int size_indexes_not_zero, vector<int> indexes_not_cero, vector<int> gaps, vector<int> data) {
  vector<int> filled_gaps;
  int a, b, lowerA, lowerB, number_to_choose;
  for (int i=1; i<size_indexes_not_zero; i++) {
    if (m == 1) { // Case when give us one m number
      filled_gaps.push_back(data[0]);
    } else {
      a = gaps[indexes_not_cero[i-1]]; // Get the numbers to calculate their zero
      b = gaps[indexes_not_cero[i]];
      // cout << a << " " << b << " " << "\n";
      int indexA = lower_bound(data.begin(), data.end(), a - 1) - data.begin();
      int indexB = lower_bound(data.begin(), data.end(), b - 1) - data.begin();
      // cout << indexA << " " << indexB << " " << "\n";
      lowerA = data[indexA == m ? indexA-1: indexA]; // Find the possible numbers
      lowerB = data[indexB == m ? indexB-1: indexB];
      // cout << lowerA << " " << lowerB << " " << "\n";
      number_to_choose = chooseNumberToZero(min(a, b), max(a, b), lowerA, lowerB); // From options choose wich be in the range or the most close
      // cout << number_to_choose << "\n";
      filled_gaps.push_back(number_to_choose);
    }
  }
  return filled_gaps;
}

int main() {
  scanf("%d %d ", &n, &m);

  vector<int> gaps;
  vector<int> data;  
  for (int i=0;i<n;i++) {
    scanf("%d ", &s);
    gaps.push_back(s);
  }
  for (int i=0;i<m;i++) {
    scanf("%d ", &v);
    data.push_back(v);
  }
  
  sort(data.begin(), data.end());

  if (gaps.size() == 1) {
    printf("0\n");
    (gaps[0] == 0) ? printf("%d\n", data[0]):printf("%d\n", gaps[0]);
  }
  else {
    vector<int> indexes_not_cero = getIndexesDifferentZero(gaps);
    int size_indexes_not_zero = indexes_not_cero.size();

    if (size_indexes_not_zero == 0) {
      int index_last_element = data.size() - 1;
      int number_choosed = data[index_last_element];

      printf("0\n");
      for (int i = 0;i < n;i++) 
        printf("%d ", number_choosed);
      printf("\n");
    } else if (size_indexes_not_zero == 1){ // case when we have only one number different from zero
      int number_to_find = gaps[indexes_not_cero[0]];
      int lower = lower_bound(data.begin(), data.end(), number_to_find) - data.begin();
      int index_number = lower == m ? lower-1:lower;
      
      if (n>2) {
        printf("0\n");
        for (int i = 0;i < n;i++) {
          (gaps[i] == 0) ? printf("%d", data[index_number]):printf("%d", gaps[i]);
          printf(" ");
        }
        printf("\n");
      } else {
        printf("%d\n", abs(number_to_find - data[index_number]));
        for (int i = 0;i < n;i++)
          (gaps[i] == 0) ? printf("%d", data[index_number]):printf("%d ", gaps[i]);
        printf("\n");
      }
    }
    else if (size_indexes_not_zero > 1) { // case when we have multiple numbers and zeros
      vector<int> filled_gaps = getFilledGaps(size_indexes_not_zero, indexes_not_cero, gaps, data);
      
      vector<int> solutions;
      for (int i=0, j=0, k=0; i<n; i++) {
        if (gaps[i] == 0) {
          j = i;
          while (gaps[j] == 0) {
            solutions.push_back(filled_gaps[k]);
            j++;
          }
          i = j-1;
          k++;
        } else {
          solutions.push_back(gaps[i]);
        }
      }

      lli minimum = INT_MAX;
      lli addition = 0;
      for (int i=1; i<solutions.size(); i++) {
        if (i+1 < n) {
          addition = abs(solutions[i-1] - solutions[i]) + abs(solutions[i] - solutions[i+1]);
          minimum = min(minimum, addition);
        }
      }
      printf("%lld\n", minimum);

      for (int i = 0; i < solutions.size(); i++)
        printf("%d ", solutions[i]);
      
      printf("\n");
    } 
  }
  return 0;
}