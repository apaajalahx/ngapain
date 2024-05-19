#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Map{
    size_t sizeOfMaps;
    char **keys;
    char **values;
};

void push(struct Map *map, char key[], char value[]);

int main() {
    struct Map map;
    map.sizeOfMaps = 0;
    push(&map, "abc","def");

    for(size_t i = 0; i < map.sizeOfMaps; ++i) {
        printf("%s\n", map.keys[i]);
        printf("%s\n", map.values[i]);
        printf("%p\n", &map.keys);
        printf("%p\n", &map.keys[i][0]);
        printf("%d\n", i);
        free(map.keys[i]);
        free(map.values[i]);
    }

    free(map.keys);
    free(map.values);
    
    map.sizeOfMaps = 0;
    
    return 0;
}

void push(struct Map *map, char key[], char value[]) {
    
    int size = map->sizeOfMaps;

    // check apakah size lebih besar dari 0, jika lebih besar maka lakukan alokasi ulang, jika tidak maka buat alokasi baru.
    if (size > 0) {

        size += 1;
        
        // alokasi ulang memori
        map->keys = realloc(map->keys, (map->sizeOfMaps + 1) * sizeof(char));
        if (map->keys == NULL) {
            printf("Gagal alokasi ulang memori pada key");
            exit(1);
        }

        map->values = realloc(map->values, (map->sizeOfMaps + 1) * sizeof(char));
        if (map->values == NULL) {
            printf("Gagal alokasi ulang memor pada value");
            exit(1);
        }
    } else {
        
        // alokasi memory
        map->keys = calloc(1, sizeof(char));
        if (map->keys == NULL) {
            printf("Gagal Alokasi memori pada key");
            exit(1);
        }

        map->values = calloc(1, sizeof(char));
        if (map->values == NULL) {
            printf("Gagal Alokasi memori pada value");
            exit(1);
        }

    }

    // alokasi size memori pada array key value
    map->keys[size] = malloc(strlen(key) * sizeof(char));
    if (map->keys[size] == NULL) {
        printf("Gagal Alokasi memori pada key");
        exit(1);
    }

    // alokasi size memori pada array key value
    map->values[size] = malloc(strlen(value) * sizeof(char));
    if (map->values[size] == NULL) {
        printf("Gagal Alokasi memori pada value");
        exit(1);
    }

    strcpy(map->keys[size], key);
    strcpy(map->values[size], value);
    map->sizeOfMaps += 1;
}
