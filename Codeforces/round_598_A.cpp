#include<iostream>
using namespace std;
#define optimize_io ios_base::sync_with_stdio(false);cin.tie(0);

typedef long long int lli;

lli a, b, n, s;
int main() {
  optimize_io
  int q;

  cin >> q;
  while (q--) {
    bool flag = false;
    cin >> a >> b >> n >> s;
    
    if (n != 1) {
      if (s % n == 0){
        lli mul = a * n;
        if (mul < s){
          if (mul + b >= s) flag = true;
        } else {
          flag = true;
        }
      } else {
        lli mul = a * n;
        if (mul > s) {
          lli mod = s % n;
          if  (b >= mod) flag = true;
        } else {
          lli result = (a * n) + b;
          if (result >= s) flag = true;
        }

      }
    } else {
      if (a >= s or b >= s or ((a + b) >= s)) flag = true;
    }

    flag ? cout << "yes\n" : cout << "no\n";
  }

  return 0;
}