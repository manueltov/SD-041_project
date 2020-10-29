// SD-041
// João Figueiredo, nº 53524
// Manuel Tovar, nº 49522
// Mariana Bento, nº 53676

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função que cria um novo elemento de dados data_t e reserva a memória
 * necessária, especificada pelo parâmetro size
 */
struct data_t *data_create(int size)
{ //size = nº de bytes que se pretende alocar

  if (size <= 0)
  {
    return NULL;
  }

  struct data_t *ptr = (struct data_t *)malloc(sizeof(struct data_t));
  //malloc--> recebe o nºde bytes que se pretende alocar(do tipo struct data_t definida em data.h)
  // e devolve um apontador para a memória que foi alocada

  if (ptr == NULL)
  {
    return NULL;
  }

  ptr->datasize = size;     //tamanho do bloco de dados
  ptr->data = malloc(size); //não precisa do tipo (antes de malloc) pq void *data
                            //é um apontador genérico

  //free()-> recebe um apontador que tenha sido retornado por uma chamada a uma
  // função(neste caso, malloc) e LIBERTA o espaço de memória. Free deve ser chamada
  //por esses apontadores e apenas 1x. Serve para quando queremos libertar memória
  // que já não precisamos

  if (ptr->data == NULL)
  {
    free(ptr);
    return NULL;
  }
  return ptr;
}

/* Função idêntica à anterior, mas que inicializa os dados de acordo com
 * o parâmetro data.
 */
struct data_t *data_create2(int size, void *data)
{
  if (size <= 0 || data == NULL)
  {
    return NULL;
  }

  struct data_t *ptr = data_create(size);

  if (ptr == NULL)
  {
    return NULL;
  }

  //memcpy --> copia o conteúdo de uma zona de memória para outra:
  // Ou seja, copia (size) bytes do apontador *data para o apontador ptr(que aponta para data)

  ptr->data = data;
  ptr->datasize = size;

  return ptr;
}

/* Função que elimina um bloco de dados, apontado pelo parâmetro data,
 * libertando toda a memória por ele ocupada.
 */
void data_destroy(struct data_t *data)
{
  if (data != NULL)
  {
    if (data->data != NULL)
      free(data->data);
    free(data); //liberta a memoria alocada em *data
  }
}

/* Função que duplica uma estrutura data_t, reservando a memória
 * necessária para a nova estrutura.
 */
struct data_t *data_dup(struct data_t *data)
{
  if (data != NULL && data->datasize > 1)
  {
    struct data_t *new_data = data_create(data->datasize);
    memcpy(new_data->data, data->data, data->datasize);
    return new_data;

    // void *new_data;
    // memccpy(new_data, data->data, data->datasize, data->datasize);
    // return data_create2(data->datasize, new_data);
  }
  return NULL;
}

/* Função que substitui o conteúdo de um elemento de dados data_t.
*  Deve assegurar que destroi o conteúdo antigo do mesmo.
*/
void data_replace(struct data_t *data, int new_size, void *new_data)
{

  if (data != NULL && new_size > 0 && new_data != NULL)
  {

    data = realloc(data, new_size);
    data_destroy(data);
    data->datasize = new_size;
    data->data = new_data;

    //  memcpy( data->data, new_data, new_size);
  }
}
