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

    int *mid_p = (data + 50);

    printf("Attempting to free a mid_p of array.\n");
    free(mid_p);
    
    printf("%d", data[99]);
    return 0;
}
