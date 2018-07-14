#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include "present.h"

int main()
{
    //Present Block Cypher
    //Binary implementation
    //Output in Hexadecimal using Print()

    uint8_t k,plain[64],key[128];//stores 64bit binary plain text and 128 bit binary key
    for(k=0;k<64;++k)plain[k]=0;
    for(k=0;k<128;++k)key[k]=0;
    //Logic
    for(k=1;k<32;++k){
        addRoundKey(plain,key);
        rotateKey(key,k);
        sblock(plain,1);
        pblock(plain);
    }
    addRoundKey(plain,key);
    Print(plain,64);
    return 0;
}
