#ifndef __SEM_BASE_H
#define __SEM_BASE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
//#include <errno.h>
//#include "semun.h"

// static int sem_id;
union semun{
	int val;
	struct semid_ds *uf;
	unsigned short *array;
};

class CSem{
public:
	CSem(int key);
	~CSem();
	int set_semvalue();
	void del_semvalue();

	int semaphore_p(void);
	int semaphore_v(void);
private:
	int m_sem_id;
};
#endif
