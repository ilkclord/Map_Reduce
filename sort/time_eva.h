/*
 * =====================================================================================
 *
 *       Filename:  time_eva.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  廿廿一年五月卅一日 十七時三分廿六秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <sys/time.h>
#include <stdlib.h>
/*
 * Copy from Word-count.c
 */
static double now()
{
    struct timeval tp;
    if (gettimeofday(&tp, (struct timezone *) NULL) == -1)
        perror("gettimeofday");
    return ((double) (tp.tv_sec) * 1000.0) + (((double) tp.tv_usec / 1000.0));
}


