#include <bits/stdc++.h>


using namespace std;



struct SqrtDecomp {
    int n;
    int block_size;

    vector < int > a;

    vector < int > blocks ;

    int block ( int i) { return i / block_size ; }

    SqrtDecomp ( vector < int > &v, int _block_size = -1) {
        n = v. size () ;
        a = v;
        block_size = ( _block_size == -1 ? ceil ( sqrt (v. size () )) : _block_size ) ;
        blocks.assign(0, block_size );
        for ( int i = 0; i < n; i++) {
            blocks [ block (i) ] += a[i];
        }
    }

    int query ( int l, int r) {
        int sum = 0;
        int i = l;
        while (i <= r) {
            if(i % block_size == 0 && i + block_size - 1 <= r) {
                sum += blocks [ block (i) ];
                i += block_size ;
            } 
            else {
                sum += a[i];
                i ++;
            }
        }
        return sum ;
    }
    void update ( int i, int k) {
        a[i] = k;
        int begin_block = i - (i % block_size ) ;
        int end_block = begin_block + block_size ;
        blocks [ block (i)] = 0;
        for ( int i = begin_block ; i < end_block ; i ++){
            blocks [ block (i)] += a[i];
        }
    }
};

int main(){

    return 0;
}