#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float val;
	void *next;
} StackItem;

typedef struct {
	StackItem *root;
} Stack;

void stack_push(Stack *s, float val) {
	StackItem *new = malloc(sizeof(StackItem));
	new->next = s->root;
	new->val = val;
	s->root = new;
}

float stack_pop(Stack *s) {
	StackItem *top = s->root;
	if (top == NULL) {
		fprintf(stderr, "Stack ran out!");
		exit(-1);
	}
	float val = top->val;
	s->root = top->next;
	free(top);

	return val;
}

int main() {

	printf("Hello World!\n");

	return 0;
}
