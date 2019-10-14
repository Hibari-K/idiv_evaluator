#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

#define LOOP 3000

#define LEN_DIVIDEND 4095
#define LEN_DIVISOR 1

void printNum(uint64_t *x, uint64_t len);
void makeBigNum(uint64_t *x, uint64_t len);
void divide(uint64_t *a, uint64_t b, uint64_t alen, uint64_t *q, uint64_t *r);

int main(){
    
    int i;
    uint64_t dividend[4096], divisor[8], quotient[4096], remainder[8];
    struct timeval s, e;
    double total = 0.0; 
    double time;

    for(i=0; i<=LEN_DIVIDEND; i++) dividend[i] = 0;

    makeBigNum(dividend, LEN_DIVIDEND);
    makeBigNum(divisor, LEN_DIVISOR);

    //printNum(dividend, LEN_DIVIDEND);
    //printNum(divisor, LEN_DIVISOR);
    //puts("");


    for(i=0; i<LOOP; i++){
        gettimeofday(&s, NULL);
        divide(dividend, divisor[0], LEN_DIVIDEND, quotient, remainder);
        gettimeofday(&e, NULL);
    
        total += (e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6;
    }


    //puts("Result");
    //printf("Quotient: ");
    //printNum(quotient, LEN_DIVIDEND);
    //printf("Remainder: ");
    //printNum(remainder, LEN_DIVISOR);

    time = total * 1000;
    printf("Time: %lf [ms]\n", time);


    

    return 0;
}

// a is a dividend and it will be destroyed.
// b is a divisor which has one word value so far.
void divide(uint64_t *a, uint64_t b, uint64_t alen, uint64_t *q, uint64_t *r){
    
    int i;
    uint64_t tmp;
    for(i=alen-1; i>=0; i--){
        
        tmp = (a[i+1] << 32) | a[i];
        q[i] = tmp / b;
        a[i] = tmp % b;
    }

    r[0] = a[0];
}


void printNum(uint64_t *x, uint64_t len){
    
    int i, vlen;
    for(i=len-1; i>=0; i--){
        if(x[i] != 0){
            vlen = i;
            break;
        }
    }

    printf("0x");
    for(i=vlen; i>=0; i--){
        printf("%08llx", x[i]);
    }
    puts("");

}

void makeBigNum(uint64_t *x, uint64_t len){

    int i;
    srand(time(NULL)+len);

    for(i=0; i<len; i++){
        x[i] = (uint32_t)rand();
    }

}
