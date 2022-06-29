#include <usergroup.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char * arg[])
{
	int my_pid, p_user_group;
	int procgroup_change_result;
  	my_pid = getpid();
  	printf("%d", setusergroup(my_pid, 1));
  	printf("Changed process group to CALCULATION\n");
	while (1){}
}
