#include <iostream>
#include <vector>

using namespace std;

#define ll long long


struct SegmentTree {

    int n; // cantidad de elementos en el arreglo original
    vector < long long > ST; // vector que nos ayudara a crear la estructura
    
    // puntero funcion que ayuda a resolver el problema
    long long (* merge )( long long , long long ) ;
    // void build (int index , int l, int r, vector < long long > & values ){
    //     // funcion que construye el segment tree
    // }
    // SegmentTree (vector < long long > & values , long long (* merge_ ) ( long long a, long long b) ){
    //     // constructor del segment tree
    // }
    // long long query ( int i, int j){
    //     // recibe un i y j correspondientes al intervalo consultado
    // }
    // long long query ( int l, int r, int index , int i, int j) {
    //     // la real funcion que responde la consulta
    // }
    // void update ( int pos , long long val ){
    //     // recibe una posicion y actualiza el valor en esa posicion
    // }
    // void update ( int l, int r, int index , int pos , long long val ){
    //     // la real funcion que actualiza el valor dada una posicion
    // }

    void build (int index , int l, int r, vector < long long > & values ){
        // funcion que construye el segment tree
        if(l == r){
            ST[ index ] = values [l];
        } 
        else {
            // hijo izquierdo
            build ( index * 2, l, (r + l) / 2, values );
            // build derecho
            build ( index * 2 + 1 , (r + l) / 2 + 1 , r, values );
            // padre = hijo izq + hijo der
            ST[ index ] = merge (ST[ index * 2] , ST[ index * 2 + 1]) ;
        }
    }
    SegmentTree (vector < long long > & values , long long (* merge_ ) ( long long a, long long b) ){
        // constructor del segment tree
        merge = merge_ ;
        n = values.size () ;
        ST. resize (4 * n + 3) ;
        build (1 , 0, n - 1, values ) ;
    }

    long long query ( int i, int j){
        // recibe un i y j correspondientes al intervalo consultado
        return query (0 , n - 1 , 1 , i, j) ;
    }

    long long query ( int l, int r, int index , int i, int j) {
        // la real funcion que responde la consulta
        if(l >= i and r <= j) return ST[ index ];

        int mid = (r + l) / 2;
        // solo consulta al lado derecho
        if( mid < i){
            return query ( mid + 1, r, index * 2 + 1, i, j);
            // solo consulta al lado izquierdo
        } else if( mid >= j){
            return query (l, mid , index * 2, i, j);
        } else {
            // consulta hacia ambos hijos
            return merge ( query (l, mid , index * 2 , i, j) ,
                query ( mid + 1, r, index * 2 + 1, i, j));
        }
    }
    // update
    void update ( int pos , long long val ){
        // recibe una posicion y actualiza el valor en esa posicion
        update (0 , n - 1, 1, pos , val );

    }
    void update ( int l, int r, int index , int pos , long long val ){
        // la real funcion que actualiza el valor dada una posicion
        if(r < pos || pos < l) return ;
        if(l == r){
            ST[ index ] = val ;
        } else {
            int mid = (r + l) / 2;
            // buscar posicion en arbol izquierdo
            update (l, mid , index * 2, pos , val );
            // buscar posicion en arbol derecho
            update (mid + 1 , r, index * 2 + 1, pos , val );

            ST[ index ] = merge (ST[ index * 2] , ST[ index * 2 + 1]) ;
        }
    }
    // asumiendo que esta todo el codigo del Segment Tree aqui

    // la funcion que vamos a utilizar para responder nuestra pregunta

    
};

long long mininum ( long long a, long long b) { return min (a,b); }
    




int main(){

    int n; cin >> n;
    vector <ll > nums (n);
    for (int i = 0; i < n; ++i) cin >> nums [i];
    
    SegmentTree arbol (nums , mininum );
    
    int q; cin >> q;

    while (q--) {
        int tipo ; cin >> tipo ;
        if( tipo == 1) { // query
            int i, j; cin >> i >> j;
            cout << arbol.query (i, j) << "\n";
        } else if( tipo == 2) { // update
            int pos , val ; cin >> pos >> val ;
            arbol.update (pos , val );
        }
    }
    //cout<<min()


    return 0;
}