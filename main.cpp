#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ishin_sav_edit.h"
#include "ishin_patch.h"

using namespace std;

static const char Key[]  = "fuEw5rWN8MBS";
static const int  KeyLen = 12;

int main(int argc, char** argv) {

    FILE *in, *out;
    char *outname, *filename, *ext;
    
    struct type_ishin_json json;
    
    if (argc != 2)
    {
        printf("Usage: %s in.sav\n", argv[0]);
        return 0;
    }
    
    if ((in = fopen(argv[1], "rb")) == NULL)
    {
        perror("Error");
        return 1;
    }
    
    filename = (char *)malloc(sizeof(argv[1]));
    strcpy(filename, argv[1]);
    ext = strrchr(filename, '.');
    filename[(int)(ext - filename)] = '\0';
    
    outname = strcat(filename, "_new.sav");
    
    if ((out = fopen(outname, "wb")) == NULL)
    {
        perror("Error");
        fclose(in);
        return 1;
    }
    
    printf("Writing %s to %s...\n", argv[1], outname);
    
    
    ishin_decrypt(in, (char *)Key, KeyLen, &json);
    ishin_patch(&json);
//    ishin_patch_instructor(&json);
    ishin_encrypt_out(out, (char *)Key, KeyLen, &json);

    fclose(out);
    
    puts("Done!");
    
    return 0;
}

