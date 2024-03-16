#ifndef ISHIN_SAV_EDIT_H
#define ISHIN_SAV_EDIT_H

#ifdef __cplusplus
extern "C" {
#endif

    struct type_ishin_json {
        uint8_t *data;
        size_t   size;
    };

    int ishin_encrypt_out(FILE *out, char *key, int key_len, struct type_ishin_json *json);
    int ishin_decrypt(FILE *in, char *key, int key_len, struct type_ishin_json *json);

#ifdef __cplusplus
}
#endif

#endif /* ISHIN_SAV_EDIT_H */

