#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Hashtable {
    int *rez;
    int hmax;
    char **keys;
    unsigned int (*hash_function)(void*);
    int (*compare_function)(void*, void*);
};
int compare_function_strings(void *a, void *b) {
    char *str_a = (char *)a;
    char *str_b = (char *)b;
    return strcmp(str_a, str_b);
}
unsigned int hash_function_string(void *a) {
    unsigned char *puchar_a = (unsigned char*) a;
    int hash = 5381;
    int c;
    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */
    return hash;
}
void init_ht(struct Hashtable *ht, int hmax,
unsigned int (*hash_function)(void*), int (*compare_function)(void*, void*)) {
    int i;
    if (ht == NULL) {
            return;
        }
    ht->hmax = hmax;
    ht->hash_function = hash_function;
    ht->compare_function = compare_function;
    ht->rez = calloc(hmax, sizeof(int));
    ht->keys = malloc(hmax*sizeof(char*));
    for (i = 0 ; i < hmax; i++)
    	ht->keys[i] = malloc(100*sizeof(char));
}
int pozitie(struct Hashtable *ht, int cursor) {
	int i;
	for (i = cursor+1; i < ht->hmax; i++)
		if (ht->rez[i] == 0)
			return i;
	for (i = 0 ; i < cursor; i++)
		if(ht->rez[i] == 0)
			return i;
	return -1;
}
void put(struct Hashtable *ht, void *key, void *value) {
	int cursor, poz;
	if (ht == NULL) {
       	return;
       }
  	cursor  = ht->hash_function(key) % ht->hmax;
  	if (ht->rez[cursor] == 0) {
  	  	ht->rez[cursor] = 1;
	   	memcpy(ht->keys[cursor], value, 100);
        return;
	}
	if (ht->rez[cursor] != 0) {
		if (ht->compare_function(value, ht->keys[cursor]) == 0) {
			ht->rez[cursor]++;
			return;
		}
		poz = pozitie(ht, cursor);
		if(poz > -1) {
			ht->rez[poz] = 1;
	   		memcpy(ht->keys[poz], value, 100);
	   		}
	}
}
int dimensiune() {
	int nr;
	char *s;
	nr = 0;
	s = malloc(100*sizeof(char));
	while(scanf("%s", s) > 0) {
			nr++;
		}
	free(s);
	return nr;
}
void free_ht(struct Hashtable *ht) {
	int i;
    if (ht == NULL) {
            return;
        }
    for (i = 0; i < ht->hmax; i++)
    	free(ht->keys[i]);
    free(ht->keys);
    free(ht->rez);
    free(ht);
}
void afis(struct Hashtable *ht) {
	int i;
	for ( i = 0; i < ht->hmax; i++)
		if(ht->rez[i] > 0) {
			printf("%s ", ht->keys[i]);
			printf("%d\n", ht->rez[i]);
		}
}
int main()
{
	int dim;
	char *sir;
	struct Hashtable *ht;
	sir = malloc(100*sizeof(char));
	dim = dimensiune();
	ht = malloc(sizeof(struct Hashtable));
	init_ht(ht, dim, hash_function_string, compare_function_strings);
	fseek(stdin, 0, SEEK_SET);
	while(scanf("%s", sir) > 0) {
			put(ht, sir, sir);
		}
	afis(ht);
	free(sir);
	free_ht(ht);
	return 0;
}

