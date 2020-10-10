#include <stdlib.h>
#include "data.h"
#include "tree-private.h"

//DESCOBRIR O Q ESTÁ MAL E VERIFICAR
/* Função para criar uma nova árvore tree vazia.
 * Em caso de erro retorna NULL.
 */
struct tree_t *tree_create()
{
    struct tree_t *temp = (struct tree_t *)malloc(sizeof(struct tree_t));
    temp->entry.key = NULL;
    temp->left = temp->right = NULL;
    return temp;
}

//VERIFY
/* Função para libertar toda a memória ocupada por uma árvore.
 */
void tree_destroy(struct tree_t *tree)
{
    free(tree);
}

//PERCEBER ERRO E VERIFICAR
/* Função para adicionar um par chave-valor à árvore.
 * Os dados de entrada desta função deverão ser copiados, ou seja, a
 * função vai *COPIAR* a key (string) e os dados para um novo espaço de
 * memória que tem de ser reservado. Se a key já existir na árvore,
 * a função tem de substituir a entrada existente pela nova, fazendo
 * a necessária gestão da memória para armazenar os novos dados.
 * Retorna 0 (ok) ou -1 em caso de erro.
 */
int tree_put(struct tree_t *tree, char *key, struct data_t *value)
{
    //erro caso seja nula
    if (tree == NULL)
    {
        return 1;
    }

    //copiar chave //char pode copiar logo
    char new_key = key;

    //copiar valor
    struct data_t *new_data = data_dup(value);

    // create entry
    struct entry_t *new_entry = entry_create(new_key, new_data);

    /* Otherwise, recur down the tree */
    if (entry_compare(new_entry, &(tree->entry)) == 0)
    {
        tree->entry = new_entry;
    }
    else if (entry_compare(new_entry, &(tree->entry)) < 0)
    {
        tree->left = tree_put(tree->left, new_key, &new_data);
        return 0;
    }
    else
    {
        tree->right = tree_put(tree->right, new_key, &new_data);
        return 0;
    }
}

//PERCEBER ERRO E VERIFICAR
/* Função para obter da árvore o valor associado à chave key.
 * A função deve devolver uma cópia dos dados que terão de ser
 * libertados no contexto da função que chamou tree_get, ou seja, a
 * função aloca memória para armazenar uma *CÓPIA* dos dados da árvore,
 * retorna o endereço desta memória com a cópia dos dados, assumindo-se
 * que esta memória será depois libertada pelo programa que chamou
 * a função.
 * Devolve NULL em caso de erro.
 */
struct data_t *tree_get(struct tree_t *tree, char *key)
{
    // Base Cases: root is null or key is present at root
    if (tree == NULL || tree->entry.key == key)
        return tree->entry.value;

    // Key is greater than root's key
    if (tree->entry.key < key)
        return tree_get(tree->right, key);

    // Key is smaller than root's key
    return tree_get(tree->left, key);
}

//TODO
/* Função para remover um elemento da árvore, indicado pela chave key,
 * libertando toda a memória alocada na respetiva operação tree_put.
 * Retorna 0 (ok) ou -1 (key not found).
 */
int tree_del(struct tree_t *tree, char *key)
{
}

//VERIFICAR
/* Função que devolve o número de elementos contidos na árvore.
 */
int tree_size(struct tree_t *tree)
{
    if (tree == NULL)
        return 0;
    else
        return (size(tree->left) + 1 + size(tree->right));
}

//VERIFICAR
/* Função que devolve a altura da árvore.
 */
int tree_height(struct tree_t *tree)
{
    if (tree == NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(tree->left);
        int rDepth = maxDepth(tree->right);

        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

//TODO
/* Função que devolve um array de char* com a cópia de todas as keys da
 * árvore, colocando o último elemento do array com o valor NULL e
 * reservando toda a memória necessária.
 */
char **tree_get_keys(struct tree_t *tree)
{
}

//VERIFICAR
/* Função que liberta toda a memória alocada por tree_get_keys().
 */
void tree_free_keys(char **keys)
{
    free(keys);
}