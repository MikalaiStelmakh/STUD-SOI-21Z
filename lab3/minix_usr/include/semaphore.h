#include "lib.h"

int sem_init(int value) {
	message m;
	m.m1_i1 = value;
	return _syscall(MM, SEM_INIT, &m);
}

int sem_down(void){
	message m;
	return _syscall(MM, SEM_DOWN, &m);
}

int sem_up(void){
	message m;
	return _syscall(MM, SEM_UP, &m);
}

int sem_release(void) {
	message m;
	return _syscall(MM, SEM_RELEASE, &m);
}

int sem_check(void){
	message m;
	printf("Queue size: %d", _syscall(MM, SEM_QUEUE_CHECK, &m));
	return _syscall(MM, SEM_CHECK, &m);
}
