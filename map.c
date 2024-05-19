#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Map{
    size_t sizeOfMaps;
    char **keys;
    char **values;
};

void push(struct Map *map, char key[], char value[]);

void free_map(struct Map *map);

int main() {
    struct Map map;
    map.sizeOfMaps = 0;
    map.keys = NULL; // inisialisasi ke NULL untuk menghindari error.
    map.values = NULL; // inisialisasi ke NULL untuk menghindari error.
    
    push(&map, "firstName","dinar");
    push(&map, "lastName", "hamid");

    for(size_t i = 0; i < map.sizeOfMaps; ++i) {
        printf("Key : %s, Value: %s\n", map.keys[i], map.values[i]);
    }

    free_map(&map);

    if (map.keys == NULL && map.values == NULL) {
        printf("Memori berhasil di bebaskan");
    }

    return 0;
}

void push(struct Map *map, char key[], char value[]) {
    
    size_t size = map->sizeOfMaps + 1;
        
    // alokasi ulang memori
    map->keys = realloc(map->keys, size * sizeof(char *));
    if (map->keys == NULL) {
        printf("Gagal alokasi ulang memori pada key");
        exit(1);
    }

    map->values = realloc(map->values, size * sizeof(char *));
    if (map->values == NULL) {
        printf("Gagal alokasi ulang memor pada value");
        exit(1);
    }

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
