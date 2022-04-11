
#include <stdio.h>

typedef struct charNode
{
	char data;
	struct charNode* next;
}charNode;

/// <summary>
/// 
/// </summary>
typedef struct Stack
{
	charNode* head;
}Stack;
void initStack(Stack* s);
void destroyStack(Stack* s);
void push(Stack* s, char data);
char pop(Stack* s);
int isEmptyStack(const Stack* s);
void flipBetweenHashes(const char* sentence);
int isPalindrome(Stack* s);
void rotateStack(Stack* s, int n);
int isPalindromeEven(Stack* s, int count);
int isPalindromeOdd(Stack* s, int count);
void printStack(Stack* s);

/***************** Stack ADT Implementation *****************/
void main() {
	Stack s;
	printf("Check the initStack fonctio:\n");
	initStack(&s);
	printf("Check the push fonctio:\n");
	push(&s, 't');
	push(&s, 'i');
	push(&s, 'C');
	push(&s, 'C');
	push(&s, 'i');
	push(&s, 't');
	printStack(&s);
	printf("Check the isEmptyStack fonctio:\n");
	printf("%d\n", isEmptyStack(&s));
	printf("Check the flipBetweenHashes fonctio:\n");
	char sentence[] = "Remem#reb#thi#carp s#tice\0";
	flipBetweenHashes(sentence);
	printf("\nCheck the isPalindrome fonctio:\n");
	printf("%d\n", isPalindrome(&s));
	printStack(&s);
	printf("Check the pop fonctio:\n");
	pop(&s);
	printStack(&s);
	printf("Check the rotateStack fonctio:\n");
	rotateStack(&s, 3);
	printStack(&s);

	printf("\nCheck the destroyStack fonctio:\n");
	destroyStack(&s);
}

void initStack(Stack* s)
{
	s->head = NULL;
}

void destroyStack(Stack* s)
{
	if (s->head == NULL)//if the stack is empty
		return;

	Stack* temp=(Stack*)malloc(sizeof(Stack));
	if (temp == NULL) { printf("alloction fails\n"); exit(1); }
	temp->head = s->head;
	while (s->head->next != NULL) {
		s->head=s->head->next;
		free(temp->head);
		 temp->head=s->head;
	}
	free(temp->head);
	free(temp);
}

void push(Stack* s, char data)
{
	charNode* node = (charNode*)malloc(sizeof(charNode));
	if (node == NULL) { printf("alloction faild\n"); exit(1); }
	node->data = data;

	if (s->head == NULL) {//is the stack is empty
		s->head = node;
		s->head->next = NULL;
		return;
	}

	node->next = s->head;
	s->head = node;

}

char pop(Stack* s)
{
	char pop = s->head->data;
	charNode* temp = s->head;
	s->head = s->head->next;
	free(temp);
	return pop;
}


int isEmptyStack(const Stack* s)
{
	if (s->head == NULL)
		return 1;
	return 0;
}

/*************** Functions using stacks - Implementation/definition **************************/

void flipBetweenHashes(const char* sentence)
{
	if (sentence == NULL)//the sentence is empty
		return;
	char* ptr = sentence;
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	if (temp == NULL) { printf("allocation fild\n"); exit(1); }
	initStack(temp);

	while (*ptr != '\0') {//chack that we no on the end of sentence
		if (*ptr == '#') {
			ptr++;
			while (*ptr != '#' && *ptr != '/0') {
				push(temp, *ptr);
				ptr++;
			}
			if (*ptr == '#') {
				while (!isEmptyStack(temp)) {
					printf("%c", pop(temp));
				}
				ptr++;
			}
		}
		else {
			printf("%c", *ptr);
			ptr++;
		}
	}
	destroyStack(temp);
	free(temp);
}

int isPalindrome(Stack* s)
{
	if (s == NULL)
		return 1;
	if (s->head == NULL)//if the stack is empty
		return 1;
	int count = 0;
	Stack sCount;
	initStack(&sCount);
	while (!isEmptyStack(s)) {
		push(&sCount, pop(s));
		count++;
	}
	while (!isEmptyStack(&sCount)) {
		push(s, pop(&sCount));
	}
	if (count % 2 == 0) {
		return isPalindromeEven(s, count);
	}
	else {
		return isPalindromeOdd(s, count);
	}

}

void rotateStack(Stack* s, int n)
{
	if (s == NULL)
		return;
	if (n < 0)
		return;
	Stack temp1, temp2, temp3, temp4, temp5;
	int count = 0;
	initStack(&temp1);
	initStack(&temp2);
	initStack(&temp3);
	initStack(&temp4);
	initStack(&temp5);
	while (!isEmptyStack(s)) {
		push(&temp5, pop(s));
		count++;
	}
	if (count < n) {
		while (!isEmptyStack(&temp5)) {
			push(s, pop(&temp5));
		}
		return;
	}
	//if n<=count
	//Separation of organs
	for (int i = 0; i < n; i++) {
		push(&temp1, pop(&temp5));
	}
	while (!isEmptyStack(&temp5)) {
		push(&temp2, pop(&temp5));
	}
	//Arranging the organs in a new order
	for (int i = 0; i < n; i++) {
		push(&temp3, pop(&temp1));
	}
	while (!isEmptyStack(&temp2)) {
		push(&temp4, pop(&temp2));
	}
	while (!isEmptyStack(&temp4)) {
		push(s, pop(&temp4));
	}
	while (!isEmptyStack(&temp3)) {
		push(s, pop(&temp3));
	}
}

int isPalindromeEven(Stack* s, int count) {
	int check = 1;
	Stack temp1, temp2, temp3, temp4;
	initStack(&temp1);
	initStack(&temp2);
	initStack(&temp3);
	initStack(&temp4);

	for (int i = 0; i < count / 2; i++) {
		push(&temp1, pop(s));
	}
	for (int i = 0; i < count / 2; i++) {
		push(&temp4, pop(s));
	}
	for (int i = 0; i < count / 2; i++) {
		push(&temp2, pop(&temp4));
	}

	for (int i = 0; i < count / 2; i++) {
		if (temp1.head->data != temp2.head->data) {
			check = 0;
		}
		push(&temp3, pop(&temp1));
		push(&temp4, pop(&temp2));
	}
	for (int i = 0; i < count / 2; i++) {
		push(s, pop(&temp4));
	}
	for (int i = 0; i < count / 2; i++) {
		push(&temp1, pop(&temp3));
	}
	for (int i = 0; i < count / 2; i++) {
		push(s, pop(&temp1));
	}
	return check;
}


int isPalindromeOdd(Stack* s, int count) {
	int check = 1;
	Stack temp1, temp2, temp3, temp4, temp5;
	initStack(&temp1);
	initStack(&temp2);
	initStack(&temp3);
	initStack(&temp4);
	initStack(&temp5);

	for (int i = 0; i < count / 2; i++) {
		push(&temp1, pop(s));
	}
	push(&temp5, pop(s));
	for (int i = 0; i < count / 2; i++) {
		push(&temp4, pop(s));
	}
	for (int i = 0; i < count / 2; i++) {
		push(&temp2, pop(&temp4));
	}

	for (int i = 0; i < count / 2; i++) {
		if (temp1.head->data != temp2.head->data) {
			check = 0;
		}
		push(&temp3, pop(&temp1));
		push(&temp4, pop(&temp2));
	}
	for (int i = 0; i < count / 2; i++) {
		push(s, pop(&temp4));
	}
	push(s, pop(&temp5));
	for (int i = 0; i < count / 2; i++) {
		push(&temp1, pop(&temp3));
	}
	for (int i = 0; i < count / 2; i++) {
		push(s, pop(&temp1));
	}
	return check;
}


void printStack(Stack* s)
{
	charNode* temp = s->head;
	while (temp != NULL)
	{
		printf("%c\n", temp->data);
		temp = temp->next;
	}
}