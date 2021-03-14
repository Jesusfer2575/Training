#include<iostream>
#include<vector>
using namespace std;

class Solution {
  public:
    vector<int> minOperations(string boxes) {
      int len = boxes.size();
      vector<int> answer;
      for (int i = 0; i < len ; i++) {
        int sum = 0;
        for (int j = 0; j < len ; j++) {
          if (i != j and boxes[j] == '1') {
            int val = abs(i - j);
            sum += val;
          }
        }
        answer.push_back(sum);
      }
      return answer;
    }
};

int main() {
  Solution* s = new Solution(); 
  return 0;
}