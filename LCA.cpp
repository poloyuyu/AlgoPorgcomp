#include <bits/stdc++.h>

#define int long long
#define endl "\n"
using namespace std;

struct LCA {
  vector<vector<int>> T, parent;
  vector<int> depth, vis;
  int LOGN, V;
  // If WA, bigger logn?
  LCA(vector<vector<int>> &T, int logn = 20): T(T), LOGN(logn), vis(T.size()) {
    parent.assign(T.size()+1, vector<int>(LOGN, 0));
    depth.assign(T.size()+1, 0);
    // If is forest
    //for (int u = 0; u < T.size(); u++)
    //  if (!vis[u]) dfs(u);
  }
  void dfs(int u = 0, int p = -1) {
    vis[u] = true;
    for (int v : T[u]) {
      if (p != v) {
        depth[v] = depth[u] + 1;
        parent[v][0] = u;
        for (int j = 1; j < LOGN; j++)
          parent[v][j] = parent[parent[v][j-1]][j-1];
          dfs(v, u);
      }
    }
  }
  int query(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int k = depth[u]-depth[v];
    for (int j = LOGN - 1; j >= 0; j--)
      if (k & (1 << j))
        u = parent[u][j];
    if (u == v)
      return u;
    for (int j = LOGN - 1; j >= 0; j--) {
      if (parent[u][j] != parent[v][j]) {
        u = parent[u][j];
        v = parent[v][j];
      }
    }        
    return parent[u][0];
  }
};

signed main(){

    int n, q;
    cin>>n>>q;
    vector<vector<int>> datos(n);
    int a,b;
    for(int i = 1; i < n ; i++){
        cin>>a; a--;
        datos[i].push_back(a);
        datos[a].push_back(i);
        
    }
 
    LCA estructura(datos);
    estructura.dfs();
    while(q--){
        cin>>a>>b;a--;b--;
        cout<<estructura.query(a,b)+1<<"\n";
    }
    return 0;
}