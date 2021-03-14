#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
using namespace std;

class Solution {
  public:
    bool canCross(vector<int>& stones) {
      for (int i = 3; i < stones.size(); i++)
        if (stones[i] > stones[i - 1] * 2)
          return false; // We need to check if the current stone (with some matemagic) 
          //is less than the double, only if that happen we can continue with the solution
      
      int lastStone = stones[stones.size() - 1];
      stack<int> positions;
      stack<int> jumps;
      unordered_map<int, bool> stonePositions;
      for (auto s : stones) 
        stonePositions[s] = true;// We marked all the positions of the stones

      positions.push(0); //  First position is 0
      jumps.push(0); // First jump value is 0

      while (!positions.empty()) {
        int position = positions.top();
        positions.pop();
        int jump = jumps.top();
        jumps.pop();
        
        for (int i = jump - 1; i <= jump + 1; i++) { // We check for k-1,k,k+1
          if (i <= 0) continue; //if first stone we skip
          int nextPosition = position + i;// catch the current position

          if (nextPosition == lastStone) {
            return true; //if we arrive to the last, problem solved!
          } else if (stonePositions.find(nextPosition) != stonePositions.end()) {
            // this is important wee need to check if actually our map contains the nextPosition to check
             positions.push(nextPosition);
             jumps.push(i);
          }
        }
      }
      return false;
    }
};

int main() {
  Solution *s = new Solution();
  vector<int> stones{0,1,3,5,6,8,12,17};
  vector<int> stones2{0,1,2,3,4,8,9,11};
  cout << s->canCross(stones) << '\n';
  cout << s->canCross(stones2) << '\n';

  return 0;
}