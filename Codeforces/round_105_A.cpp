#include<iostream>
#include<stack>
using namespace std;
#define optimize_io ios_base::sync_with_stdio(false);cin.tie(0);

int t;
string s;

bool isRegular(string s) {
  stack<char> stk;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(')
      stk.push('(');
    else {
      if (!stk.empty()) stk.pop();
      else return false;
    }
  }
  return stk.empty() ? true:false;
}

bool checkAllChances(string s) {
  string parenthesis;
  for (int msk = 0; msk < (1 << 3); msk++) {
    parenthesis.clear();
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == 'A')
        msk & (1 << 0) ? parenthesis.push_back('(') : parenthesis.push_back(')');
      else if (s[i] == 'B') 
        msk & (1 << 1) ? parenthesis.push_back('(') : parenthesis.push_back(')');
      else 
        msk & (1 << 2) ? parenthesis.push_back('(') : parenthesis.push_back(')');
    }
    bool ans = isRegular(parenthesis);
    if (ans) return ans;
  }
  return false;
}

int main() {
  optimize_io

  cin >> t;
  while(t--) {
    cin >> s;
    checkAllChances(s) ? cout << "YES\n" : cout << "NO\n";
  }

  return 0;
}