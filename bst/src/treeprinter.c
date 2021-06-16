#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "treeprinter.h"
#include "forest.h"
#include "linkedlist.h"

#define __author__ "Anaxímeno Brito"

#define BRANCH_SPACES "  "
#define VERTICAL_BRANCH "│ "
#define LEFT_BRANCH "└──"
#define RIGHT_BRANCH "┌──"
#define ROOT_BRANCH "━"
#define MIDDLE_BRANCH "├──"



void printTree(btree *root, char tipo)
{
	switch (tipo)
	{
	case 'a':
		/* Mostra a árvore binária em ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Em Ordem\n\n");

		_in_order(root);

		putchar('\n');
		break;
	case 'b':
		/* Mostra a árvore binária em pré ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Pré Ordem\n\n");

		_pre_order(root);

		putchar('\n');
		break;
	case 'c':
		/* Mostra a árvore binária em pós ordem. */
        printf("\n\n\t  BINARY SEARCH TREE");
		printf(" - Pós Ordem\n\n");

		_post_order(root);

		putchar('\n');
		break;
	default:
		printf("\n erro: opção desconhecida, escolha entre (a, b ou c)!\n");
		break;
	}
}


struct _divs *_get_divs(btree *node)
{
    DIVS *divs = (DIVS *) malloc (sizeof(DIVS));
	if (divs != NULL) {
		if (node->level == 0) {
			divs->f = '[';
			divs->s = ']';
		} else {
			divs->f = '<';
			divs->s = '>';
		}
	}
    return divs;
}

	/** Mostram árvores binárias em Ordem */

linked *_in_order_branch_depths(btree *node, linked *list)
{
	/* Procura por posições contrárias reversamente na árvore. */
    char *search_position = !strcmp(node->position, R) ? L : R;
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (!strcmp(parent->position, search_position))
		insertInList(&list, parent->level*DEPTH_MULTIPLIER);

    return _in_order_branch_depths(parent, list);

}


char *_in_order_branch(btree *node)
{
    if (node->level != 0) {
		linked *branch_depths = NULL;

		branch_depths = _in_order_branch_depths(node, branch_depths);
        unsigned short int i;
		/* Profundidade visual do nó na árvore. */
		int depth = node->level*DEPTH_MULTIPLIER;
		for (i = 1 ; i < depth ; ++i)
			printf(isInList(branch_depths, i) ? VERTICAL_BRANCH : BRANCH_SPACES);

		freeList(&branch_depths);

		return !strcmp(node->position, R) ? LEFT_BRANCH : RIGHT_BRANCH;
	}

	else
		return ROOT_BRANCH;
}


void _in_order(btree *root)
{
    if (root == NULL)
		return ;

	_in_order(root->left);

    DIVS *divs = _get_divs(root); /* Tests*/
	printf("%s%c%s%c\n", _in_order_branch(root), divs->f, root->marca.nome, divs->s);
	free(divs);

	_in_order(root->right);
}


	/** Mostram a árvore em pré ordem.  */

linked *_pre_order_branch_depths(btree *node, linked *list)
{
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->right != NULL && parent->right != node)
		insertInList(&list, node->level*DEPTH_MULTIPLIER);

    return _pre_order_branch_depths(parent, list);
}

char *_pre_order_branch(btree *node)
{
    if (node->level != 0) {
		char *branch;
		btree *parent = node->parent;
		linked *branch_depths = NULL;
        unsigned short int i, depth;


		branch_depths = _pre_order_branch_depths(node, branch_depths);


		/* Profundidade visual do nó na árvore. */
		depth = node->level*DEPTH_MULTIPLIER;

		for (i = 1 ; i < depth ; ++i)
			printf(isInList(branch_depths, i) ? VERTICAL_BRANCH : BRANCH_SPACES);

		freeList(&branch_depths);


		if (parent->left != NULL && parent->right != NULL && parent->left == node)
			branch = MIDDLE_BRANCH;
		else
			branch = LEFT_BRANCH;

		return branch;
	}

	else
		return ROOT_BRANCH;
}

void _pre_order(btree *root)
{
	if (root == NULL)
		return ;


	DIVS *divs = _get_divs(root);

	printf("%s%c%s%c\n", _pre_order_branch(root), divs->f, root->marca.nome, divs->s);

	free(divs);
	_pre_order(root->left);
	_pre_order(root->right);
}


	/** Mostram a árvore em pós ordem.  */

linked *_post_order_branch_depths(btree *node, linked *list)
{
    btree *parent = node->parent;

	if (parent == NULL)
		return list;

	else if (parent->left != NULL && parent->left != node)
		insertInList(&list, node->level*DEPTH_MULTIPLIER);

    return _post_order_branch_depths(parent, list);
}


char *_post_order_branch(btree *node)
{
    if (node->level != 0) {
		linked *branch_depths = NULL;
		btree *parent = node->parent;
		char *branch;

		branch_depths = _post_order_branch_depths(node, branch_depths);

        unsigned short int i;
		/* Profundidade visual do nó na árvore. */
		int depth = node->level*DEPTH_MULTIPLIER;
		for (i = 1 ; i < depth ; ++i)
			printf(isInList(branch_depths, i) ? VERTICAL_BRANCH : BRANCH_SPACES);

		freeList(&branch_depths);

		if (parent->right != NULL && parent->left != NULL && parent->right == node)
			branch = MIDDLE_BRANCH;
		else
			branch = RIGHT_BRANCH;

		return branch;
	}

	else
		return ROOT_BRANCH;
}


void _post_order(btree *root)
{
	if (root == NULL)
		return ;


	_post_order(root->left);
	_post_order(root->right);

	DIVS *divs = _get_divs(root);
	printf("%s%c%s%c\n", _post_order_branch(root), divs->f, root->marca.nome, divs->s);
	free(divs);
}

