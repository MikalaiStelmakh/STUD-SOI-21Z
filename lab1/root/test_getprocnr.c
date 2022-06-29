#include <lib.h>
#include <stdio.h>
#include <stdlib.h>

int getprocnr(int pid) {
	message m;
	m.m1_i1 = pid;
	return _syscall(MM, GETPROCNR, &m);
}

int main(int argc, char* argv[]) {
	int pid, i, end_i;

	if (argc != 2) {
		return 1;
	}

	pid = atoi(argv[1]);
	end_i = pid + 10;

	for (; pid <= end_i; ++pid) {
		i = getprocnr(pid);
		if (i > 0) {
			printf("PID: %d, Index: %d\n", pid, i);
		} else {
			printf("PID: %d, error: %d.\n", pid, errno);
		}
	}
	return 0;
}

