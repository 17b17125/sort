#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int i, j, l, pivot;

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

  if(j-l<=k+1 && k+1<=j) return pivot;
  if(j < k+1) return quick_select(A+j, n-j, k-j);
  return quick_select(A+1, j-1-l, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  /*A[0]=8;
  A[1]=2;
  A[2]=3;
  A[3]=2;
  A[4]=3;
  A[5]=8;
  A[6]=10;
  A[7]=3;
  A[8]=11;
  A[9]=11;
  A[10]=10;
  for(i=1;i<11;i++){
    printf("%d: %d\n", i, quick_select(A,11,i));
  }*/
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
    //printf("%d th element is %d\n", i, quick_select(A, N, i));
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  for(i=0;i<N;i++) A[i] = 2;
  quick_select(A, N, 22);

  printf("done\n");
}
