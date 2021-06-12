/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  廿廿一年六月七日 廿二時43分廿八秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "queue.h"
#include <pthread.h>
#include <stdatomic.h>

#define test 200
#define move 100
int m = move ;
int v[move] ;
int rm = 0 , wm = 0 ;
int i = 0 ;
pthread_t thread[3] ;
pthread_mutex_t  lock;

struct tn{
  queue * q ;
  int id ;
} typedef id ;

void w(id * id){
  queue *  q = id->q ;
  for( ; i < test ;){
    info * tmp ;
    job * tmp0 ;
    int ji = atomic_fetch_add(&i , 1) ;
    //printf("%d\n" ,ji);
    if(!info_init(&tmp , ji , ji + 1 , "testing"))
      printf("ops\n");
    if(!job_init(&tmp0 , tmp , &foo))
      printf("oops\n");
    while(atomic_load(&m) > 0){
       
       if(!queue_w( q,tmp0,id->id , ji )){
         //atomic_fetch_sub(&m ,1) ;
         //printf("w_blocking\n") ;
        //queue_state(q) ;
         }
       else{
         //job_info(tmp0) ;
         //atomic_fetch_sub(&m ,1) ;
         atomic_fetch_add(&wm , 1);
         break ;
       }
    }
    if(m <= 0 )
      break ;
  }

}
void r(queue * q){
    job * j ;
    while(atomic_load(&m) > 0){
      if(!queue_r(q , &j)){
           //printf("r_blocking %d\n" , q->entry) ;
            //queue_state(q) ;a
      }
      else{
        //job_info(j) ;
       rm++ ;
       atomic_fetch_sub(&m ,1) ;
      }
    }
    load(q , 0) ;
}

int main(){
  queue *t ;
  queue_init(&t) ;
  id * a = malloc(sizeof(id)) ;
  id * b = malloc(sizeof(id)) ;
  a->q = b->q = t ;
  a->id = 1 ;
  b->id = 2 ;
  for(int j = 0 ; j <move ; j++)
    v[j] = 0 ;
  pthread_create(&thread[0] , NULL ,(void *)r ,t );
  pthread_create(&thread[1] , NULL , (void *)w  , a) ;
  pthread_create(&thread[2] , NULL , (void *)w , b) ;
  pthread_join(thread[0] , NULL) ;
  pthread_join(thread[1] , NULL) ;
  pthread_join(thread[2] , NULL) ;
  //printf("m : %d rm : %d . wm : %d \n" ,m , rm ,wm) ;
  //queue_state(t) ;
  //queue_info(t) ;
  //for(int j  =0 ; j <move ; j++)
    //printf("%d" , v[j]) ;
  return 1;
}
