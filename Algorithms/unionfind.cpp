#include<iostream>
using namespace std;

// Documentation:
// https://docs.google.com/presentation/d/1KMhJ3C77TuW2E0685BYZCwoykPzf-95n1CW3n8ziGoA/edit#slide=id.p
// Problems to solve:
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=636&page=show_problem&problem=734
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=636&page=show_problem&problem=2737
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=636&page=show_problem&problem=1626
// Find more in: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=636

class UnionFind {
  int* parent;
  int sets;
  public:
    void initialize(int n){
      sets = n;
      parent = new int[n];
      for(int i = 0; i <= n; i++)
        parent[i] = i;
    }
    int find(int x) {
      if (parent[x] == x) return x;
      return parent[x] = find(parent[x]);
    }
    bool areJoined(int a, int b) {
      return (find(a) == find(b)) ? true:false;
    }
    void join(int a, int b) {
      if (areJoined(a, b)) return;

      int parentA = find(a); // 0
      int parentB = find(b); // 1
      parent[parentA] = parentB;
    }
    void printSets() {
      for(int i = 1; i <= sets; i++)
        cout << parent[i] << ' ';
      cout << '\n';
    }
    int numberOfSets() {
      int number = 0;
      for(int i = 1; i <= sets; i++)
        if (parent[i] == i) number++;
      return number;
    }
};

int main() {
  UnionFind *uf = new UnionFind();
  uf -> initialize(5);
  uf -> join(1, 2);
  uf -> join(3, 5);
  // {1,2} {3, 5} {4}
  // uf -> join(2, 5);
  uf -> printSets();
  cout << uf -> numberOfSets() << "\n";
  return 0;
}