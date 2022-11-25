#include "bptree.h"
#include <vector>
#include <sys/time.h>

int middle = (int)ceil(N/2);

struct timeval cur_time(void){
	struct timeval t;
	gettimeofday(&t, NULL);
	return t;
}

void print_tree_core(NODE *n){
	printf("["); 
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]); 
		printf("%d", n->key[i]); 
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");
}

void print_tree(NODE *node) {
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

NODE *find_leaf(NODE *node, int key){
	int kid;

	if (node->isLeaf) return node;
	for (kid = 0; kid < node->nkey; kid++) {
		if (key < node->key[kid]) break;
	}

	return find_leaf(node->chi[kid], key);
}

NODE *insert_in_leaf(NODE *leaf, int key, DATA *data){
	int i;
	if (key < leaf->key[0]) {
		for (i = leaf->nkey; i > 0; i--) {
			leaf->chi[i] = leaf->chi[i-1] ;
			leaf->key[i] = leaf->key[i-1] ;
		} 
		leaf->key[0] = key;
		leaf->chi[0] = (NODE *)data;
	}
	else {
		for (i = 0; i < leaf->nkey; i++) {
			if (key < leaf->key[i]) break;
		}
		for (int j = leaf->nkey; j > i; j--) {
			leaf->chi[j] = leaf->chi[j-1] ;
			leaf->key[j] = leaf->key[j-1] ;
		}

		//Assignment 1: leaf insert
		leaf->key[i] = key;
		leaf->chi[i] = (NODE *)data;
	}
	leaf->nkey++;

	return leaf;
}

NODE *alloc_leaf(NODE *parent){
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->parent = parent;
	node->nkey = 0;

	return node;
}

void insert(int key, DATA *data){
	NODE *leaf;

	if (Root == NULL) {
		leaf = alloc_leaf(NULL);
		Root = leaf;
	}
	else {
		leaf = find_leaf(Root, key);
	}
	if (leaf->nkey < (N-1)) {
		insert_in_leaf(leaf, key, data);
	}
	else {
		//Further codes for Leaf split
	}
}

void init_root(void){
	Root = NULL;
}

int interactive(){
	int key;

	std::cout << "Key: ";
	std::cin >> key;

	return key;
}

int main(int argc, char *argv[]){
	struct timeval begin, end;

	init_root();

	printf("-----Insert-----\n");
	begin = cur_time();
	while (true) {
		insert(interactive(), NULL);
		print_tree(Root);
	}
	end = cur_time();

	return 0;
}
