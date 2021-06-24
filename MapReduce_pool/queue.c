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
pthread_t thread[4] ;
pthread_mutex_t  lock;
int l = 1 ;
struct tn{
  queue * q ;
  int id ;
} typedef id ;

void w(id * id){
  queue *  q = id->q ;
  for( ; q->mode == act ;){
    info * tmp ;
    job * tmp0 ;
    int ji = atomic_fetch_add(&i , 1) ;
    //printf("%d\n" ,ji);
    if(!info_init(&tmp , ji , ji + 1 , "testing"))
      printf("ops\n");
    if(!job_init(&tmp0 , tmp , &foo))
      printf("oops\n");
    while(!queue_w( q,tmp0,id->id , ji ) && (q->mode == act)) ;
    if(m <= 0 )
      break ;
  }
  if(atomic_load(&q->mode)== act && atomic_fetch_sub(&l  , 1)){
        queue_stop(q , 1) ;
  }
  printf("done\n") ;
}
void r(queue * q){
    job * j  = NULL;
    while(atomic_load(&m) > 0){
       while(!queue_r(q , &j) && (q->mode == act)) ;
         //printf("r") ;
       rm++ ;
       atomic_fetch_sub(&m ,1) ;
       if(j != NULL){
        job_destroy(j);
        j = NULL ;
       }
    }
    if(atomic_load(&q->mode) == act && atomic_fetch_sub(&l  , 1))
        queue_stop(q , 1) ;
    printf("dones\n") ;
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
  pthread_create(&thread[3] , NULL , (void *)r , t) ;
  pthread_join(thread[3] , NULL) ;
  pthread_join(thread[0] , NULL) ;
  pthread_join(thread[1] , NULL) ;
  pthread_join(thread[2] , NULL) ;
  //printf("m : %d rm : %d . wm : %d \n" ,m , rm ,wm) ;
  queue_state(t) ;
  queue_info(t) ;
  free(a) ;
  free(b) ;
  queue_destroy(t) ;
  //for(int j  =0 ; j <move ; j++)
    //printf("%d" , v[j]) ;
  return 1;
}
