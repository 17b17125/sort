#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int i, j, tmp,pivot;
  // 先頭の要素をピボットとする
  pivot = A[0];
  if(n<=5){
    for(i = j = 1; i < n; i++){
      if(A[i] <= pivot){
        int z = A[j];
        A[j] = A[i];
        A[i] = z;
        j++;
      }
    }
    if(j == k+1) return pivot;
    if(j < k+1) return quick_select(A+j, n-j, k-j);
    return quick_select(A+1, j-1, k);
  }else{
    i = 1;
    while(5*i < n){
      tmp = quick_select(A+5*(i-1), 5, 5/2);  //長さ5の部分配列の中で3番目に小さい数(中央値)
      for(j=0; j<5; j++){                     //配列の左に中央値を詰めていく
        if(A[5*(i-1)+j] == tmp){
          tmp = A[i-1];
          A[i-1] = A[5*(i-1)+j];
          A[5*(i-1)+j] = tmp;
          break;
        }
      }
      i++;
    }
    tmp = quick_select(A+5*(i-1), n%5, n%5/2);
    for(j=0; j<n%5; j++){                   //部分配列の先頭にその中央値を置く
      if(A[5*(i-1)+j] == tmp){
        tmp = A[i-1];
        A[i-1] = A[5*(i-1)+j];
        A[5*(i-1)+j] = tmp;
        break;
      }
    }
    pivot = quick_select(A, i , i/2);                //各部分配列の中央値でできた長さceil(n/5)の配列の中央値をピボットとして選択
    for(j=0; j<i; j++){
      if(A[j] == pivot){
        tmp = A[j];
        A[j] = A[0];
        A[0] = tmp;
      }
    }
    for(i = j = 1; i < n; i++){
      if(A[i] <= pivot){
        int z = A[j];
        A[j] = A[i];
        A[i] = z;
        j++;
      }
    }
    if(j == k+1) return pivot;
    else if(j < k+1) return quick_select(A+j, n-j, k-j);
    else return quick_select(A+1, j-1, k);                //探している値より大きい部分がなくなっただけだから順位は変わらない
  }
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
