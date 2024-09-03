#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define int long long

struct xiexie{

    ll dato;
    ll index;
    ll exit = -1;
};

int partition(vector <xiexie > &nums, int start, int end)
{
 
    int pivot = nums[start].dato;
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (nums[i].dato <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(nums[pivotIndex], nums[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (nums[i].dato <= pivot) {
            i++;
        }
 
        while (nums[j].dato > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(nums[i++], nums[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(vector<xiexie > &nums, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(nums, start, end);
 
    // Sorting the left part
    quickSort(nums, start, p - 1);
 
    // Sorting the right part
    quickSort(nums, p + 1, end);
}

int partition1(vector <xiexie > &nums, int start, int end)
{
 
    int pivot = nums[start].index;
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (nums[i].index <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(nums[pivotIndex], nums[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (nums[i].index <= pivot) {
            i++;
        }
 
        while (nums[j].index > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex && nums[i].index != nums[j].index) {
            swap(nums[i++], nums[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort1(vector<xiexie > &nums, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition1(nums, start, end);
 
    // Sorting the left part
    quickSort1(nums, start, p - 1);
 
    // Sorting the right part
    quickSort1(nums, p + 1, end);
}

void reverse(vector<xiexie > &nums, int m){
    vector<xiexie > copy(m);
    for (int i = 0; i < m; ++i){
        copy[i] = nums[i];
    }
    int cont = 0;
    for (int i = 0; i < m; ++i){
        nums[i] = copy[m-1 - cont];
        cont++;
    }
}


signed main(){

    ll n,m; cin >> n >> m;
    vector <xiexie > nums (n), cositas(m);
    for (int i = 0; i < n; ++i){
        cin >> nums[i].dato;
        nums[i].index = i;
    }
    for (int i = 0; i < m; ++i){ 
        cin >> cositas[i].dato;
        cositas[i].index = i;
    }

    quickSort(nums, 0, n - 1);
    quickSort(cositas, 0, m - 1);
  
    // for (int i = 0; i < n; ++i){
    //     cout << nums[i].dato << " ";

    // }
    //cout<<endl<<"----------------------------------------------------------------------------------------"<<endl;
    reverse(nums, n); reverse(cositas,m);

    // for (int i = 0; i < n; ++i){
    //     cout << nums[i].dato << " ";

    // }
    ll temp, indexxx;
    for (ll i = 0; i < m; ++i){ 

        temp = -1; indexxx = -1;
        for (int j = 0; j < n; ++j){
            if(cositas[i].dato == nums[j].dato){
                cositas[i].exit = nums[j].index + 1;
                nums[j].dato -= cositas[i].dato;
                quickSort(nums, 0, n - 1); reverse(nums, n);

                break;
            }
            else if(cositas[i].dato < nums[j].dato){
                temp = nums[j].dato; indexxx= j;
            }
            else{
                if(temp != -1 && indexxx != -1){
                    cositas[i].exit = nums[indexxx].index + 1;
                    nums[indexxx].dato -= cositas[i].dato;
                    quickSort(nums, 0, n - 1); reverse(nums, n);

                    break;
                }
            }
        }
        if(cositas[i].exit == -1){
            cositas[i].exit = 0;
        }
    }
    quickSort1(cositas, 0, m - 1);
    //cout<<endl<<"----------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i < m; ++i){ 
        cout<</*"dato: "<<cositas[i].dato<<"  index: "<<cositas[i].index<<"  exit: "<<*/cositas[i].exit/*<<endl*/<<" ";
        
    }
    


    return 0;
}