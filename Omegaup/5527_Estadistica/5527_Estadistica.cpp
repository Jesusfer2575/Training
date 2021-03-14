#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include <unordered_map>
#include<limits.h>
using namespace std;
typedef long long int lli;

int n, m, s, v;
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
      auto hash1 = hash<T1>{}(p.first); 
      auto hash2 = hash<T2>{}(p.second); 
      return hash1 ^ hash2; 
    } 
};
//                        4       9      100       3
int chooseNumberToZero(int a, int b, int lowerA, int lowerB) {
  // cout << a << " " << b << " "  << lowerA << " " << lowerB << " "<< "\n";
  int minA = abs(a-lowerA) + abs(b-lowerA);
  int minB = abs(a-lowerB) + abs(b-lowerB);
  return (minA < minB) ? lowerA:lowerB;
}

vector<int> getIndexesDifferentZero(vector<int> gaps) {
  vector<int> indexes_not_cero;
  for (int i=0; i<n; ++i) {
    if (gaps[i] != 0) {
      if ( (( i == 0 ) && ( gaps[i+1] == 0 )) || 
          ( ( i == (n-1) ) && ( gaps[i-1] == 0 )) ||
          // ( (gaps[i+1] == 0 && gaps[i+2] != 0 && (i+1) <= (n-1) && i+2 < (n-1)) ||
          //   (gaps[i-1] == 0 && gaps[i-2] != 0 && (i-1) >= 0 && i-2 > 0))
          ( ( i < (n-1) && i > 0 ) && ( gaps[i-1] == 0 || gaps[i+1] == 0 ) )
      ) {
        indexes_not_cero.push_back(i);
      }
    }
  }
  return indexes_not_cero;
}

void getFilledGaps(int size_indexes_not_zero, vector<int> indexes_not_cero, vector<int> gaps, vector<int> data) {
  vector<int> new_solutions(1000003, 0);
  int a, b, idxA, idxB, lowerA, lowerB, number_to_choose;
  unordered_map<pair<int, int>, int, hash_pair> possible_solutions;

  for (int i=1; i<size_indexes_not_zero; i++) {
    idxA = i-1;
    idxB = i;
    a = gaps[indexes_not_cero[idxA]]; // Get the numbers to calculate their zero
    b = gaps[indexes_not_cero[idxB]];

    if (abs(indexes_not_cero[idxA] - indexes_not_cero[idxB]) > 1) {
      pair<int, int> p(min(a, b), max(a, b));
      // cout << indexes_not_cero[idxA] << " " << indexes_not_cero[idxB] << " " << abs(indexes_not_cero[idxA] - indexes_not_cero[idxB]) << "\n";

      if (possible_solutions.find(p) == possible_solutions.end()) {
        int indexA = lower_bound(data.begin(), data.end(), a - 1) - data.begin();
        int indexB = lower_bound(data.begin(), data.end(), b - 1) - data.begin();

        lowerA = data[indexA == m ? indexA-1: indexA]; // Find the possible numbers
        lowerB = data[indexB == m ? indexB-1: indexB];
        number_to_choose = chooseNumberToZero(min(a, b), max(a, b), lowerA, lowerB); // From options choose wich be in the range or the most close
        possible_solutions[p] = number_to_choose;
      }
      
      new_solutions[indexes_not_cero[idxA]] = a;
      for (int k=indexes_not_cero[idxA] + 1; k<indexes_not_cero[idxB]; k++)
        new_solutions[k] = possible_solutions[p];
      // new_solutions.push_back(a);
      // new_solutions.push_back(possible_solutions[p]);
      
    } else {
      // cout << "ELSE " << a << " " << b << " " << "\n";
      //new_solutions.push_back(a);
      new_solutions[indexes_not_cero[idxA]] = a;
    }
  }
  new_solutions[indexes_not_cero[idxB]] = b;

  for (int i = 0; i < n; i++)
    if (new_solutions[i] == 0) 
      new_solutions[i] = gaps[i];

  lli minimum = INT_MAX;
  lli addition = 0;
  for (int i=1; i<n; i++) {
    if (i+1 < n && new_solutions[i] != 0) {
      addition = abs(new_solutions[i-1] - new_solutions[i]) + abs(new_solutions[i] - new_solutions[i+1]);
      minimum = min(minimum, addition);
    }
  }

  printf("%lld\n", minimum);
  for (int i = 0; i < n; i++)
    (new_solutions[i] == 0) ? printf("%d ", gaps[i]):printf("%d ", new_solutions[i]);
  printf("\n");
}

int main() {
  scanf("%d %d", &n, &m);

  vector<int> gaps;
  vector<int> data;  
  for (int i=0;i<n;i++) {
    scanf("%d", &s);
    gaps.push_back(s);
  }
  for (int i=0;i<m;i++) {
    scanf("%d", &v);
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
        int min_above = abs(number_to_find - data[index_number]);
        int min_bellow = abs(number_to_find - data[index_number - 1]);
        if (data[index_number] > number_to_find && min_bellow < min_above) { // Case when we find a number grater than the one we're looking for
          index_number -= 1;
        }
        printf("%d\n", abs(number_to_find - data[index_number]));
        for (int i = 0;i < n;i++)
          (gaps[i] == 0) ? printf("%d", data[index_number]):printf("%d ", gaps[i]);
        printf("\n");
      }
    }
    else if (size_indexes_not_zero > 1) { // case when we have multiple numbers and zeros
      getFilledGaps(size_indexes_not_zero, indexes_not_cero, gaps, data);
    } 
  }
  return 0;
}