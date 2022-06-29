/* Prgram to create three threads,first to increment the variable,second to store them into buffer & third to write the incremented value into file */
/* Date:- 28/06/22 */
/* BHAKTI VYAS */

#include<fcntl.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


void *functionC();                                // defining functions
void *functionS();
void *functionP();
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // intialiazing the pthread mutex
int x=8,i, temp, fd;

int main()
{
    int a1,a2,a3;
    pthread_t thread1, thread2,thread3;

    if((a1 = pthread_create(&thread1, NULL, &functionC, NULL)))  // creating thread1
    {
        printf("thread failed:\n");
    }
	
    if((a2 = pthread_create(&thread2, NULL, &functionS, NULL)))  // creating thread2
    {
        printf("thread failed:\n");
    }
	
    if((a3 = pthread_create(&thread3, NULL, &functionP, NULL)))  // creating thread3
    {
        printf("thread3 failed:\n");
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
 
     
    return 0;
}

void *functionC()
{
    printf("th1");
    pthread_mutex_lock(&lock);                                  // applying mutex lock
    printf("value of variable is %d",x);
    x++;
    printf("\nafter increment %d\n",x); 
    pthread_mutex_unlock(&lock);                                  // unlocking mutex lock  
                              
}    

void *functionS() {

    printf("th2");
    pthread_mutex_lock(&lock);                                   // applying mutex lock
    temp=x;
    pthread_mutex_unlock(&lock);                                 // unlocking mutex lock
}

void *functionP(){

    printf("th3");
    pthread_mutex_lock(&lock); 
    FILE *fd = fopen( "test.txt","a+");                // opens file in a+ append  mode,if it unable to open the file returns NULL
    if (fd!=NULL) 
    {
        fprintf(fd, "new value: %d", temp); // fprintf is used to print content in file instead of stdout console.
    }
    else
    
     printf("unable to open the file");
    }     
    pthread_mutex_unlock(&lock);                                    // unlocking mutex lock
}  
