#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For systems based on Linux kernel.
#if defined(__linux__)
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#endif

#define NO_SUCCESS(x) (x) == -1
#define IS_CHILD_PID(x) (x) == 0

typedef struct {
    int fd[2];
    pid_t childpid;
} IPC_descriptor;

void print_error_and_exit()
{
    int errnum;

    errnum = errno;
    char *err_str = strerror(errnum);
    perror(err_str);
    _exit(-1);
}

int main(int argc, char *argv[])
{
    IPC_descriptor ipc_des;

    if (NO_SUCCESS(pipe(&ipc_des.fd[0]))) {
        print_error_and_exit();
    }

    if (NO_SUCCESS(ipc_des.childpid = fork())) {
        print_error_and_exit();
    }

    if (IS_CHILD_PID(ipc_des.childpid)) {
        if (NO_SUCCESS(close(ipc_des.fd[0]))) {
            print_error_and_exit();
        }

        if (NO_SUCCESS(close(STDIN_FILENO))) {
            print_error_and_exit();
        }
        // Often the descriptors of the childe are duplicated onto standard
        // input and output. The child can then exec() another program, which
        // inherits the standard streams.
        if (NO_SUCCESS(dup(ipc_des.fd[0]))) {
            print_error_and_exit();
        }
    } else {
        if (NO_SUCCESS(close(ipc_des.fd[0]))) {
            print_error_and_exit();
        }
    }

    // All parts of the program now must _exit(-1) if something goes wrong.
    return 0;
}
