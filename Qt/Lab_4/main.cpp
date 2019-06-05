#include <QCoreApplication>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <string>
#include <cstring>

#define BUFSIZE 1024 //Любое число байт, кратное 16.
using namespace std;

char *booof = new char[1024];

void printCharsAsHex(unsigned char *buf, int len){
    for(int i=0; i<len; i++) printf("0x%02x ", buf[i]);
    printf("\n\n");
}

//General encryption and decryption function example using FILE I/O and AES256 with a 256-bit key.
int do_crypt(char* textin, int do_encrypt){
    unsigned char inbuf[BUFSIZE], outbuf[BUFSIZE + EVP_MAX_BLOCK_LENGTH]; //EVP_MAX_BLOCK_LENGTH = 128 бит
    int inlen, outlen;

    inlen = 0;
    outlen = 0;
    inlen = strlen(textin);

    char *buff = new char[inlen+16];
    char *buff_update = new char[inlen+16];
    char *buff_final = new char[inlen+16];

    cout<<textin<<"\n";

    for(int i = 0; i < inlen+16; i++)
        inbuf[i] = textin[i];

    unsigned char key[] = "0123456789abcdeF0123456789abcdeF"; //256 бит
    unsigned char iv[] = "1234567887654321"; //128 бит

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, NULL, NULL, do_encrypt);
    OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == 32);
    OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == 16);
    EVP_CipherInit_ex(ctx, NULL, NULL, key, iv, do_encrypt);

    printf("%d B, In:\n", inlen);

    if(!EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen)){
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    for(int i = 0; i < inlen+16; i++)
        buff_update[i] = outbuf[i];
    strcpy(buff, buff_update);


    printf("  %d B, OutU:\n", outlen);

    if(!EVP_CipherFinal_ex(ctx, outbuf, &outlen)){
        EVP_CIPHER_CTX_free(ctx);
        //return 0;
    }

    printf("  %d B, OutF:\n", outlen);

    if(do_encrypt == 1){
        for(int i = 0; i < inlen+16; i++)
            buff_final[i] = outbuf[i];
        strcat(buff, buff_final);
    }
    delete [] booof;
    strcpy(booof, buff);
    cout<<"\n"<<"\n"<<"booof       "<<booof;

    delete[] buff;
    delete[] buff_final;
    delete[] buff_update;

    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    string text1;
    getline(cin, text1);
    int size = text1.length();
    char* text = new char[size];
    strcpy((char*) text, text1.c_str());

    printf("ENCRYPT:\n\n");
    do_crypt(text, 1); // 0 - decrypt, 1 - encrypt
    printf("\n---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----\n\n");
    printf("DECRYPT:\n\n");

    do_crypt(booof, 0); // 0 - decrypt, 1 - encrypt

    delete[] booof;
    return a.exec();
}

//TEST
