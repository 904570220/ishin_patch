#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ishin_sav_edit.h"

static const char Key[]  = "fuEw5rWN8MBS";
static const int  KeyLen = 12;

uint32_t POLYNOMIAL = 0xEDB88320 ;
int have_table = 0 ;
uint32_t table[256] ;

void make_table()
{
    int i, j, crc ;
    have_table = 1 ;
    for (i = 0 ; i < 256 ; i++)
        for (j = 0, table[i] = i ; j < 8 ; j++)
            table[i] = (table[i]>>1)^((table[i]&1)?POLYNOMIAL:0) ;
}

uint32_t crc32(uint32_t crc, char *buff, int len)
{
    if (!have_table) make_table() ;
    crc = ~crc;
    for (int i = 0; i < len; i++)
        crc = (crc >> 8) ^ table[(crc ^ buff[i]) & 0xff];
    return ~crc;
}

int ishin_decrypt(FILE *in, char *key, int key_len, struct type_ishin_json *json)
{
    size_t sz;
    uint8_t *data;

    fseek(in, 0, SEEK_END);
    sz = ftell(in) - 8;
    data = malloc(sz);
    rewind(in);
    fread(data, 1, sz, in);

    for (int i = 0; i < sz; i++) {
        data[i] ^= key[i % key_len];
    }
    
    json->data = data;
    json->size = sz;
    
    return 1;
}

int ishin_encrypt_out(FILE *out, char *key, int key_len, struct type_ishin_json *json)
{
    const char tailer[] = {0xFF, 0x00, 0x00, 0x00};
    uint32_t crc;
    size_t sz;
    uint8_t *data;

    sz   = json->size;
    data = json->data;

    //calculate crc
    crc = crc32(0, data, sz - 8);
    
    for (int i = 0; i < sz; i++)
        data[i] ^= Key[i % KeyLen];
    //write data
    fwrite(data, 1, sz, out);
    free(data);
    //write crc
    fwrite(&crc, 1, sizeof(crc), out);
    //write tail
    fwrite(tailer, 1, sizeof(tailer), out);
    
    fflush(out);
    
    return 1;
}



