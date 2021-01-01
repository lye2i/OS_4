#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include "SSU_Sem.h"

void SSU_Sem_init(SSU_Sem *s, int value) {
	s->value = value;
	pthread_cond_init(&s->cond, NULL);
	pthread_mutex_init(&s->lock, NULL);
}

void SSU_Sem_down(SSU_Sem *s) {
	s->value--;

	pthread_mutex_lock(&s->lock);
	
	if(s->value < 0)
		pthread_cond_wait(&s->cond, &s->lock);

	pthread_mutex_unlock(&s->lock);
}

void SSU_Sem_up(SSU_Sem *s) {

	s->value++;

	pthread_mutex_lock(&s->lock);
	pthread_cond_signal(&s->cond);
	pthread_mutex_unlock(&s->lock);

}
