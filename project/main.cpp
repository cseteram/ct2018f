#include <cstdio>
#include <vector>
#include <utility>
#include "fibonacci_heap.hpp"
using namespace std;
typedef pair<int, int> pii;

vector<vector<pii>> g;

int main() {
  // n = number of node, m = number of edge
  int n, m;
  scanf("%d%d", &n, &m);
  // g = adjacent list of graph
  g = vector<vector<pii>>(n);
  for (int i = 0; i < m; ++i) {
    int s, e, x;
    scanf("%d%d%d", &s, &e, &x);
    g[s].emplace_back(e, x);
    g[e].emplace_back(s, x);
  }


  // ans = final answer
  int ans = -1;
  // merged = 1 if the node is already merged, 0 otherwise
  vector<int> merged(n);
  for (int phase = 0; phase < n - 1; ++phase) { // PHASE START
    // h = fibonacci heap
    FibonacciHeap<pii> h;
    // put unmerged nodes to heap, keep pointers in v
    vector<node<pii>*> v(n);
    for (int i = 0; i < n; ++i) {
      if (merged[i] == 0) {
        v[i] = h.insert(pii(0, i));
      }
    }
    // check = 0 if the node is still in heap, 0 otherwise
    vector<int> check(n);
    int s, t;
    printf("[MinimumCutPhase %d]\n", phase);
    printf("processing vertices in the order of the most tightly connectedness:\n");
    for (int i = 0; i < n - phase; ++i) {
      // pick the most tightly connected node, a
      // 1) since the fibonacci heap implementation is MIN heap,
      // we put weight as negative and remove the minimum one
      // 2) removeMinimum has amortized O(logV) time complexity => O(VlogV) per phase
      pii a = h.removeMinimum();
      int w = a.first;
      int here = a.second;
      if (i == n - phase - 2) s = here;
      if (i == n - phase - 1) t = here;
      check[here] = 1;
      printf("%d ", here);
      // update key of nodes inside fibonacci heap
      // 1) decreaseKey has amortized O(1) time complexity => O(E) per phase
      for (pii &p : g[here]) {
        int there = p.first;
        if (check[there] == 0 && merged[there] == 0) {
          int cost = p.second;
          h.decreaseKey(v[there], pii(v[there]->getValue().first - cost, there));
        }
      }
    }
    printf("\n");
    printf("last two nodes : s = %d, t = %d\n", s, t);

    // calculate the cut-of-the-phase, which is the cut (t, V-t)
    int cotp = 0;
    for (pii &p : g[t]) {
      cotp += p.second;
    }
    if (ans == -1) ans = cotp;
    else if (ans > cotp) ans = cotp;
    printf("the cut-of-the-phase = %d\n", cotp);

    // merge node s and t
    vector<pii> nn;
    for (pii &p : g[t]) {
      if (p.first != s) {
        nn.emplace_back(p.first, p.second);
      }
    }
    for (pii &p : g[s]) {
      if (p.first != t) {
        nn.emplace_back(p.first, p.second);
      }
    }
    g[s] = nn;
    for (int i = 0; i < n; ++i) {
      if (merged[i] == 0) {
        for (pii &p : g[i]) {
          if (p.first == t) p.first = s;
        }
      }
    }
    merged[t] = 1;
    printf("merged node %d to node %d\n", t, s);
  } // PHASE END
  // one phase O(E+VlogV), V phases => O(VE + V^2logV) total time complexity
  printf("\nMIN CUT = %d\n", ans);
  return 0;
}
