#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

#if 1
void* sum(void* arg){
    int* input = (int*)arg;
    int* res = calloc(1, sizeof(int));
    *res = *input + 1;
    return (void*) res;
}
#endif

int main(int argc, char *argv[]){
    int NUM_OF_THREADS = 1;
    int input = atoi(argv[1]);
    int *thread_result;

    // printf("%d\n", res);

    pthread_t threads[NUM_OF_THREADS];

    pthread_create(&threads[0], NULL, sum, &input);
    pthread_join(threads[0], (void **)&thread_result);
    // int res = *thread_result;
    #if 1
    // int ans = atoi(argv[1]);
    char tmpbuf[128];
    int n = sprintf(tmpbuf, "%d\n", *thread_result);
    write(STDOUT_FILENO, tmpbuf, n);
    #endif
    free(thread_result);

    return 0;
}