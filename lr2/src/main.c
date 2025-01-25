#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

#define MAX_THREADS 16


typedef struct {
    int n;           
    double *a;        
    double *b;          
    int start;     
} data;


pthread_mutex_t mutex; 


void* gauss(void* arg) {
    data* num = (data*)arg;
    double *a = num->a;
    double *b = num->b;
    // int k = num->start;
    int n = num->n;
    for (int k = 0; k < n; k++) {
        double p = a[k * n + k];
        for (int i = k + 1; i < n; i++) {
                pthread_mutex_lock(&mutex);
                double l = a[i * n + k] / p;
                for(int j = k; j < n; j++){
                    a[i * n + j] -= l * a[k * n + j];
                }
                b[i] -= l * b[k];
                pthread_mutex_unlock(&mutex);
            }
    }
    return NULL;
}

void back_way(int n, double *a, double *b, double *x) {
    for(int k = n - 1; k >= 0; k--){
        x[k] = b[k];
        for(int i = k + 1; i < n; i++){
            x[k] -= a[k * n + i] * x[i];
        }
        x[k] /= a[k * n + k];
        printf("x[%d] = %5.4f\n", k, x[k]);
    }
}

int main(int argc, char *argv[]){
    if (argc < 3) {
		const char msg[] = "error: failed, too many arguments\n";
		write(STDOUT_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }
    
    int n = atoi(argv[1]);
	int num_of_threads = atoi(argv[2]);
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization error\n");
        exit(EXIT_FAILURE);
    }

	double *a = malloc(sizeof(*a) * n * n);
    double *b = malloc(sizeof(*b) * n);
    double *x = malloc(sizeof(*x) * n);

    // создание матрицы
    for (int i = 0; i < n; i++) {
        srand(i * (10 + 1));
        for (int j = 0; j < n; j++) {
            a[i * n + j] = rand() % 10 + 1;  
        }
        b[i] = rand() % 10 + 1;
    }

    // отображение матрицы
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%5.2f ", a[i * n + j]);
        }printf(" | %5.2f\n", b[i]);
    }

    pthread_t threads[MAX_THREADS];
    data thread_data[MAX_THREADS];

    int chunks = n / num_of_threads;
    for(int i = 0; i < num_of_threads; i++){
        thread_data[i].n = n;
        thread_data[i].a = a;
        thread_data[i].b = b;
        thread_data[i].start = i * chunks;
        pthread_create(&threads[i], NULL, gauss, &thread_data[i]);
    }

    for (int i = 0; i < num_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    back_way(n, a, b, x);

    free(a);
    free(b);
    free(x);

    pthread_mutex_destroy(&mutex);
    return 0;
}
