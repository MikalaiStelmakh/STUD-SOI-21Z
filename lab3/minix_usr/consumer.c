#include <minix/callnr.h>
#include <lib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <prod_cons.h>


int main(int argc, char* argv[]){
	int n, current;
	char *time, *log[100], *log_path[100];
	int i = atoi(argv[1]);
	int magazine_size = atoi(argv[2]);
	int min_n = atoi(argv[3]);
	int max_n = atoi(argv[4]);
	
	snprintf(log_path, sizeof(log_path), "prod_cons/consumer%d.txt", i);

	while (1){
		n = rand_in_range(min_n, max_n);
		
		snprintf(log, sizeof(log), "(%s) Trying to consume %d items.\n",get_current_time(), n);
		append_txt(log_path, log);
		sem_down();
		current = check_magazine();
		if (current >= n){
			update_magazine(current-n);
			snprintf(log, sizeof(log), "(%s) Consumed %d items.\n",get_current_time(), n);
		}
		else{
			snprintf(log, sizeof(log), "(%s) Failed to consume %d items.\n",get_current_time(), n);
		}
		append_txt(log_path, log);
		sem_up();
		fflush(stdout);
		sleep(5);
	}
	return 0;
}
