#include <stdio.h>

//フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
  int i, j, l, pivot;

  if(n<=0) return;
// 先頭の要素をピボットとする
  pivot = A[0];
  for(i = j = l = 1; i < n; i++){
    if(A[i] <= pivot){
      int z = A[j+l-1];
      A[j+l-1] = A[i];
      A[i] = z;
      j++;
      if(A[i] == pivot){
        l++;
      }
    }
  }
  for(i = 0;i < l; i++){
    int z = A[i];
    A[i] = A[j-i-1];
    A[j-i-1]=z;
  }
  quick_sort(A, j-l);
  quick_sort(A+j, n-j);
  return;
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}
