#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// For systems based on Linux kernel.
#if defined(__linux__)
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#endif

#define IS_CHILD_PID(x) (x) == 0

typedef struct {
    int fd[2];
    pid_t childpid;
} IPC_descriptor;

#define print_error_and_exit() \
    int errnum; \
    errnum = errno; \
    char *err_str = strerror(errnum); \
    perror(err_str); \
    _exit(-1);

#define print_error_and_exit1(x) \
    int errnum; \
    errnum = errno; \
    char *err_str = strerror(errnum); \
    perror(err_str); \
    _exit(x);

int main(int argc, char *argv[])
{
    IPC_descriptor ipc_des;
    int ret;

    if ((ret = pipe(&ipc_des.fd[0]) == -1)) {
        print_error_and_exit1(ret);
    }

    if ((ipc_des.childpid = fork()) == -1) {
        print_error_and_exit();
    }

    if (IS_CHILD_PID(ipc_des.childpid)) {
        // Often the descriptors of the child are duplicated onto standard
        // input and output. The child can then exec() another program, which
        // inherits the standard streams.
        if ((ret = dup(ipc_des.fd[0])) == -1) {
            print_error_and_exit1(ret);
        }

        if ((ret = close(ipc_des.fd[0])) == -1) {
            print_error_and_exit1(ret);
        }

        if ((close(STDIN_FILENO))) {
            print_error_and_exit();
        }
    } else {
        if ((close(ipc_des.fd[1]))) {
            print_error_and_exit();
        }
    }

    // All parts of the program now must _exit(x) if something goes wrong.
    return 0;
}
