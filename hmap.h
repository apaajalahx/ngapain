#include <stdint.h>


struct Node {
    int hash;
    char* key;
    char* value;

    struct Node* next;
};

/* Singly Linked List Implementation */

struct MapStr {
    size_t size;
    struct Node* bucket[31];
};

/*
 * bucket[computed_hash] = map[key]
 */

struct MapStr* create_map();

int push(const char* key, const char* value);
char* get(const char* key);
int del(const char* key);
int hash(const char* str);
void free_map(struct MapStr* hmap);
