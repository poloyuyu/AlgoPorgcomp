#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define int long long

vector<vector<pair<ll, ll>>> G;
/*
 Description: Minimum spanning tree in $O(E log E)$
 Status: Tested
*/
struct union_find {
  vector<int> e;
  union_find(int n) { e.assign(n, -1); }
  int findSet (int x) { 
    return (e[x] < 0 ? x : e[x] = findSet(e[x]));
  }
  bool sameSet (int x, int y) { return findSet(x) == findSet(y); }
  int size (int x) { return -e[findSet(x)]; }
  bool unionSet (int x, int y) {
    x = findSet(x), y = findSet(y);
    if (x == y) return 0;
    if (e[x] > e[y]) swap(x, y);
    e[x] += e[y], e[y] = x;
    return 1;
  }
};
struct Edge {
  int a; int b; int w;
  Edge(int a_, int b_, int w_) : a(a_), b(b_), w(w_) {}
};

vector<Edge> tree;
bool c_edge(Edge &a, Edge &b) { return a.w < b.w; }
ll Kruskal() {
  int n = G.size();
  union_find sets(n);
  vector< Edge > edges;
  for(int i = 0; i < n; i++) {
    for(auto eg : G[i]) {
      // node i to node eg.first with cost eg.second
      edges.emplace_back(i, eg.first, eg.second);
    }
  }
  sort(edges.begin(), edges.end(), c_edge);
  int min_cost = 0;
  for(Edge e : edges) {
    if(sets.sameSet(e.a, e.b) != true) {
      tree.emplace_back(e.a, e.b, e.w);
      min_cost += e.w;
      sets.unionSet(e.a, e.b);
    }
  }
  return min_cost;
}



signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cout << fixed << setprecision(9);
    ll a,b;
    cin>>a>>b;
    ll c,d,e;
    G.resize(a);
 
    for(ll i = 0; i< b; i++){
        cin>>c>>d>>e;
        c--;d--;
        G[c].emplace_back(d,e);
        G[d].emplace_back(c,e);
 
 
    }
   
    return 0;
}