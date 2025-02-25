/* memory-user.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s memory_mb [time]\n",
                argv[0]);
        exit(1);
    }
    printf("pid: %d\n\n", getpid());
        
    int memory_mb = atoi(argv[1]);
    int time = (argc > 2) ? atoi(argv[2]) : -1;

    size_t array_size = (size_t)memory_mb * 1024 * 1024 / (sizeof(int));
    int *array = malloc(array_size * sizeof(int));
    if (array == NULL) {
        perror("malloc failed.");
        exit(1);
    }

    printf("Allocated %d mb memory.\n", memory_mb);

    for (size_t i = 0; i < array_size; i++) {
        array[i] = i;
    }

    if (time > 0) {
        printf("Running for %d seconds...\n", time);
        sleep(time);
    } else {
        printf("Infinite loop...\nPress Ctrl + c to stop.\n");
        while (1) {
            for (size_t i = 0; i < array_size; i++) {
                array[i]++;
            }
        }
    }

    free(array);

    return 0;
}


