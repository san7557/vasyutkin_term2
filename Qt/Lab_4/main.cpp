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

static char *booof = new char[1024];

void printCharsAsHex(unsigned char *buf, int len){
    for(int i=0; i<len; i++) printf("0x%02x ", buf[i]);
    printf("\n\n");
}

//General encryption and decryption function example using FILE I/O and AES256 with a 256-bit key.
int do_crypt(char* textin, char* textout, int do_encrypt){
    unsigned char inbuf[BUFSIZE], outbuf[BUFSIZE + EVP_MAX_BLOCK_LENGTH]; //EVP_MAX_BLOCK_LENGTH = 128 бит
    int inlen, outlen;

    char *buff = new char[inlen+16];
    char *buff_update = new char[inlen+16];
    char *buff_final = new char[inlen+16];

    cout<<textin<<"\n";

    inlen = strlen(textin);
    cout<<inlen<<"\n";

    for(int i = 0; i < inlen; i++)
        inbuf[i] = textin[i];

    unsigned char key[] = "0123456789abcdeF0123456789abcdeF"; //256 бит
    unsigned char iv[] = "1234567887654321"; //128 бит

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, NULL, NULL, do_encrypt);
    OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == 32);
    OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == 16);
    EVP_CipherInit_ex(ctx, NULL, NULL, key, iv, do_encrypt);

    //for(;;){
    //inlen = fread(inbuf, 1, BUFSIZE, in);
    printf("%d B, In:\n", inlen);
    //if (inlen <= 0) break;
    if(!EVP_CipherUpdate(ctx, outbuf, &outlen, inbuf, inlen)){
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }
    //fwrite(outbuf, 1, outlen, out);
    printf("  %d B, OutU:\n", outlen);
    //printCharsAsHex(outbuf, outlen);
    //}
    for(int i = 0; i < inlen+16; i++)
        buff_update[i] = outbuf[i];
    strcpy(buff, buff_update);
    //cout<<"\n"<<outbuf<<"\n"<<buff_update<<"\n"<<buff<<"\n"<<"\n";


    if(!EVP_CipherFinal_ex(ctx, outbuf, &outlen)){
        EVP_CIPHER_CTX_free(ctx);
        return 0;
    }

    //fwrite(outbuf, 1, outlen, out);
    printf("  %d B, OutF:\n", outlen);
    //printCharsAsHex(outbuf, outlen);

    for(int i = 0; i < inlen+16; i++)
        buff_final[i] = outbuf[i];

    strcat(buff, buff_final);
    //cout<<buff_final<<"\n"<<buff;
    strcpy(booof, buff);
    cout<<"\n"<<"\n"<<"gggggggggghghgjhgjhg       "<<booof;

    EVP_CIPHER_CTX_free(ctx);
    return 1;
}

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    //############

    string text1;
    getline(cin, text1);
    int size = text1.length();
    cout<<size<<"\n";
    char* text = new char[size];

    strcpy((char*) text, text1.c_str());
    cout<<text;

    char* textenc = new char[size+16];
    char* textdec = new char[size];

    printf("ENCRYPT:\n\n");
    do_crypt(text, textenc, 1); // 0 - decrypt, 1 - encrypt
    printf("\n---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----\n\n");
    printf("DECRYPT:\n\n");

    strcpy(textenc, booof);

    cout<<"textenc    "<<booof;


    do_crypt(booof, textdec, 0); // 0 - decrypt, 1 - encrypt

    //strcpy(textdec, booof);
    cout<<"textdec   "<<booof;
    //############

    return a.exec();
}
