#include	<pthread.h>
#include	<stdlib.h>
#include	<stdio.h>

int sum = 0;

void *PrintHello(void *arg){

  int i;
  for(i=0;i<100;i++) {
    contador_global++;
  }
  pthread_exit(NULL);
}

int main (int argc,char	**argv)	{

  int NTHREADS = argv[1];
  int VECSIZE = argv[2];  

  srand(time(NULL));

  int vectorA[VECSIZE];
  int vectorB[VECSIZE];

  
  /* int *vector = (int *) malloc(sizeof(int) * 10); */
  /* pthread_create(THREAD,NULL,FUNC,ARG) */
  
  int i;
  
  for(i=0;i<VECSIZE;i++) {
    vectorA[i] = rand() % 10;    
    vectorB[i] = rand() % 10;
  }

  for(i=0;i<NTHREADS;i++) {
    pthread_create(&thread[i],NULL,,(void *)arg);
  }

  int resto = VECSIZE % NTHREADS;

  
}
