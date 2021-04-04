#include<iostream>
using namespace std;

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

      int parentA = find(a);
      int parentB = find(b);
      parent[parentA] = find(parentB);
    }
    void printSets() {
      for(int i = 1; i <= sets; i++)
        cout << parent[i] << ' ';
      cout << '\n';
    }
};

int main() {
  UnionFind *uf = new UnionFind();
  uf -> initialize(5);
  uf -> join(1, 2);
  uf -> join(4, 5);
  uf -> join(2, 5);
  uf -> printSets();
  return 0;
}