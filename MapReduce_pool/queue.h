/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  Job queue of MapReduce Model
 *
 *        Version:  1.0
 *        Created:  廿廿一年六月七日 〇時49分廿二秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

/*
 * Check
 * user define here
 */

#define rbuffer_s 16
#define readable 1
#define writing  0
#define raw      2

pthread_mutex_t p ;
uint8_t mask = 16 ;
uint8_t wmask = 15 ;
struct input{
    int start ;
    int end ;
    char * pwd ;
}typedef info ;

typedef int func(info * i) ;

int foo(info * i){
  //printf("foo %d \n" , i->start + i->end) ;
  return 1 ;
}

struct job{
    info * data ;
    func * func ;
} typedef job;

struct jobqueue{
    job * buffer[rbuffer_s] ;
    uint8_t state[rbuffer_s] ;
    uint8_t read ;
    uint8_t write ;
    uint8_t entry ;
    uint8_t load ;
    uint8_t round ;
} typedef queue ;

uint8_t queue_state(queue * q) ;
uint8_t queue_info(queue * q) ;
uint8_t info_init(info ** i , int a ,int b ,char * pwd){
    *i = malloc(sizeof(info)) ;
    if(!i)
      return 0 ;
    (*i)->start = a;
    (*i)->end = b ;
    (*i)->pwd = pwd ;
    return 1 ;
}

uint8_t job_init(job ** j , info * i , func * f){
  *j = malloc(sizeof(job)) ;
  if(!j)
    return 0 ;
  (*j)->data = i ;
  (*j)->func = f ;
  return 1 ;
}

uint8_t queue_init(queue ** q){
    *q = malloc(sizeof(queue)) ;
    if(!q)
      return 0 ;
    pthread_mutex_init(&p , NULL) ;
    (*q)->read = 0 ;
    (*q)->write = 0 ;
    (*q)->entry = 0 ;
    (*q)->round = 0 ;
    (*q)->load = 1 ;
    for(int i = 0 ; i < rbuffer_s ; i++)
      (*q)->state[i] = raw ;
    return 1 ;
}

uint8_t load(queue * q ,int a){
  q->load = a ;
  return 1 ;
}
uint8_t queue_w(queue * q , job * j , int id , int ji){
    if(( q->entry/*  atomic_load(&q->entry)*/ & mask)){
      //printf("oops") ;
      return 0 ;
     }
    atomic_fetch_add(&q->entry , 1) ;
     int ro = q->round;
    int w  = atomic_fetch_add(&q->write , 1) ;
    int w2 = w ;
    w = w & wmask ;
    /*  if(w == 15){
      atomic_store(&q->write , 0) ;
      //ro = atomic_fetch_add(&q->round , 1) ;
    }
    else if (w > 15){
      printf("largeer w : %d\n" , w) ;
      //ro = atomic_fetch_add(&q->round , 1) ;
      w = 0 ;
    }*/

    int out = 0 , r ;
    while(atomic_load(&q->state[w]) != raw){
      if(!out){
      //pthread_mutex_lock(&p) ;
      r= atomic_load(&q->read) & wmask;
      //printf("shit ! ow : %d  w : %d , r : %d data : %d\n" ,w2 , w ,r ,j->data->start) ;
      //queue_state(q) ;
      //queue_info(q) ;
      //printf("---------\n") ;
      //pthread_mutex_unlock(&p) ;
      }
      out++ ;
      if(!q->load ){
        atomic_fetch_sub(&q->entry , 1) ;
        /*  
        queue_state(q) ;
        printf("                                                                  time out\n") ;
        printf(" ow : %d  w : %d , r : %d data : %d\n" ,w2 , w ,r ,j->data->start) ;
        queue_state(q) ;
        queue_info(q) ;
        */
        return 0 ; 
      }
    };
    atomic_store(&q->state[w] , writing) ;
   


    q->buffer[w] = j ;
    if(out > 1000 ){
      //queue_state(q) ;
      //queue_info(q) ;
      
      //printf("success write\n") ;
    }

    atomic_store(&q->state[w] , readable) ;
    //atomic_fetch_add(&q->entry , 1) ;
    //printf("%d\n" , w) ;
    return 1 ;
}

uint8_t queue_r(queue * q ,job ** j ){
    if(q->entry ==  0)
      return 0 ;
    int r  = atomic_fetch_add(&q->read , 1) & wmask;

    while(q->state[r] != readable) ;
    *j = q->buffer[r] ;
    atomic_store(&q->state[r] , raw) ;
    int ro = atomic_load(&q->round) ;
    atomic_fetch_sub(&q->entry , 1) ;
    //printf("%d %d\n" ,ro, r) ;
    printf("%d\n" , (*j)->data->start);
    return 1 ;
}

/*
 * debug
 */

uint8_t info_info(info * i){
    printf(" info :　%d %d %s\n" , i->start , i->end ,i->pwd) ;
    return 1 ;
}


uint8_t job_info(job * j){
    info_info(j->data) ;
    j->func(j->data) ;
    return 1 ;
}

uint8_t queue_info(queue  * q){
    int j = q->read & wmask ;
  for(int i  = 0 ; i < q->entry ; i++){
    printf("%d :" , j) ;
    job_info(q->buffer[j]) ;
    j++ ;
    if(j > 15)
      j = 0 ;
  }
  return 1 ;
}

uint8_t queue_state(queue *q){
  printf("read : %d , write : %d  , entry : %d \n"  ,atomic_load(&q->read) &wmask ,atomic_load(&q->write)& wmask,atomic_load(&q->entry)) ;
  return 1 ;
}
