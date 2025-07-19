#include <stdio.h>

int main() {
    char buffer[16 * 1024 * 1024];
    buffer[0] = 'a';
    buffer[sizeof(buffer) - 1] = 'z';
    printf(
        "Allocated stack buffer: %c ... %c \n",
        buffer[0],
        buffer[sizeof(buffer) - 1 ]
    );
    return 0;
}
