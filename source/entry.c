#include "entry.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Função que cria uma entry, reservando a memória necessária e
 * inicializando-a com a string e o bloco de dados passados.
 */
struct entry_t *entry_create(char *key, struct data_t *data){

  if( key == NULL || data == NULL){
    return NULL;
  }

  struct entry_t *e = (struct entry_t *) malloc(sizeof(struct entry_t));

  if( e == NULL){
    return NULL;
  }

  e->key = (char *) malloc(sizeof(strlen(key))+1);
  memcpy( e->key, key, strlen(key)+1);

  e->value = data;

  return e;
}

/* Função que inicializa os elementos de uma entry com o
 * valor NULL.
 */
void entry_initialize(struct entry_t *entry){

  if( entry == NULL){
    return;
  }

  entry->key = NULL;
  entry->value = NULL;
}

/* Função que elimina uma entry, libertando a memória por ela ocupada
 */
void entry_destroy(struct entry_t *entry){
  if( entry != NULL){
    if( entry->value != NULL){
        free(entry->value);
        free(entry);
    }
  }
}

/* Função que duplica uma entry, reservando a memória necessária para a
 * nova estrutura.
 */
struct entry_t *entry_dup(struct entry_t *entry){

  if( entry == NULL){
    return NULL;
  }

  struct entry_t *e = (struct entry_t *) malloc(sizeof(struct entry_t));

  if( e == NULL){
    return NULL;
  }

  e->key = strdup( entry->key );
  e->value = data_dup( entry->value );

  return e;
}

/* Função que substitui o conteúdo de uma entrada entry_t.
*  Deve assegurar que destroi o conteúdo antigo da mesma.
*/
void entry_replace(struct entry_t *entry, char *new_key, struct data_t *new_value){

  entry_destroy(entry);
  struct entry_t *new_entry = entry_create(new_key, new_value);

  if( new_entry != NULL){
     entry = realloc(new_entry, strlen(new_key)+1);
  }
}
/* Função que compara duas entradas e retorna a ordem das mesmas.
*  Ordem das entradas é definida pela ordem das suas chaves.
*  A função devolve 0 se forem iguais, -1 se entry1<entry2, e 1 caso contrário.
*/
int entry_compare(struct entry_t *entry1, struct entry_t *entry2){
    int ret;

    ret = memcmp( entry1, entry2, sizeof(struct entry_t));

    if( ret < 0){ // entry1<entry2
      return -1;
    }else if( ret > 0){
      return 1;
    }else{
      return 0;
    }
}
