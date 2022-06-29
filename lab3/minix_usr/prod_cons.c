#include <minix/callnr.h>
#include <lib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>


int main(int argc, char** argv){
	int i, magazine_size, num_prod, num_cons;
	int prod_min_n, prod_max_n, cons_min_n, cons_max_n, pid;
	char *i_str[10], *magazine_size_str[10], *prod_min_n_str[10], *prod_max_n_str[10];
	char *cons_min_n_str[10], *cons_max_n_str[10];
	
	if (argc != 8){
		printf("Usage: ./prod_cons size num_prod num_cons prod_min_n prod_max_n cons_min_n cons_max_n");
		return -1;
	}
	magazine_size = atoi(argv[1]);
	num_prod = atoi(argv[2]);
	num_cons = atoi(argv[3]);
	prod_min_n = atoi(argv[4]);
	prod_max_n = atoi(argv[5]);
	cons_min_n = atoi(argv[6]);
	cons_max_n = atoi(argv[7]);
	
	snprintf(magazine_size_str, sizeof(magazine_size_str), "%d", magazine_size);
	snprintf(prod_min_n_str, sizeof(prod_min_n_str), "%d", prod_min_n);
	snprintf(prod_max_n_str, sizeof(prod_max_n_str), "%d", prod_max_n);
	snprintf(cons_min_n_str, sizeof(cons_min_n_str), "%d", cons_min_n);
	snprintf(cons_max_n_str, sizeof(cons_max_n_str), "%d", cons_max_n);
	
	sem_init(1);
	for (i=0; i< num_prod; i++){
		pid = fork();
		if (pid == 0) {
			snprintf(i_str, sizeof(i_str), "%d", i);
			execlp("./producer", "producer", i_str, magazine_size_str, prod_min_n_str, prod_max_n_str);
			sleep(3);
		}
	}
	for (i=0; i< num_cons; i++){
		pid = fork();
		if (pid == 0) {
			snprintf(i_str, sizeof(i_str), "%d", i);
			execlp("./consumer", "consumer", i_str, magazine_size_str, cons_min_n_str, cons_max_n_str);
			sleep(3);
		}
	}
	for (i=0; i<num_prod+num_cons; i++) {
		wait(NULL);
	}
	sem_release();
	return 0;
}
