#include <fcntl.h>
#include <stdio.h> 
#include <sys/stat.h>

const char* TEXT_FILE = "./index.html";

int print_size(struct stat mtdta) {
    printf("struct size: %ld bytes - ", mtdta.st_size);
    return 0;
}

int is_empty(int fd) {
    struct stat metadata;
    print_size(metadata);

    char check_file = fstat(fd, &metadata);
    print_size(metadata);

    if (check_file == -1) {
        printf("It's empty\r\n");
        return 1;
    }

    printf("It's not empty\r\n");
    return 0;
}

int main() {
    char* file = "./fail.html";
    int fd = open(TEXT_FILE, O_RDONLY);
    int fd_2 = open(file, O_RDONLY);
    is_empty(fd_2);
    is_empty(fd);
}
