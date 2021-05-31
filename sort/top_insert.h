/*
 * =====================================================================================
 *
 *       Filename:  top_insert.h
 *
 *    Description:  Simple insertion to find top 10
 *
 *        Version:  1.0
 *        Created:  廿廿一年五月卅一日 十六時四分廿七秒
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


#define top 10


int top_arr[10] ;
int in_init(){
    for(int i = 0 ; i < top ; i++)
      top_arr[i] = 0 ;
    return 1 ;
}

int in_insert(int input){
  int tmp ;
  for(int i = 0 ;i < top ;i++){
    if(input > top_arr[i]){
      tmp = top_arr[i] ;
      top_arr[i] = input ;
      in_insert(tmp) ;
      break ;
    }
  }
  return 1 ;
}

void in_info(){
  for(int i= 0; i< top ; i++)
    printf(" %d", top_arr[i]) ;
  printf("\n") ;
}
 
