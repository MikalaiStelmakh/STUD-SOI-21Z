#include <lib.h>

int setusergroup(pid_t pid, int usergr)
{
	message m;
	m.m1_i1 = pid;
	m.m1_i2 = usergr;
	return _syscall(MM, SETPROCGROUP, &m);
}
