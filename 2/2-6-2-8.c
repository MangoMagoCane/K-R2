#include <stdio.h>

// exercises 2-6, 2-7, 2-8
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);

int main(void)
{
    // printf("getbits: %u\n", getbits(17, 4, 4));
    // printf("setbits: %u\n", setbits(31, 4, 3, 0));
    // printf("invert: %u\n", invert(0b00010110, 4, 3));
    printf("rightrot: %u\n", rightrot(13, 3));
    
    return 0;
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}
// getbits(17, 4, 4);
// 17 = 00010001
// x >> (4+1-4)
// x >> (1) = 00001000
// 
// ~(11111111 << 4) = ~(11110000) = 00001111
// 00001000 & 11110000 = 00001000 = 8
// 
// 
// getbits(21, 6, 5);
// 21 = 00010101
// x >> (6+1-5)
// x >> (2) = 00000101
// 
// ~(11111111 << 5) = ~(11100000) = 00011111
// 00000101 & 00011111 = 00000101 = 5
// 
// 
// getbits(254, 6, 5);
// 254 = 11111110
// x >> (6+1-5)
// x >> (2) = 00111111
// 
// ~(11111111 << 5) = ~(11100000) = 00011111
// 00111111 & 00011111 = 00011111 = 31
// 

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned dist, mask;
    dist = (p+1-n);
    mask = ~(~0 << n);
    return (x & ~(mask << dist)) | ((y & mask) << dist);

    // d = (p+1-n);
    // y_mask = ~(~0 << n);
    // x_mask = y_mask << d;

    // y = (y & y_mask) << d;
    // b = x & x_mask;
    // return x - b + y;
}
// setbits(20, 4, 3, 15);
// x20 = 00010100, y15 = 0000111
// 
// d = (p+1-n) == 2
// mask = ~(~0 << n) == 00000111
// x &= ~(mask << d) == 00010100 & 11100011 == 00000000
// 
// y = (y & mask) << d == 00011100
// x |= y
// 
// result = 00011100 = 28
// result = 00010100 = 20

unsigned invert(unsigned x, int p, int n)
{
    unsigned mask;
    mask = ~(~0 << n) << (p+1-n);

    return (x & ~mask) | (~x & mask);
}
// d = (p+1-n) == 2
// x = 00010110
// 
// mask = ~(~0 << n) << d == 00011100
// z = x & ~mask == 00010110 & 11100011 == 00000010
// y = (~x & mask) == (~00010110 & 00011100) = (11101001 & 00011100) == 00001000
// return z | y == 00000010 | 00001000 == 00001010
// 
// Result == 00001010
//

unsigned rightrot(unsigned x, int n)
{
    unsigned mask, y, numbits;
    numbits = sizeof(x) * 8;
    mask = ~(~0 << n);
    y = x & mask;

    return (x >> n) | (y << (numbits-n));

}
// x = 00001101 == 13
// n = 3
// numbits = 32
// mask = ~(~0 << n) == 00000111
// y = x & mask == 00000101
// x >>= n
// return x + y << (numbits-n)
// 
// 10100000..00000001 == 2684354561




