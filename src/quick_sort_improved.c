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
  for(i = j = 1,l = 0; i < n; i++){
    if(A[i] < pivot){
      int z = A[i];
      A[i] = A[j];
      A[j] = A[j-l];
      A[j-l] = z;
      j++;
    }else if(A[i] == pivot){
      int z = A[j];
      A[j] = A[i];
      A[i] = z;
      l++;
      j++;
    }
  }
  i = A[0];
  A[0] = A[j-1];
  A[j-1] = i;
  quick_sort(A, j-1-l);
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

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  for(i=0;i<N;i++) A[i] = 2;
  quick_sort(A, N);
  //for(i=0;i<N;i++) printf("A[%d]: %d\n", i, A[i]);

  printf("done\n");
}
