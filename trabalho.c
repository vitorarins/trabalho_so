#include	<pthread.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<math.h>

pthread_mutex_t mutex;

int *vectorA;
int *vectorB;

int sum = 0;

struct params {
  int n_thread;
  int start;
  int finish;
};

void *ProdutoEscalar(void *arg){

  // inicializacao da variavel com o parametro arg
  struct params *threadParams = arg;
  // delcaracao e inicializacao das variaveis auxiliares
  int i;
  int local_sum = 0;
  int end_index = threadParams->finish - 1;

  // itera do parametro de inicio ate o parametro de final
  for(i=threadParams->start;i<threadParams->finish;i++) {
    // soma cada produto entre elemento de A com elemento de B
    local_sum = local_sum + (vectorA[i] * vectorB[i]);
  }
  
  printf ("Thread %d calculou de %d a %d: produto escalar parcial = %d\n",threadParams->n_thread,threadParams->start,end_index,local_sum);

  // trava o mutex para a regiao critica
  pthread_mutex_lock(&mutex);
  
  // adiciona a soma local na variavel global de soma
  sum = sum + local_sum;

  // destrava o mutex apos regiao critica
  pthread_mutex_unlock(&mutex);
  
  pthread_exit(NULL);
}

int main (int argc,char	**argv)	{

  /* Ex. de uso: ./trabalho 4 16
     Isso inicializa NTHREADS = 4 e VECSIZE = 16
   */
  
  // inicializacao das variaveis com argumentos da linha de comando
  float NTHREADS = atof(argv[1]);
  float VECSIZE = atof(argv[2]);
  pthread_t thread[(int)NTHREADS];

  // se o numero de threads for maior que tamanho do vetor, os mesmos serao igualados
  if (NTHREADS > VECSIZE)
    {
      NTHREADS = VECSIZE;
    }

  srand(time(NULL));

  vectorA = (int *) malloc(sizeof(int) * VECSIZE);
  vectorB = (int *) malloc(sizeof(int) * VECSIZE);

  // inicializacao dos vetores com valores aleatorios
  for(int i=0;i<VECSIZE;i++) {
    vectorA[i] = rand() % 10;
    vectorB[i] = rand() % 10;
  }

  int *thread_size = (int *) malloc(sizeof(int) * NTHREADS);
  
  // inicializa um array para as quantidades utilizadas por cada thread
  for (int i = 0; i < NTHREADS; ++i) {
    thread_size[i] = 0;
  }

  int j = 0;
  
  // itera ate o tamanho dos vetores principais
  for (int i = 0; i < VECSIZE; ++i) {

    // se incrementou o tamanho de todas as threads, reinicia
    if (j == NTHREADS) {
      j = 0;
    }

    // incrementa o tamanho/quantidade de elementos utilizadas pela thread 'j'
    thread_size[j]++;
    j++;
  }

  // inicio da impressao dos vetores
  printf ("A = ");
  for(int i = 0; i < VECSIZE; i++) {
    printf("%d ", vectorA[i]);
  }
  
  printf("\nB = ");
  
  for(int i = 0; i < VECSIZE; i++) {
    printf("%d ", vectorB[i]);
  }

  printf("\n");
  // final da impressao dos vetores  

  // contador para indicar o indice inicial de cada thread
  int thread_size_counter = 0;

  // inicializa variavel mutex
  pthread_mutex_init(&mutex,NULL);
  
  // itera ate o numero de threads
  for(int i=0;i<NTHREADS;i++) {

    // inicializa a struct auxiliar de parametros
    struct params *argParams = malloc(sizeof(struct params));

    // indica o numero da thread para impressao
    argParams->n_thread = i+1;
    // indica o indice para inicio do calculo na thread
    argParams->start = thread_size_counter;
    // indica o indice para final do calculo na thread
    argParams->finish = thread_size_counter + thread_size[i];

    /* eh necessario incrementar o contador com a quantidade maxima
     de elementos que sera aceito pela thread em questao */     
    thread_size_counter = thread_size_counter + thread_size[i];
    
    pthread_create(&thread[i],NULL,ProdutoEscalar,(void *)argParams);
  }

  for(int i=0;i<NTHREADS;i++) {
    pthread_join(thread[i],NULL);
  }

  // destroi a variavel mutex
  pthread_mutex_destroy(&mutex);
  
  printf("\n");
  
  printf("Produto escalar = %d\n",sum);

}
