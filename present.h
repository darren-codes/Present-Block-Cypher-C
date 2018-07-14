#ifndef PRESENT_H_INCLUDED
#define PRESENT_H_INCLUDED

void Print(uint8_t a[],int s);
//Prints the binary array passed to it in hexadecimal representation
//Arguments: array, size of array
void addRoundKey(uint8_t plain[], uint8_t key[]);
//Xors the two arrays passed to it
//Arguments: array a, array b
void rotateKey(uint8_t key[], int it);
//Rotates the input array
//Integer 'it' is for xor, as mentioned in present. It represents the round/iteration number
//Arguments: array a, it
void sblock(uint8_t a[], int flag);
//flag value 0 is for sblock operation on key(sblock only on first 8 bits), 1 for plain text
//Arguments: array a, flag
void pblock(uint8_t plain[]);
//Arguments: array a
void xor(uint8_t key[], int it);
//Integer 'it' is for xor, as mentioned in present. It represents the round/iteration number
//Arguments: array a, it
uint8_t i;
uint8_t s[16][4]={{1,1,0,0},{0,1,0,1},{0,1,1,0},{1,0,1,1},{1,0,0,1},{0,0,0,0},{1,0,1,0},{1,1,0,1},{0,0,1,1},{1,1,1,0},{1,1,1,1},{1,0,0,0},{0,1,0,0},{0,1,1,1},{0,0,0,1},{0,0,1,0}};
//Sbox of present
uint8_t p[]={0,16,32,48,1,17,33,49,2,18,34,50,3,19,35,51,4,20,36,52,5,21,37,53,6,22,38,54,7,23,39,55,8,24,40,56,9,25,41,57,10,26,42,58,11,27,43,59,12,28,44,60,13,29,45,61,14,30,46,62,15,31,47,63};
//pbox of present

void Print(uint8_t a[],int s){
    int count;
    for(i=0;i<s;i+=4){
        count=8*a[i]+4*a[i+1]+2*a[i+2]+a[i+3];
        if(count>=0 && count<=9) printf("%c",(count+48));
        else printf("%c",(count+87));
    }
    printf("\n");
}

void addRoundKey(uint8_t plain[], uint8_t key[]){
    for(i=0;i<64;++i)plain[i]^=key[i];
}

void rotateKey(uint8_t key[], int it){
    uint8_t temp[128];
    for(i=0;i<128;++i)temp[(i+67)%128]=key[i];
    for(i=0;i<128;++i)key[i]=temp[i];
    sblock(key,0);
    xor(key,it);
}

void sblock(uint8_t a[], int flag){//0 for key,1 for plain text
    int count;
    if(flag==0){
        for(i=0;i<8;i+=4){
            count=8*a[i]+4*a[i+1]+2*a[i+2]+a[i+3];
            a[i]=s[count][0];a[i+1]=s[count][1];a[i+2]=s[count][2];a[i+3]=s[count][3];
        }
    }
    else {
        for(i=0;i<64;i+=4){
            count=8*a[i]+4*a[i+1]+2*a[i+2]+a[i+3];
            a[i]=s[count][0];a[i+1]=s[count][1];a[i+2]=s[count][2];a[i+3]=s[count][3];
        }
    }
}

void pblock(uint8_t plain[]){
    uint8_t temp[64];
    for(i=0;i<63;++i)temp[(int)p[i]]=plain[i];
    for(i=0;i<63;++i)plain[i]=temp[i];
}

void xor(uint8_t key[], int it){
    for(i=0;i<5;++i){
        if(it%2!=0)key[65-i]^=1;
        else key[65-i]^=0;
        it/=2;
    }
}

#endif // PRESENT_H_INCLUDED
