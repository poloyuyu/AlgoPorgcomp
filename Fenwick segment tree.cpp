#include <bits/stdc++.h>

using namespace std;

#define ll long long

struct fenwick_tree {

    vector <int > bit ; int n;

    fenwick_tree ( int n): n(n) { bit . assign (n, 0) ; }

    fenwick_tree ( vector <int > &a): fenwick_tree (a. size () ) {
        for ( size_t i = 0; i < a. size () ; i ++)
            add (i, a[i]) ;
    }
    int sum( int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1) ) - 1)
            ret += bit [r];
        return ret ;
    }
    int sum( int l, int r) {
        return sum (r) - sum (l - 1) ;
    }
    void add ( int idx , int delta ) {
        for (; idx < n; idx = idx | ( idx + 1) )
            bit [ idx ] += delta ;
    }
};

struct fenwick_tree_2d {
    int N, M;
    vector < vector < int >> BIT ;
    fenwick_tree_2d ( int N, int M): N(N) , M(M) {
        BIT.assign (N + 1 , vector < int > (M + 1, 0) );
    }
    void update ( int x, int y, int v) {
        for (int i = x; i <= N; i += (i & -i))
        for (int j = y; j <= M; j += (j & -j))
        BIT [i][j] += v;
    }
    int sum( int x, int y) {
        int s = 0;
        for (int i = x; i > 0; i -= (i & -i) )
        for (int j = y; j > 0; j -= (j & -j) )

        s += BIT [i][j];
        return s;
    }
    int query ( int x1 , int y1 , int x2 , int y2) {
        return sum (x2 , y2) - sum(x2 , y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1) ;
    }
};

int main(){

    ll numero_cosas, numero_acciones;

    cin>>numero_cosas>>numero_acciones;
    vector <int> nums(numero_cosas);

    for (ll i = 0; i < numero_cosas; ++i) cin >> nums [i];

    fenwick_tree arbol1d(nums);



    


    while(numero_acciones--){
        int tipo ; cin >> tipo ;
        if( tipo == 1) { // query
            int i, j; cin >> i >> j;
            cout << arbol1d.sum (i, j) << "\n";
        } else if( tipo == 2) { // update
            int pos , val ; cin >> pos >> val ;
            arbol1d.add(pos,val);
        }
    }

    return 0;
}
