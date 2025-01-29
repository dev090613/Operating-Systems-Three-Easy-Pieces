#include <sys/time.h>
#include <stdio.h>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL); // timezone is depricated

    printf("Seconds: %ld\n", (long)tv.tv_sec);
    printf("Micro seconds: %d\n", (int)tv.tv_usec);

    long total_usec = ((long)tv.tv_sec * 1000000L) + (long)tv.tv_usec;
    printf("Total micro seconds: %ld\n", total_usec);

}
