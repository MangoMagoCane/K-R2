#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define NUMMAX 100000
#define FACTORLEN 5

typedef struct Number {
    int num;
    struct Number *factors;
} Number;

typedef struct Factors {
    int smallest;
    int largest;
} Factors;

void pfarray(int printprimes);
void pfstruct(int printprimes);
void pfstructv2(int printprimes);
void printfactors(Number *number);
void printfactorsv2(int number);
int printfactorhelper(int num);
void dadversion(int printprimes);
double gettime(void (*funct)(int), int);

int main(void)
{ 
    double pfa = gettime(&pfarray, 0);
    // double pfs = gettime(&pfstruct, 0);
    double pfs2 = gettime(&pfstructv2, 0);
    double dad = gettime(&dadversion, 0);

    printf("A: %f\n", pfa);
    // printf("S: %f\n", pfs);
    printf("S2: %f\n", pfs2);
    printf("dad: %f\n", dad);

    return 0;
}

Factors numbers[NUMMAX+1] = {0};
// Factors *numbers;

void pfstructv2(int printprimes)
{
    int primes[NUMMAX/2 + 1] = {0};
    // int *primes = calloc(NUMMAX/2 + 1, sizeof(int));
    // numbers = calloc(NUMMAX+1, sizeof(Factors));

    primes[0] = 2, primes[1] = 3;
    int prime, i, max;
    int highestPrimeI = 1;

    for (int num = 2; num <= NUMMAX; num++) {
        // bool testPrimes = true;
        max = num/2+1;
        for (i = 0; primes[i] != 0 && primes[i] < max; i++) {
            prime = primes[i];
            if (num % prime == 0) {
                if (num != prime) {
                    numbers[num].smallest = prime;
                    numbers[num].largest = num / prime;
                }
                // testPrimes = false;
                goto skipPrimeTest;
                break;
            }
        }

        // if (testPrimes) {
            
            // while (prime < num) {
            //     prime += 2;
            //     if (num % prime == 0) {
            //         primes[i] = num;
            //         break;   
            //     } 
            // }
            if (num % primes[i] != 0) {
                primes[++highestPrimeI] = num;
            } else {
                while (prime < num) {
                    prime += 2;
                    if (num % prime == 0) {
                        primes[++highestPrimeI] = num;
                        break;   
                    } 
                }
            }


        // }
        skipPrimeTest:
        // printfactorsv2(num);
    }
    printf("prime count: %d\n", highestPrimeI);
}

void printfactorsv2(int num)
{
    printf("%d: ", num);
    printfactorhelper(num);    
    printf("\n");
}

int printfactorhelper(int num)
{
    int printnode;

    if (numbers[num].smallest) {
        printf("%d ", numbers[num].smallest);
        if (numbers[num].largest) {
            printnode = printfactorhelper(numbers[num].largest);
        }
    } else {
        return 1;
    }

    if (printnode) {
        // printf("%d ", numbers[num].largest);
    }

    return 0;
}

void dadversion(int printprimes)
{
    // num n[MAXPRIMES];
    int prime[NUMMAX/100];
    bool bP;
    int primeindex = 2;
    Factors n[NUMMAX];

    memset(prime, 0, sizeof(prime));
    prime[0] = 2;
    prime[1] = 3;

    for (int i = 0; i < NUMMAX; i++)
    {
        n[i].smallest = n[i].largest = 0;
    } 
    for (int i = 4; i < NUMMAX;i++)
    {
        bP = true;
        for(int p = 0; prime[p]; p++)
        {
            if(i % prime[p] == 0){
               n[i].smallest = prime[p]; 
               n[i].largest = i / prime[p]; 
               bP = false;  
               break;  
            }    
        }                  
        if (bP) {
            prime[primeindex++] = i;
        }
    } 
    for (int i = 0; i < NUMMAX; i++)
    {
        int b = i;
        // printf("%d: %d ", i, n[b].smallest);  
        // printf("% 4d: % d %d\n", b, n[b].a, n[b].b) ; 
        while (n[b].smallest){  
            if (n[b].smallest) {
                // printf("%d ", n[b].smallest);
            }
            b = n[b].largest; 
        }
        // printf("%d \n", b); 
 
    } 
}

void pfstruct(int printprimes)
{
    Number numbers[NUMMAX];
    int i;
    int numI = 0;

    for (int num = 2; num <= NUMMAX; num++, numI++) {
        int factorI = 0;
        int temp = num;
        bool isPrime = true;

        Number *currNum = &numbers[numI];
        currNum->num = num;
        currNum->factors = (Number *) calloc(FACTORLEN, sizeof(Number));

        while (temp != 1) {
            for (i = numI/2; i >= 0; i--) {
                Number *iterNum = &numbers[i];

                if (temp % iterNum->num == 0 && iterNum->num != num) {  
                    currNum->factors[factorI++] = numbers[i];
                    temp /= iterNum->num; 
                    isPrime = false;
                    i = numI/2;
                }
            }

            if (isPrime) {
                currNum->factors = NULL;
                break;
            }

            factorI = 0; 
        }

        // printf("%i: ", num);
        if (isPrime) {
            // printf("prime");
        } else {
            // printfactors(currNum);
        }
        // printf("\n");
    }
}


void printfactors(Number *number)
{
    bool printval = true;
    for (int k = 0; k < FACTORLEN && number->factors != 0; k++) {
        if (number->factors[k].num != 0) {
            printfactors(&number->factors[k]);
            printval = false;
        }
    }

    if (printval) {
        // printf("%d ", number->num);
    }
}


/* primefactarry: print prime factors using an array to cache previously seen primes */
void pfarray(int printprimes)
{
    int prime;
    int primes[NUMMAX/2 + 2] = {0};
    primes[0] = 2;
    primes[1] = 3;

    for (int num = 2; num <= NUMMAX; num++) {
        int temp = num;
        int i = 0;
        // printf("%i: ", num);
        
        while (temp != 1) {
            while (primes[i] != 0) {
                prime = primes[i];
                if (temp % prime == 0) {
                    temp /= prime;
                    // printf("%d ", prime);
                    i = 0;
                } else {
                    i++;
                }
            }

            prime += 2;
            if (temp % prime == 0) {
                primes[i] = prime;
                temp /= prime;
                // printf("%d ", prime);
            }      
        }

        // printf("\n");
    }
    
    if (printprimes) {
        // printf("primes: ");
        for (int j = 0; primes[j] != 0; j++) {
            // printf("%d ", primes[j]);
        }
    }
}


double gettime(void (*funct)(int), int i)
{
    clock_t start, end;
    start = clock();
    (*funct)(i);
    end = clock();
    return (double)(end - start)/CLOCKS_PER_SEC;
}