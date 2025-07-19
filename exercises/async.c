#include <liburing.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

const char* TEXT_FILE = "./index.html";

int main() {
    struct io_uring ring;
    io_uring_queue_init(8, &ring, 0);

    int fd = open(TEXT_FILE, O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    struct stat metadata;
    if (fstat(fd, &metadata) == -1) {
        close(fd);
        return 1;
    }
    
    char *buf = malloc(metadata.st_size + 1);
    if (buf == NULL) {
        close(fd);
        return 1;
    }

    struct io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_read(sqe, fd, buf, metadata.st_size - 1, 0);
    io_uring_submit(&ring);
    
    // missing to handle if bytes read error
    struct io_uring_cqe *cqe;
    io_uring_wait_cqe(&ring, &cqe);
    buf[cqe->res] = 0; // null-terminate
    printf("file content: \n\n%s\n", buf);

    io_uring_cqe_seen(&ring, cqe);
    close(fd);
    free(buf);
    io_uring_queue_exit(&ring);

    return 0;
}
