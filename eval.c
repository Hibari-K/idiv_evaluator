#include<stdio.h>
#include<stdint.h>

#define N 1000000

uint64_t rdtscp(uint32_t index);
uint32_t arr_aux[2];

int main(){
    
    uint32_t flag = 1;
    uint64_t i;
    uint64_t diff, tsc1, tsc2;

    while(flag){
        
        tsc1 = rdtscp(0);

        // initialize
        __asm__ volatile(
            "mov $156707, %rax;"
            "mov $9999883, %rcx;"
            "mov $-1, %r10"
        );

        for(i=0; i<N; i++){
            __asm__ volatile(
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                "mov %%r10, %%rdx;"
                "idiv %%rcx;" 
                ::: "rax", "rdx", "rcx", "r10"
            );
        }

        tsc2 = rdtscp(1);

        if(arr_aux[0] == arr_aux[1]) flag = 0;
    }

    diff = tsc2 - tsc1;
    printf("diff = %ld\n", diff);

    return 0;
    
}



uint64_t rdtscp(uint32_t index){
    
    uint32_t high, low, aux;

    __asm__ volatile("rdtscp" : "=a"(low), "=d"(high), "=c"(aux));
    arr_aux[index] = aux;

    return ((uint64_t) high << 32) | low;
}
