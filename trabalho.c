#include	<pthread.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

int *vectorA;
int *vectorB;

int sum = 0;

struct params {
  int start;
  int finish;
};

void *ProdutoEscalar(void *arg){

  int i;

  struct params *threadParams = arg;
  
  for(i=threadParams->start;i<threadParams->finish;i++) {
    sum = sum + (vectorA[i] * vectorB[i]);
  }
  
  pthread_exit(NULL);
}

int main (int argc,char	**argv)	{

  int NTHREADS = atoi(argv[1]);
  int VECSIZE = atoi(argv[2]);
  pthread_t thread[NTHREADS];

  srand(time(NULL));

  vectorA = (int *) malloc(sizeof(int) * VECSIZE);
  vectorB = (int *) malloc(sizeof(int) * VECSIZE);

  /* int *vector = (int *) malloc(sizeof(int) * VECSIZE);*/
  /* pthread_create(THREAD,NULL,FUNC,ARG) */
  
  int i;
  
  /* for(i=0;i<VECSIZE;i++) { */
  /*   vectorA[i] = rand() % 10;     */
  /*   vectorB[i] = rand() % 10; */
  /* } */

  for(i=0;i<VECSIZE;i++) {
    vectorA[i] = 2;
    vectorB[i] = 2;
  }
  
  int thread_size = VECSIZE / NTHREADS;
  int resto = VECSIZE % NTHREADS;  

  for(int i = 0; i < VECSIZE; i++) {
    printf("%d ", vectorA[i]);
  }
  
  printf("\n");
  
  for(int i = 0; i < VECSIZE; i++) {
    printf("%d ", vectorB[i]);
  }
  
  for(i=0;i<NTHREADS;i++) {

    struct params *argParams = malloc(sizeof(struct params));

    argParams->start = i * thread_size;
    argParams->finish = (i * thread_size) + thread_size;
    
    pthread_create(&thread[i],NULL,ProdutoEscalar,(void *)argParams);
  }
  
  printf("\n");
  
  printf("%d\n",sum);

}
