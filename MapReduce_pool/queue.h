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

uint8_t mask = 16 ;
uint8_t wmask = 15 ;
struct input{
    int start ;
    int end ;
    char * pwd ;
}typedef info ;

typedef int func(info * i) ;

int foo(info * i){
    return 1 ;
}
/* Ring buffer aka jobqueue :
 *
 * Provide an array of pointer , each points to the data aka job
 * Like a hook used to hang the clothes
 *
 * Using state to double check the accuracy
 */
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
    (*q)->read = 0 ;
    (*q)->write = 0 ;
    (*q)->entry = 0 ;
    (*q)->load = 1 ;
    for(int i = 0 ; i < rbuffer_s ; i++)
      (*q)->state[i] = raw ;
    return 1 ;
}

uint8_t load(queue * q ,int a){
  q->load = a ;
  return 1 ;
}
/*
 * Writing into queue
 */
uint8_t queue_w(queue * q , job * j , int id , int ji){
    if(( q->entry & mask)){
      return 0 ;
     }
    atomic_fetch_add(&q->entry , 1) ;
    int w  = atomic_fetch_add(&q->write , 1) & wmask;
    while(atomic_load(&q->state[w]) != raw){
      /*
       * in the test program the write funtion keeps writing data into the buffer
       */
      if(!q->load ){
        atomic_fetch_sub(&q->entry , 1) ;
        return 0 ; 
      }
    };
    atomic_store(&q->state[w] , writing) ;
    q->buffer[w] = j ;
    atomic_store(&q->state[w] , readable) ;
    return 1 ;
}
/*
 * Reading out the queue
 */
uint8_t queue_r(queue * q ,job ** j ){
    if(q->entry ==  0)
      return 0 ;
    atomic_fetch_sub(&q->entry , 1) ;
    int r = atomic_fetch_add(&q->read , 1) & wmask;
    while(q->state[r] != readable) ;
    *j = q->buffer[r] ;
    atomic_store(&q->state[r] , raw) ;
    return 1 ;
}

/*
 * debug
 */

uint8_t info_info(info * i){
    printf(" info :　%d %d " , i->start , i->end ) ;
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
    printf("state :%d \n" , q->state[j]) ;
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
