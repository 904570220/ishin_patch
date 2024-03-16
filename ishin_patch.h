#ifndef ISHIN_PATCH_H
#define ISHIN_PATCH_H

#ifdef __cplusplus
extern "C" {
#endif

    struct type_ishin_trooper  {
        uint16_t num;
        uint8_t  data[48-2];
    };
    
    int ishin_patch(struct type_ishin_json *json);
    int ishin_patch_instructor(struct type_ishin_json *json);


#ifdef __cplusplus
}
#endif

#endif /* ISHIN_PATCH_H */

