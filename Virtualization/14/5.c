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

    data[100] = 0; // out of bound
    printf("%d\n", data[100]);

    free(data);
    return 0;
}
