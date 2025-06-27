#include <string.h>
#include <stdio.h>
const char* DEFAULT_FILE = "index.html";

char *to_path(char *req) {
    char *start, *end;

    // Advance `start` to the first space
    for (start = req; start[0] != ' '; start++) {
        if (!start[0]) {
            return NULL;
        }
    }

    start++; // Skip over the space

    if (start[0] == '/') {
        start++;
    }

    // Advance `end` to the second space
    for (end = start; end[0] != ' '; end++) {
        /*printf("\n%s", end);*/
        if (!end[0]) {
            return NULL;
        }
    }

    // Ensure there's a '/' right before where we're about to copy in "index.html"
    if (end[-1] == '/') {
        end--; // We end in a slash, e.g. "/blog/" - so just move `end` to that slash.
        end++;
    } else {
        end[0] = '/'; // We don't end in a slash, so write one.
        end++;
    }

    if (end + strlen(DEFAULT_FILE) > req + strlen(req)) {
        return NULL;
    }

    memcpy(
        end,
        DEFAULT_FILE,
        // 👉 Try removing the +1 here. Re-run to see what happens, but first try to guess!
        strlen(DEFAULT_FILE) + 1
    );

    return start;
}

int main() {
    char req4[] = "GET /blog ";
    printf("\nShould be \"(null)\": \"%s\"", to_path(req4));
    char req1[] = "GET /blog HTTP/1.1\nHost: example.com";
    printf("\nShould be \"blog/index.html\": \"%s\"\n", to_path(req1));

    char req2[] = "GET /blog/ HTTP/1.1\nHost: example.com";
    printf("Should be \"blog/index.html\": \"%s\"\n", to_path(req2));

    char req3[] = "GET / HTTP/1.1\nHost: example.com";
    printf("Should be \"index.html\": \"%s\"\n", to_path(req3));

    return 0;
}
