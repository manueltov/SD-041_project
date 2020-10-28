#include <stdlib.h>
#include "data.h"
#include "entry.h"
#include "tree-private.h"
#include <stdio.h>

//DESCOBRIR O Q ESTÁ MAL E VERIFICAR
/* Função para criar uma nova árvore tree vazia.
 * Em caso de erro retorna NULL.
 */
struct tree_t *tree_create()
{
    struct tree_t *temp = (struct tree_t *)malloc(sizeof(struct tree_t));
    if (temp != NULL)
    {
        return temp;
    }
    return NULL;
}

//VERIFY
/* Função para libertar toda a memória ocupada por uma árvore.
 */
void tree_destroy(struct tree_t *tree)
{
    /*
    free(tree);
    */
}

//VERIFICAR
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
    if (tree == NULL || key == NULL || value == NULL)
    {
        return -1;
    }
    if (tree->entry != NULL)
    {
        if (key == tree->entry->key)
        {
            entry_replace(tree->entry, key, value);
            return 0;
        }
        else if (key < tree->entry->key)
        {
            if (tree->left != NULL)
            {
                tree_put(tree->left, key, value);
            }
            else
            {
                struct tree_t *temp = tree_create();
                temp->entry = entry_create(key, value);
                temp->right = NULL;
                temp->left = NULL;

                tree->left = temp;
                return 0;
            }
        }
        else
        {
            if (tree->right != NULL)
            {
                tree_put(tree->right, key, value);
            }
            else
            {
                struct tree_t *temp = tree_create();
                temp->entry = entry_create(key, value);
                temp->right = NULL;
                temp->left = NULL;

                tree->right = temp;
                return 0;
            }
        }
    }
    else
    {
        tree->entry = entry_create(key, value);
    }
    return -1;
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
    /*
    // Base Cases: root is null or key is present at root
    if (tree == NULL || tree->entry->key == key)
        return tree->entry->value;

    // Key is greater than root's key
    if (tree->entry->key < key)
        return tree_get(tree->right, key);

    // Key is smaller than root's key
    return tree_get(tree->left, key);
    */
    return NULL;
}

//TODO
/* Função para remover um elemento da árvore, indicado pela chave key,
 * libertando toda a memória alocada na respetiva operação tree_put.
 * Retorna 0 (ok) ou -1 (key not found).
 */
int tree_del(struct tree_t *tree, char *key)
{
    /*
    if (tree == NULL)
        return -1;

    if (tree->entry->key < key)
    {
        tree_del(tree->left, key);
        return 0;
    }
    else if (tree->entry->key > key)
    {
        tree_del(tree->right, key);
        return 0;
    }

    if (tree->left == NULL)
    {
        //struct tree_t *temp = tree->right;
        free(tree->left);
        return 0;
    }
    else if (tree->right == NULL)
    {
        //struct tree_t *temp = tree->left;
        free(tree->right);
        return 0;
    }

    else
    {
        struct tree_t *succParent = tree;

        struct tree_t *succ = tree->right;
        while (succ->left != NULL)
        {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != tree)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        tree->entry->key = succ->entry->key;

        free(succ);
        return 0;
    }
    */
    return -1;
}

//VERIFICAR
/* Função que devolve o número de elementos contidos na árvore.
 */
int tree_size(struct tree_t *tree)
{
    //struct entry_t *temp = tree->entry;
    if (tree->entry == NULL)
        return 0;
    return (tree_size(tree->left) + 1 + tree_size(tree->right));
}

//VERIFICAR
/* Função que devolve a altura da árvore.
 */
int tree_height(struct tree_t *tree)
{
    // if (tree == NULL)
    //     return 0;
    // else
    // {
    //     /* compute the depth of each subtree */
    //     int lDepth = tree_height(tree->left);
    //     int rDepth = tree_height(tree->right);

    //     /* use the larger one */
    //     if (lDepth > rDepth)
    //         return (lDepth + 1);
    //     else
    //         return (rDepth + 1);
    // }
    return -1;
}

/* Função que devolve um array de char* com a cópia de todas as keys da
 * árvore, colocando o último elemento do array com o valor NULL e
 * reservando toda a memória necessária.
 */
char **tree_get_keys(struct tree_t *tree)
{
    //
    return NULL;
}

//VERIFICAR
/* Função que liberta toda a memória alocada por tree_get_keys().
 */
void tree_free_keys(char **keys)
{
    /*
    free(keys);
    */
}