/*
 * =====================================================================================
 *
 *       Filename:  sample.c
 *
 *    Description:  Find top10 using hash
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
#define wide top_n

int top_hash_re() ;
struct arr{
    int node[wide] ;
    int count ;
} typedef bracket ; 

struct top{
    bracket * table ;
    int up  ;
    int low ;
    int current ;
} typedef top_hash;
/*
 * Changable hashing funtion
 *
 */
int dhash(int input , int up , int low){
  if(input < low)
    return top_n + 1 ;
  if(input >= up)
    return top_n - 1 ;
  int upper = (input - low +1) * top_n ;
  int lower = (up - low + 1) ;
  if(upper % lower > 0)
    return upper / lower ;
  else
    return upper / lower -1 ;
}
/*
 * Find the smallest element in the list by traverse the whole table
 */
int low_update(bracket * table , int low){
    int low_next = table[top_n - 1].node[0] ;
    for(int i = 0 ; i < top_n ; i++){
        if(table[i].count != 0){
          for(int j  = table[i].count -1 ; j >= 0 ;j--){
            if(table[i].node[j] == low){
              table[i].count-- ;
              table[i].node[j] = 0 ;
            }
            if(low_next > table[i].node[j] && table[i].node[j] != low && table[i].node[j] > 0)
                low_next = table[i].node[j] ;
          }
        }
    }
    return low_next ;  
}
/*
 * Initialize the top_hash
 */
int htable_init(bracket * a){
    for(int i = 0 ;i < top_n ; i++){
      for(int j = 0 ; j< wide ; j++)
        a[i].node[j] = 0 ;
      a[i].count = 0 ;
    }
    return 0;
}

int top_hash_init(top_hash * a){
    a->table = malloc(sizeof(bracket) * top_n) ;
    htable_init(a->table) ;
    a->up = 0 ;
    a->low = 0 ;
    a->current = 0 ;
    return 1 ;
}
int top_hash_reinit(bracket * table){
    for(int i = 0 ;i < top_n ; i++){
      for(int j = 0 ; j< wide ; j++)
        table[i].node[j] = 0 ;
      table[i].count = 0 ;
    }
    return 0;
}
/*
 * hashing into table and also sort it
 * Return value
 * 0 : the table is full
 * count - table->count : the change of the count
 */
int top_hash_sort(bracket * table, int index ,int input , int low){ // address , index , data
    int count = table->count ;
    if(table->count++ == wide)
      return 2 ;
    else{
      for(int i = 0 ; i < wide ; i++){
        if(input > table->node[i]){
            int tmp = table->node[i] , tmp2;
            table->node[i] = input;
            int j ;
            for(j = ++i ; j < table->count ; j++){
              tmp2 = table->node[j] ;
              if(tmp < low)
                break ;
              table->node[j] = tmp ;
              tmp = tmp2 ;
            }
            break ;
        }
      }
      return  1 ;
    }
}
/*
 * Main insertion
 * Return value
 * @1 : simple hashing
 * @2 : needed restruct
 * @0 : discard
 */
int top_hash_insert(top_hash * top , int input){
   //upper range
   if(input > top->up)
     top->up = input ;

   /*
    * When the table isn't full
    */
   if(input < top->low  && top->current < 10)
     top->low = input ;
   // discard
   if(input < top->low)
     return 0 ;
   // When there are 2 elements ,get the range
   if(!top->low && top->current == 1)
     top->low = low_update(top->table , top->low) ;

   // The table is full
   if(top->current == top_n){
     top->current-- ;
     top->low = low_update(top->table , top->low) ;
     if(top->low > input)
       top->low = input ;
   }
   int index = dhash(input , top->up , top->low) ;
   int change = top_hash_sort( &top->table[index] , index ,input ,top->low) ;
   if(change == 2){
     printf("re\n\n");
     return 2 ; 
   }
   top->current += change ;
   return 1 ;
}
/* If the collision list is full reconstruct the hash table
 *
 *
 */
int top_hash_re(top_hash * top_re){
    int count = 0 ;
    int tmp[top_n] ;
    while(count < top_n){
        for(int i = 0 ; i < top_n ; i++){
           for(int j = 0 ;j < top_re->table[i].count ; j++){
               tmp[count++] = top_re->table[i].node[j] ;
            }       
        }
    }
    top_hash_reinit(top_re->table) ;
    for(int i = 0  ; i < top_n ; i++)
      top_hash_insert(top_re , tmp[i]) ;
}
/*
 * Debug : )
 */
void top_hash_info(top_hash * top , int add){
  printf("up : %d , low : %d , current : %d , insert : %d\n" , top->up , top->low , top->current ,add) ;
  for(int i = 0 ; i < top_n ; i++){
    printf("%d th bracket :"  ,i );
    for(int j = 0 ; j < wide ; j++){
      printf(" %d" , top->table[i].node[j]) ;
    }
    printf("count : %d\n" , top->table[i].count) ;
  }
}
