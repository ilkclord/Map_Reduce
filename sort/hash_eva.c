/*
 * =====================================================================================
 *
 *       Filename:  hash_eva.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  廿廿一年五月廿九日 十五時35分四秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"


void show_hash(int up , int low){
    int  a[top_n] ;
    for(int i = 0 ; i < top_n ; i++)
      a[i] = 0 ;
    for(int i = low ; i <= up ; i++){  
      a[dhash(i , up ,low)]++ ;
    }
    for(int i = 0 ;i <top_n ; i++)
      printf("%d" ,a[i]) ;
    printf("\n") ;
}

int main(int argc, char *argv[]){
    int up = atoi(argv[1]) ,low = atoi(argv[2]) ;
    printf("up : %d low : %d  up / low : %d\n" , up ,low ,up/low) ;
    for(int i = 0 ;up > low ; low++ , i++){
        printf("The %d th extension\n" , i) ;
        show_hash(up , low) ;
    }
    return 0 ;
}
