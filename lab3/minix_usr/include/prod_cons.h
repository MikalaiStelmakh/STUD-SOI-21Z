#include <lib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAGAZINE_PATH "prod_cons/magazine.txt"

int rand_in_range(int min, int max){
	int n;
	srand(time(NULL));
	n = (rand() % (max - min + 1)) + min;
	return n;
}

int check_magazine(void){
	int num;
   	FILE *fptr;

   	if ((fptr = fopen(MAGAZINE_PATH,"r")) == NULL){
       		printf("Error opening magazine.\n");
       		exit(1);
   	}
   	fscanf(fptr,"%d", &num);
      	fclose(fptr);
   	return num;
}

int update_magazine(int value){
	int num;
   	FILE *fptr;

   	fptr = fopen(MAGAZINE_PATH,"w");

   	if(fptr == NULL)
   	{
     	 	printf("Error opening magazine.\n");   
      		exit(1);             
   	}

   	fprintf(fptr,"%d",value);
   	fclose(fptr);

   	return 0;
}

int append_txt(char *path, char *text){
	FILE *fptr;
	fptr = fopen(path, "a");
	if(fptr == NULL)
   	{
     	 	printf("Error opening file.\n");   
      		exit(1);             
   	}
	fputs(text, fptr);
	fclose(fptr);
	return 0;
}

char* get_current_time(void){
	char *output;
	time_t rawtime;
    	struct tm * timeinfo;

    	time ( &rawtime );
    	timeinfo = localtime ( &rawtime );

    	sprintf(output, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    	return output;
}
