#define RAND_MAX 32767
unsigned long next = 1;

int rand(){
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % RAND_MAX+1; 
    // We can also return the %10 of this.
    
}

void srand(unsigned int seed){
    next = seed;
}
