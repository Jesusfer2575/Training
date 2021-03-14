//Knapsack Problem el problema de la mochila!
#include<stdio.h>
#include<algorithm>
#include <string.h>
using namespace std;
int G, MW, N, T, sum_values;
int dp(int,int);

struct Bag {
	int price, weight;
};
int weights[102];
int memo[1008][38];
Bag obj[1006];

int dp_bottom_up(int N, int weight) {
  int dp[N+1][weight+1];

  for (int i=0;i<=N;i++){
    for (int w=0;w<=weight;w++) {
      if (i == 0 || w == 0)
        dp[i][w] = 0;
    }
  }
}

int dp(int i, int total_weight) {
	if (memo[i][total_weight] != -1)
		return memo[i][total_weight];
	if (i >= N || total_weight <= 0)
		return 0;
	if (obj[i].weight > total_weight)
		return memo[i][total_weight] = dp(i+1, total_weight);
	else
	  return memo[i][total_weight] = max(
      dp(i + 1, total_weight),
      dp(i + 1, total_weight - obj[i].weight) + obj[i].price
    );
}

int main() {
  scanf("%d ", &T);
  while(T--) {
    scanf("%d ", &N);
    sum_values = 0;
    memset(memo, -1, sizeof(memo));
    for (int i=0;i<N;i++)
      scanf("%d %d ", &obj[i].price, &obj[i].weight);
    scanf("%d ", &G);
    for (int i=0;i<G;i++) {
      scanf("%d ", &MW);
      int maximum = dp(0, MW);
      sum_values += maximum;
    }
    printf("%d\n", sum_values);

  }
	return 0;
}
