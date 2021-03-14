#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
using namespace std;

class Solution {
  private:
    bool visited[1000];
    stack<int> s;

    void dfs(int origin) {
      visited[origin] = true;
      s.push(origin);

      while(!s.empty()) {
        int vertex = s.top();
        s.pop();

        for(int i = 0; i < graph[vertex].size(); i++){
          int node = graph[vertex][i];
          if(!visited[node]) {
            visited[node] = true;
            s.push(node);
          }
        }
      }
    }
  
  public:
    vector<int>graph[1000];
    int edges, vertexes;

    void initialize() {
      
      edges = 3;
      vertexes = 4;

      fill(visited, visited + vertexes, false);

      dfs(1);

      for (int i = 1; i <= vertexes; i++) 
        cout << visited[i] << "\n";
      
    }
};

int main() {
  Solution *s = new Solution();

  int edges = 3;
  int x, y;
  for (int i = 0 ; i < edges ; i++) {
    scanf(" %d %d", &x, &y);
    s->graph[x].push_back(y);
    s->graph[y].push_back(x);
  }
  s->initialize();

  return 0;
}