#include <stdio.h>
#include <unistd.h>

int main() {
    write(1, "Hello, World!\n", 14);

    int num = 42;
    int num2 = 24;
    printf("The numbers are: %d, %d\n", num, num2);

    return 0;
}
