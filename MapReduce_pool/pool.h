/*
 * =====================================================================================
 *
 *       Filename:  pool.h
 *
 *    Description: Thread pool designed for MapReduce 
 *
 *        Version:  1.0
 *        Created:  廿廿一年六月四日 十九時51分三秒
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
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include "list.h"

#define thread_n 4
/*
 * user defined
 */

/* 
 * the arguments the funtion needed
 */
struct input{
    int start ;
    int end ;
    char * pwd ;
}typedef info ;

/*
 * the funtion
 */
typedef int map() ;
typedef int reduce() ;
typedef int trim() ;

/*
 *funtion package ; 
 */
struct f{
  map * map ;
  reduce * reduce ;
  trim * trim ;
} typedef funcs ;

struct state_2{
    uint8_t  w  ;
    uint8_t job ;
}typedef w_state;

struct state{
    time_t moment ;
    double complete ;
    uint8_t active;
    w_state * w ;
    p_state * next ;
} typedef p_state ;

struct job{
    info * data ;
    funcs * work ;
    node * next ;
} typedef jobqueue ;

struct pool{
    pthread_t * worker ;
    jobqueue * queue ;
    p_state * state ;
}typedef mr_pool ;
/*
 * p_state funtion = init && back_up
 */
int back_up(p_state ** current);
int p_s_init(p_state * current) ;

int p_s_init(p_state * current){
    current->moment = get() ;
    current->complete = 0 ;
    current_active = 1 ;
    current->w = malloc(sizeof(w_sate)*thread_n) ;
    if(!current->w)
      return 0 ;
    current->next = malloc(sizeof(p_state)) ;
    if(!current->next){
      free(current->w) ;
      return 0 ;
    }
    back_up(&current) ;
    return 1 ;
}

int back_up(p_state ** current){
    (*current)->active = 0 ;
    p_state * next = (*current)->next ;
    next->moment = current->moment ;
    next->complete = current->complete ;
    for(int i = 0 ; i < thread_n ; i++)
      next->w[i] = current->w[i] ;
    next->active = 1 ;
    current = next ;
    return 1 ;
}
/*
 * pool funtion
 */
int pool_create();
int pool_init() ;
int pool_assign() ;
int pool_runtime() ;
int pool_backup() ;
int pool_check() ;

int thread_run() ;

