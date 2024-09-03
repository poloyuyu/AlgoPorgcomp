#include <bits/stdc++.h>

#define ll long long

using namespace std;

/*
 *Description:* Segment tree but with range updates, build $O(n)$, query and update $O(log n)$
 *Status:* Highly tested
*/
template<
  class T1, // answer value stored on nodes
  class T2, // lazy update value stored on nodes
  T1 merge(T1, T1), 
  void pushUpd(T2 /*parent*/, T2& /*child*/, int, int, int, int), // push update value from a node to another. parent -> child
  void applyUpd(T2, T1&, int, int)           // apply the update value of a node to its answer value. upd -> ans
>
struct segment_tree_lazy{
  vector<T1> ST; vector<T2> lazy; vector<bool> upd;
  int n;
  void build(int i, int l, int r, vector<T1>&values){
    if (l == r) {
      ST[i] = values[l];
      return;
    }
    build(i << 1, l, (l + r) >> 1, values);
    build(i << 1 | 1, (l + r) / 2 + 1, r, values);
    ST[i] = merge(ST[i << 1], ST[i << 1 | 1]);
  }
  segment_tree_lazy(vector<T1>&values){
    n = values.size();
    ST.resize(n << 2 | 3);
    lazy.resize(n << 2 | 3);
    upd.resize(n << 2 | 3, false);
    build(1, 0, n - 1, values);
  }
  segment_tree_lazy(){}
  void push(int i, int l, int r){
    if (upd[i]){
      applyUpd(lazy[i], ST[i], l, r);
      if (l != r){
        if (!upd[i << 1])
          lazy[i << 1] = lazy[i];
        else
          pushUpd(lazy[i], lazy[i << 1], l, r, l, (l + r) / 2);
        if (!upd[i << 1 | 1])
          lazy[i << 1 | 1] = lazy[i];
        else
          pushUpd(lazy[i], lazy[i << 1 | 1], l, r, (l + r) / 2 + 1, r);
        upd[i << 1] = 1;
        upd[i << 1 | 1] = 1;
      }
      upd[i] = false;
    }
  }
  void update(int i, int l, int r, int a, int b, T2 &u){
    if (l >= a and r <= b){
      if (!upd[i]) lazy[i] = u;
      else pushUpd(u, lazy[i], a, b, l, r);
      upd[i] = true;
    }
    push(i, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) return;
    update(i << 1, l, (l + r) >> 1, a, b, u);
    update(i << 1 | 1, (l + r) / 2 + 1, r, a, b, u);
    ST[i] = merge(ST[i << 1], ST[i << 1 | 1]);
  }
  void update(int a, int b, T2 u){
    if (a > b){
      update(0, b, u);
      update(a, n - 1, u);
      return;
    }
    update(1, 0, n - 1, a, b, u);
  }
  T1 query(int i, int l, int r, int a, int b){
    push(i, l, r);
    if (a <= l and r <= b)
      return ST[i];
    int mid = (l + r) >> 1;
    if (mid < a)
      return query(i << 1 | 1, mid + 1, r, a, b);
    if (mid >= b) 
      return query(i << 1, l, mid, a, b);
    return merge(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
  }
  T1 query(int a, int b){
    if (a > b){
      return merge(query(a, n - 1), query(0, b));
    }
    return query(1, 0, n - 1, a, b);
  }
};

long long merge ( long long a, long long b){
    return min(a , b);
}

void pushUpd ( long long u1 , long long &u2 , int l1 , int r1 , int l2 , int r2){
    u2 += u1;
}

void applyUpd ( long long u, long long &v, int l, int r){
    v += (r - l + 1) * u;
}

    

int main () {
// se asume que aqui se setea todo lo previo para el problema
    ll n; cin >> n;
    vector <ll > nums (n);
    for (int i = 0; i < n; ++i) cin >> nums [i];
    segment_tree_lazy < long long , long long , merge , pushUpd , applyUpd > arbol( nums );
    int q; cin >> q;

    while (q--) {
        int tipo ; cin >> tipo ;
        if( tipo == 1) { // query
            int i, j; cin >> i >> j;
            cout << arbol.query(i, j) << "\n";
        } else if( tipo == 2) { // update
            int pos_inicial , pos_final , cantidad_sumada ; cin >> pos_inicial >> pos_final >> cantidad_sumada ;
            arbol.update(pos_inicial, pos_final, cantidad_sumada);
        }
    }

    return 0;
}