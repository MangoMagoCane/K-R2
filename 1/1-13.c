#include <stdio.h>

#define MAX_WL 16
#define BIN_SIZE 4

#define IN 1
#define OUT 0

int main(void)
{
    int c;
    int wl_freq[MAX_WL];
    int curr_wl = 0;
    int state = OUT;

    for (int i = 0; i < MAX_WL; ++i) {
        wl_freq[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (curr_wl <= MAX_WL) {
                wl_freq[curr_wl-1] += 1;
            }

            curr_wl = 0;
            state = OUT;
        } 
        else if (state == OUT) {
            state = IN;
        }

        if (state == IN) {
            curr_wl += 1;
        }
    }

    // for (int i = 0; i < MAX_WL; i++) {
    //     printf("%d: %d\n", i+1, wl_freq[i]);
    // }

    // Horizontal implementation
    int bin_sum = 0;

    for (int i = BIN_SIZE; i <= MAX_WL; i += BIN_SIZE) {
        for (int j = i - BIN_SIZE; j < i; ++j) { 
            bin_sum += wl_freq[j];
        }

        if (i - BIN_SIZE + 1 <= 9) {
            printf(" ");
        }
        printf("%d-", i - BIN_SIZE + 1, i);
    
        printf("%d", i);
        if (i <= 9) {
            printf(" ");
        }

        printf("| ");
        for (int k = 0; k < bin_sum; ++k) {
            printf("*");
        }
        printf("\n");

        bin_sum = 0;
    }
    
    return 0;
}