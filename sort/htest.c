/*
 * =====================================================================================
 *
 *       Filename:  htest.c
 *
 *    Description:  Make a non-identical data stream with specific range with specific size 
 *
 *        Version:  1.0
 *        Created:  廿廿一年五月卅日 十四時廿分七秒
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
#include "top_insert.h"
#include "time_eva.h"
//#define test 100

/*
 * parse 1 -> k :  range 1 ~ k
 * parse 2 -> n :  n data
 */

int main(int argc , char * argv[]){
    int len = atoi(argv[1]) ;
    int * a = malloc(sizeof(int) * len); 
    int test = atoi(argv[2]) ;
    int * re = malloc(sizeof(int) * test) ;
    top_hash * t = malloc(sizeof(top_hash)) ;
    top_hash_init(t) ;
    for(int i= 0 ; i <  len; i++)//data range
      a[i] = i+1 ;
    for(int i = 0 ; i < test ; i++){//generating random data stream
      int k ;
      while(1){ // non-identical
        k = rand()%len;
        if(a[k] != 0)
          break ;
      }
      re[i] = a[k] ;
      a[k] = 0 ;
    }

    double in_s = now() ;
    for(int i = 0 ; i < test ; i++)
        in_insert(re[i]) ;
    double in_f = now() ;

    double hash_s = now() ;
    for(int i = 0 ; i < test ; i++)
        top_hash_insert(t ,re[i]) ;
    double hash_f = now() ;
    printf("\n\n");
    printf("Insertion : \n") ;
    in_info();
    printf("execution time : %g msec\n" ,in_f - in_s) ;
    printf("\nTop_hash :\n") ;
    top_hash_info(t, 0);
    printf("execution time : %g msec\n" , hash_f - hash_s) ;
    return 0 ;
}
