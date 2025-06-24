#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char *header = "HTT\0P/1.1 200 OK";

    write(1, header, strlen(header));
    printf("\nheader: %s", header);

    // 👉 Try changing this `%s` to `%zu` (ignore the compiler warning).
    printf("\n\nThat output was from write(). This is from printf: %s\n", header);
    printf("\n\nThat output was from write(). This is from printf: %zu\n", header);
    printf("\n\nThat output was from write(). This is from printf: %zu\n", (char*)123456);

    return 0;
}
