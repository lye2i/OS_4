#include "rw_lock.h"

void init_rwlock(struct rw_lock * rw)
{
	rw->reader = 0;
	rw->writer = 0;
	rw->read_counter = 0;
	rw->write_counter = 0;
	pthread_mutex_init(&rw->lock, NULL);
	pthread_cond_init(&rw->read_signal, NULL);
	pthread_cond_init(&rw->write_signal, NULL);
	//	Write the code for initializing your read-write lock.
}

void r_lock(struct rw_lock * rw)
{
//	if(rw->writer > 0){
//		rw->read_counter++;
//		pthread_cond_wait(&rw->read_signal, &rw->lock);
//	}

//	rw->read_counter--;
	rw->reader++;
	pthread_mutex_lock(&rw->lock);
	//rw->reader++;
	
	//	Write the code for aquiring read-write lock by the reader.
}

void r_unlock(struct rw_lock * rw)
{
	rw->reader--;
	//pthread_mutex_unlock(&rw->lock);

	if(rw->reader == 0)
		pthread_cond_signal(&rw->write_signal);
	pthread_mutex_unlock(&rw->lock);
	
  //	Write the code for releasing read-write lock by the reader.
}

void w_lock(struct rw_lock * rw)
{
	rw->write_counter++;
	
	if(rw->reader > 0 || rw-> writer > 0){
		pthread_cond_wait(&rw->write_signal, &rw->lock);
	}

	rw->write_counter--;
	rw->writer++;
	pthread_mutex_lock(&rw->lock);
  //	Write the code for aquiring read-write lock by the writer.
}

void w_unlock(struct rw_lock * rw)
{
	pthread_mutex_unlock(&rw->lock);
	rw->writer--;

	if(rw->write_counter > 0){
			pthread_cond_signal(&rw->write_signal);
	}
  //	Write the code for releasing read-write lock by the writer.
}
