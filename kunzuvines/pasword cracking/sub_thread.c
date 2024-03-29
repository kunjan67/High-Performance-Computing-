#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>


int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$5B3KGhhav2/OsufUGxdicHWDBJM7ojVt0DvSVVwcpHL2OiiiBnq.b6hHZ/uYsi9PETZ6XDOW9/xOOrcbIXcfE/",
  "$6$KB$9su2.NRbU5.MLcI2AoIiaoweIjbw93hYcI3lT1s3YFyu.4oLGagTNFTLM9bl3C5MGLlVvnfYHEeArlvb.edBf1",
  "$6$KB$LmaRjg/rYxlWNto93hz/VRDDjP4AYWrwz4W2mfICOhpTqNKlU8khek/18ydiS0RKJphaPrFrBePEmigiOX4Rd0",
  "$6$KB$vIBYaJoTKVrm46ODHzCVNcIJqf0gviDbD7MKcaJIequnv9UgzcPMPUOV6EI1itDVh6H/mBnyPiAnAhYYNm5X3/"
};
/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All
combinations
 that are tried are displayed and when the password is found, #, is put
at the
 start of the line. Note that one of the most time consuming operations
that
 it performs is the output of intermediate results, so performance
experiments
 for this kind of program should not include this. i.e. comment out the
printfs.
*/

void thread()
{
  int i;
pthread_t thread_1, thread_2;

    void *kernel_function_1();
    void *kernel_function_2();
for(i=0;i<n_passwords;i<i++) {
   
    
    pthread_create(&thread_1, NULL,kernel_function_1, encrypted_passwords[i]);
    pthread_create(&thread_2, NULL,kernel_function_2, encrypted_passwords[i]);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
 }
}

void *kernel_function_1(void *salt_and_encrypted){
  int k, u, n;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(k='A'; k<='M'; k++){
    for(u='A'; u<='Z'; u++){
      for(n=0; n<=99; n++){
        sprintf(plain, "%c%c%02d", k,u,n);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else{printf("%-8d%s %s\n", count, plain, enc);}
      }
    }
  }
  printf("%d solutions explored\n", count);
}


void *kernel_function_2(void *salt_and_encrypted){
  int k, u, n;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(k='N'; k<='Z'; k++){
    for(u='A'; u<='Z'; u++){
      for(n=0; n<=99; n++){
        sprintf(plain, "%c%c%02d", k,u,n);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else{printf("%-8d%s %s\n", count, plain, enc);}
      }
    }
  }
  printf("%d solutions explored\n", count);
}

//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}
int main(int argc, char *argv[])
{
  	
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	
	
    		thread();
  	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}
