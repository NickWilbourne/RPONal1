#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		fprintf(stderr, "Stack ran out!\n");
		exit(-1);
	}
	float val = top->val;
	s->root = top->next;
	free(top);

	return val;
}

int parse_operation(Stack *s, const char *string) {
	char *conv_ret;
	float val = strtod(string, &conv_ret);
	float val2;
	if (conv_ret != string) {
		stack_push(s, val);
	} else if (!strcmp(string, "ADD")) {
		val = stack_pop(s);
		val2 = stack_pop(s);
		stack_push(s, val + val2);
	} else if (!strcmp(string, "SUB")) {
		val = stack_pop(s);
		val2 = stack_pop(s);
		stack_push(s, val2 - val);
	} else if (!strcmp(string, "QUIT")) {
		return 1;
	} else {
		fprintf(stderr, "Invalid value or operation!\n");
	}
	return 0;
}

void print_stack_from(StackItem *i) {
	if (i == NULL)
		return;
	printf("%f	", i->val);
	print_stack_from(i->next);
}

void print_stack(Stack *s) {
	print_stack_from(s->root);
	printf("\n");
}

void clear_stack(Stack *s) {
	StackItem *cur = s->root;
	while (cur != NULL) {
		StackItem *next = cur->next;
		free(cur);
		cur = next;
	}
}

int main() {

	printf("Hello World!\n");

	Stack mainStack;
	while (1) {
		char inputstr[21];
		for (int i = 0; i < 20; i++) {
			inputstr[i] = getchar();
			if (inputstr[i] == '\n' || inputstr[i] == ' ' || inputstr[i] == 0) {
				inputstr[i] = 0;
				break;
			}
			if (i == 19) {
				fprintf(stderr, "Input token too long!\n");
				exit(-1);
			}
		}
		if (parse_operation(&mainStack, inputstr))
			break;
		print_stack(&mainStack);
	}
	clear_stack(&mainStack);

	return 0;
}
