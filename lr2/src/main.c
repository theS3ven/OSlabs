#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

typedef struct {
    int n;           
    double **A;        
    double *b;          
    int start, end;     
} data;


pthread_mutex_t mutex; 


void* gauss(void* arg) {
    data* num = (data*)arg;
    int n = num->n;
    double **A = num->A;
    double *b = num->b;

    for (int k = 0; k < n; k++) {
        for (int i = num->start; i < num->end; i++) {
            if (i > k) {
                double factor = A[i][k] / A[k][k];
                pthread_mutex_lock(&mutex); 

                for (int j = k; j < n; j++) {
                    A[i][j] -= factor * A[k][j];
                }
                b[i] -= factor * b[k];
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    return NULL;
}

void back_way(int n, double **A, double *b, double *x) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i] / A[i][i];
        for (int j = i - 1; j >= 0; j--) {
            b[j] -= A[j][i] * x[i];
        }
    }
}

int main(int argc, char *argv[]){
    if (argc < 3) {
		const char msg[] = "error: failed, too many arguments\n";
		write(STDOUT_FILENO, msg, sizeof(msg));
        exit(EXIT_FAILURE);
    }

    int num = atoi(argv[1]);
	int NUM_OF_THREADS = atoi(argv[2]);

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization error\n");
        exit(EXIT_FAILURE);
    }

	double **A = malloc(num * sizeof(double *));
    double *b = malloc(num * sizeof(double));
    double *x = malloc(num * sizeof(double));
    for (int i = 0; i < num; i++) {
        A[i] = malloc(num * sizeof(double));
        for (int j = 0; j < num; j++) {
            A[i][j] = (double)(rand() % 100);  
        }
        b[i] = (double)(rand() % 100);
    }

	pthread_t threads[NUM_OF_THREADS];
    data thread_data[NUM_OF_THREADS];

	int chunk_size = num / NUM_OF_THREADS;  
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        thread_data[i].n = num;
        thread_data[i].A = A;
        thread_data[i].b = b;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, gauss, &thread_data[i]);
    }

	for (int i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    back_way(num, A, b, x);

	const char msg[] = "Matrix solve:\n";
	write(STDOUT_FILENO, msg, sizeof(msg));

    for (int i = 0; i < num; i++) { 
 		char tmpbuf[128];
    	int n = sprintf(tmpbuf, "x[%d] = %f\n", i, x[i]);
    	write(STDOUT_FILENO, tmpbuf, n);
	}

    for (int i = 0; i < num; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);

    pthread_mutex_destroy(&mutex);

    return 0;
}