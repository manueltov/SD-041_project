#include "data.h"
#include "tree-private.h"
#include "entry.h"
#include <stdlib.h>
#include <stdio.h>

//Cria nó vazio
struct treeNode *create_node(){
  struct treeNode *node = (struct treeNode *) malloc(sizeof(struct treeNode));
  if( node == NULL || node->entry == NULL){
    return NULL;
  }
  node->entry = NULL;
  node->left = NULL;
  node->right = NULL;

  return node;
}
/* Função para criar uma nova árvore tree vazia.
 * Em caso de erro retorna NULL.
 */
struct tree_t *tree_create(){

  struct tree_t *tree = (struct tree_t *) malloc(sizeof(struct tree_t));

  if( tree == NULL || tree->root == NULL){
    return NULL;
  }
  tree->root = create_node();
  /*tree->root->left = create_node();
  tree->root->right = create_node();*/

  return tree;
}

struct treeNode *destroy_node(struct treeNode *node){
  if( node != NULL){
    if( node->entry != NULL){
        entry_destroy(node->entry);
    }
  }
}

/* Função para libertar toda a memória ocupada por uma árvore.
 */
void tree_destroy(struct tree_t *tree){

  if( tree != NULL ){
    if( tree->root->left != NULL){
      destroy_node(tree->root->left);
    }
    if(tree->root->right != NULL){
      destroy_node(tree->root->right);
    }
    destroy_node(tree->root);
  }
}

/* Função para adicionar um par chave-valor à árvore.
 * Os dados de entrada desta função deverão ser copiados, ou seja, a
 * função vai *COPIAR* a key (string) e os dados para um novo espaço de
 * memória que tem de ser reservado. Se a key já existir na árvore,
 * a função tem de substituir a entrada existente pela nova, fazendo
 * a necessária gestão da memória para armazenar os novos dados.
 * Retorna 0 (ok) ou -1 em caso de erro.
 */
int tree_put(struct tree_t *tree, char *key, struct data_t *value){

  if( tree == NULL || key == NULL || value == NULL){
    return -1;
  }



}

/* Função para obter da árvore o valor associado à chave key.
 * A função deve devolver uma cópia dos dados que terão de ser
 * libertados no contexto da função que chamou tree_get, ou seja, a
 * função aloca memória para armazenar uma *CÓPIA* dos dados da árvore,
 * retorna o endereço desta memória com a cópia dos dados, assumindo-se
 * que esta memória será depois libertada pelo programa que chamou
 * a função.
 * Devolve NULL em caso de erro.
 */
struct data_t *tree_get(struct tree_t *tree, char *key){
  /*// Base Cases: root is null or key is present at root
  if (tree == NULL || tree->root->entry->key == key)
      return tree->root->entry->value;

  // Key is greater than root's key
  if (tree->root->entry->key < key)
      return tree_get(tree->root->right, key);

  // Key is smaller than root's key
  return tree_get(tree->root->left, key);
*/
}

/* Função para remover um elemento da árvore, indicado pela chave key,
 * libertando toda a memória alocada na respetiva operação tree_put.
 * Retorna 0 (ok) ou -1 (key not found).
 */
int tree_del(struct tree_t *tree, char *key){

}

/* Função que devolve o número de elementos contidos na árvore.
 */
int tree_size(struct tree_t *tree){
  if(tree == NULL || tree->root == NULL){
    return 0;
  }
  return tree->size;
}

//Devolve a altura máxima
int tree_maxHeigth(struct treeNode *node){
  if(node == NULL)
      return 0;
  else{

    //profundidade de cada subtree
    int l_heigth = tree_maxHeigth(node->left);
    int r_heigth = tree_maxHeigth(node->right);

    if( l_heigth > r_heigth)
        return (l_heigth+1);
    else return (r_heigth+1);
    }
}

/* Função que devolve a altura da árvore.
 */
int tree_height(struct tree_t *tree){
  if( tree == NULL || tree->root == NULL){
    return 0;
  }
  return tree_maxHeigth(tree->root);
}

/* Função que devolve um array de char* com a cópia de todas as keys da
 * árvore, colocando o último elemento do array com o valor NULL e
 * reservando toda a memória necessária.
 */
char **tree_get_keys(struct tree_t *tree){

}

/* Função que liberta toda a memória alocada por tree_get_keys().
 */
void tree_free_keys(char **keys){

}
