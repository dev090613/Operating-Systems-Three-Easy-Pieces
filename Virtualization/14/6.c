#include <stdio.h>
#include <stdlib.h>

int main() 
{
    int *data;
    data = (int *)malloc(100 * sizeof(int));
    if (data == NULL) {
        perror("malloc failed.");
        exit(1);
    }

    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    free(data);

    printf("Value after free: %d\n", data[99]);
    return 0;
}
