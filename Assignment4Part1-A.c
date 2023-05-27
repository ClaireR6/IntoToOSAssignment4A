#include <stdio.h>
#include <pthread.h>

int n = 10;
int cnt = 0;
int count = 0;
pthread_cond_t f, d;
pthread_mutex_t m;


void inc(){ // Part A method for incrementing cnt within the thread process
	for(int lcv=0;lcv<1000;lcv++){
		cnt++;
	}
	count++;
}

void *process(void *arg){
	for(int lcv=0;lcv<1000;lcv++){
		cnt++;
	}
	pthread_cond_signal(&d);
}

void *process2(void *arg){
	pthread_mutex_lock(&m);
	while(count == 1){
		pthread_cond_wait(&f, &m);
	}
	inc();
	pthread_cond_signal(&d);
	pthread_mutex_unlock(&m);
}


int main(void) {

	printf("WITHOUT LOCKS\n");
	
	for(int lcv=0;lcv<n;lcv++){
		pthread_t p;
		pthread_create(&p, NULL, process, NULL);
		pthread_cond_wait(&d, &m);
	}

	printf("%d\n", cnt);
	cnt = 0;

	printf("WITH LOCKS\n");

	for(int lcv=0;lcv<n;lcv++){
		pthread_t p;
		pthread_create(&p, NULL, process2, NULL);
		pthread_mutex_lock(&m);
		while(count == 0){
			pthread_cond_wait(&d, &m);
		}
		count--;
		pthread_cond_signal(&f);
		pthread_mutex_unlock(&m);
	}
	printf("%d\n", cnt);
	return 0;
}