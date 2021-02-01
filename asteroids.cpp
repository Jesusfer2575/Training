/*
 * Problem: Asteroid Collision
 * From: https://leetcode.com/problems/asteroid-collision/submissions/
 * Level: Medium
**/
#include<iostream>
#include<vector>
#include<stack>
using namespace std;

vector<int> asteroidCollision(vector<int>& asteroids) {
  vector<int> solution;
  stack<int> stk;
  int n = asteroids.size();

  for (auto &asteroid : asteroids) {
    if (asteroid > 0) { //positive
      stk.push(asteroid);
    } else {// negative
      int abs_asteroid = -asteroid;
      if (stk.empty()) solution.push_back(asteroid);
      while (!stk.empty()) {
        int top = stk.top();
        if (abs_asteroid > top) {
          stk.pop();
        } else if (top > abs_asteroid) {
          break;
        } else if (top == abs_asteroid){
          stk.pop();
          break;
        }
        if (stk.empty()) solution.push_back(asteroid);
      }
    }
  }
  vector<int> positivesInStack;
  while (!stk.empty()) {
    int top = stk.top();
    stk.pop();
    positivesInStack.push_back(top);
  }
  reverse(positivesInStack.begin(), positivesInStack.end());
  solution.insert( solution.end(), positivesInStack.begin(), positivesInStack.end() );
  return solution;
}

int main() {
  vector<int> test{5,10,-5}; //pass
  vector<int> test2{8, -8}; // pass
  vector<int> test3{10,2,-5}; //pass
  vector<int> test4{-2,-1,1,2}; //pass
  vector<int> test5{-2,-1,1,2,-1,-2,3,4,13}; //pass
  vector<int> solution = asteroidCollision(test5);
  for (auto &i : solution) cout << i << " ";
  return 0;
}