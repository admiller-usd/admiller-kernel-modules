#include <stdio.h>
#include <unistd.h>

int vuln() {
    char arr[400];
    int return_status;
    printf("What's your name?\n");
    return_status = read(0, arr, 800);
    printf("Hey %s", arr);

    return 0;
}

int main (int argc, char *argv[]) {
    vuln();

    return 0;
}
