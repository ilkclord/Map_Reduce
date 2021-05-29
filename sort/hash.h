/*
 * =====================================================================================
 *
 *       Filename:  sample.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  廿廿一年五月廿九日 十三時十九分46秒
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

#define top_n 10

struct top{
    int ** hash_table ;
    int up ;
    int low ;
    int count ;
} typedef top_hash;

int dhash(int input , int up , int low){
  if(input < low)
    return top_n + 1 ;
  if(input > up)
    return top_n - 1 ;
  int upper = (input - low +1) * top_n ;
  int lower = (up - low + 1) ;
  if(upper % lower > 0)
    return upper / lower ;
  else
    return upper / lower -1 ;
}

int hash_table_init(int ** a){
    a = malloc(sizeof(int) * top_n) ;
    for(int i = 0 ; i < top_n ; i++)
      a[i] = malloc(sizeof(int)* 2);
    for(int i = 0 ;i < top_n ; i++){
      a[i][1] = a[i][0] = 0 ;
    }
    return 0;
}

int top_hash_init(top_hash * a ){
    a = malloc(sizeof(top_hash)) ;
    hash_table_init(a->hash_table) ;
    a->up = 0 ;
    a->low = 0 ;
    a->count = 0 ;
    return 1 ;
}

int top_hash_insert(int ** hash_table , int index ,int input){
    if(hash_table[index][1] != 0)
      return 0 ;
    else if (hash_table[index][0] == 0){
      hash_table[index][0] = input ;
      return 1 ;
    }
    else if (hash_table[index][0] != 0){
      if(hash_table[index][0] < input){
        hash_table[index][1] = hash_table[index][0] ;
        hash_table[index][0] = input ;
      }
      else 
        hash_table[index][1] = input ;
      return 2 ;
    }
}

