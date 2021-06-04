/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description: Double linked list header 
 *
 *        Version:  1.0
 *        Created:  廿廿一年六月四日 十九時56分六秒
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

#define type int
struct n {
  type data ;
  struct n * next ;
  struct n * prev ;
} typedef node ;

#define list_add(root ,new) \
  root->prev->next = new ;\
  new->next = root ;\
  new->prev = root->prev ;\
  root->prev = new ;\

int list_init(node * root){
    root->next = root ;
    root->prev = root ;
    return 1 ;
}

int list_insert(node * root ,type data){
   node * new = malloc(sizeof(node)) ;
   if(!new)
     return 0 ;
   new->data = data ;
   list_add(root , new) ;
}

int list_del(node * n){
    node * tmp = n ;
    n->prev->next = n->next ;
    n->next->prev = n->prev; 
    free(n) ;
    return 1 ;
}
/*
 * Return value
 * 0 : remove the last element
 * 1 : simple remove
 */
int list_rm(node **root ,type data){
  if((*root)->next == (*root)){
    free(*root) ;
    root = NULL ;
    return 0 ;
  }
  if((*root)->data == data){
    node * tmp = *root ;
    *root = (*root)->next; 
    list_del(tmp);
    return 1 ;
  }
  for(node * i = (*root)->next ; i != (*root) ; i = i->next)
    if(i->data == data){
      list_del(i) ;
      break ;
    }
 return 1 ;
}

int list_destroy(node * root){
    for( node * i = root->next; i != root ; i = i->next)
      list_del(i) ;
    free(root) ;
    return 1 ;
}

node * list_find(node * root , type data){
   node * i = root ;
   if(root->data == data)
     return root ;
   for(i = i->next ; i != root ; i = i->next)
     if(i->data == data)
       return i ;
   return NULL ;
}

void list_info(node * root){
  printf(" %d" , root->data) ;
  for(node * i = root->next ; i!= root ; i = i->next)
    printf(" %d" , i->data) ;
  printf("\n") ;
}
