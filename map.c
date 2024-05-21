#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 
 * get = oke
 * free_map = oke
 * realloc_map = oke
 * push = oke
 * 
*/

struct Map{
    size_t sizeOfMaps;
    char **keys;
    char **values;
};

void push(struct Map *map, char key[], char value[]);

char *get(struct Map *map, char *key);

int del(struct Map *map, char *key);

void free_map(struct Map *map);

void realloc_map(struct Map *map, size_t size);

int main() {
    struct Map map;
    map.sizeOfMaps = 0;
    map.keys = NULL; // inisialisasi ke NULL untuk menghindari error.
    map.values = NULL; // inisialisasi ke NULL untuk menghindari error.
    
    push(&map, "firstName","dinar");
    push(&map, "lastName", "hamid");

    for (size_t i = 0; i < map.sizeOfMaps; ++i) {
        printf("Key : %s, Value: %s\n", map.keys[i], map.values[i]);
    }

    char *test = get(&map, "firstName");
    printf("%s\n", test);

    free_map(&map);

    if (map.keys == NULL && map.values == NULL) {
        printf("Memori berhasil di bebaskan");
    }

    return 0;
}

void push(struct Map *map, char key[], char value[]) {
            
    realloc_map(map, map->sizeOfMaps + 1);

    // alokasi size memori pada array key value
    map->keys[map->sizeOfMaps] = malloc((strlen(key) + 1) * sizeof(char));
    if (map->keys[map->sizeOfMaps] == NULL) {
        printf("Gagal Alokasi memori pada key");
        exit(1);
    }

    // alokasi size memori pada array key value
    map->values[map->sizeOfMaps] = malloc((strlen(value) + 1) * sizeof(char));
    if (map->values[map->sizeOfMaps] == NULL) {
        printf("Gagal Alokasi memori pada value");
        exit(1);
    }

    strcpy(map->keys[map->sizeOfMaps], key);
    strcpy(map->values[map->sizeOfMaps], value);
    map->sizeOfMaps += 1;
}

char *get(struct Map *map, char *key) {

    for (size_t i = 0; i < map->sizeOfMaps; ++i) {
        if (strcmp(map->keys[i], key) == 0) {
            return map->values[i];
        }
    }

    return NULL;

}

int del(struct Map *map, char *key) {
    
    size_t indexOfArray = NULL;

    for (size_t i = 0; i < map->sizeOfMaps; ++i) {
        if (strcmp(map->keys[i], key) == 0) {
            indexOfArray = i+1;
            break;
        }
    }

    if (indexOfArray == NULL) {
        return -1;
    }

    if (indexOfArray == map->sizeOfMaps) {
        free(map->keys[indexOfArray]);
        free(map->values[indexOfArray]);
        map->sizeOfMaps -= 1;
        realloc_map(map, map->sizeOfMaps);
        return 0;
    }

    for (size_t i = indexOfArray - 1; i < map->sizeOfMaps - 1; ++i) {
        free(map->keys[i]);
        free(map->values[i]);
        map->keys[i] = map->keys[i + 1];
        map->values[i] = map->values[i + 1];
    }
    
    free(map->keys[map->sizeOfMaps - 1]);
    free(map->values[map->sizeOfMaps - 1]);
    map->sizeOfMaps -= 1;
    realloc_map(map, map->sizeOfMaps);
    return 0;

}

void free_map(struct Map *map) {
    for (size_t i = 0; i < map->sizeOfMaps; ++i) {
        free(map->keys[i]);
        map->keys[i] = NULL;
        free(map->values[i]);
        map->keys[i] = NULL;
    }

    free(map->keys);
    free(map->values);

    map->sizeOfMaps = 0;
    map->keys = NULL;
    map->values = NULL;
}

void realloc_map(struct Map *map, size_t size) {

    map->keys = realloc(map->keys, size * sizeof(char *));
    if (map->keys == NULL) {
        fprintf(stderr, "Galat : Gagal melakukan alokasi ulang terhadap keys");
        exit(1);
    }

    map->values = realloc(map->values, size * sizeof(char *));
    if (map->values == NULL) {
        fprintf(stderr, "Galat : Gagal melakukan alokasi ulang terhadap value");
        exit(1);
    }

}
