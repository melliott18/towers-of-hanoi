// stack.c - Contains the function definitions for the Stack ADT.

#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//
// Constructor for a new Stack.
//
// capacity:    The maximum number of items the Stack can hold.
// name:        The Stack ’s single - character identifier.
//
Stack *stack_create(int capacity, char name) {
  Stack *stk = malloc(sizeof(Stack));
  assert(stk != NULL);
  stk->name = name;
  stk->top = -1;
  stk->capacity = capacity;
  stk->items = malloc(sizeof(int) * capacity);
  return stk;
}

//
// Destructor for a Stack.
//
// s:   The Stack to free allocated memory for.
void stack_delete(Stack *s) {
  if (s != NULL && s->items != NULL) {
    free(s->items);
    free(s);
  }
}

//
// Pops an item off a Stack if it isn’t empty.
//
// s:   The Stack to pop an item off of.
//
int stack_pop(Stack *s) {
  if (s != NULL && s->items != NULL) {
    if (stack_empty(s)) {
      return -1;
    }

    int topIndex = s->top;
    int topItem = s->items[topIndex];
    s->top = topIndex - 1;

    return topItem;
  } else {
    return -1;
  }
}

//
// Pushes an item into a Stack if it isn’t full.
//
// s:   The Stack to push an item into.
//
void stack_push(Stack *s, int item) {
  if (s != NULL && s->items != NULL) {
    int topIndex;

    if (s->top == s->capacity - 1) {
      return;
    }

    topIndex = s->top;
    s->items[topIndex + 1] = item;
    s->top = topIndex + 1;
  }
}

//
// Returns true if a Stack is empty and false otherwise.
//
// s:   The Stack to query about being empty.
bool stack_empty(Stack *s) {
  if (s->top == -1) {
    return true;
  } else {
    return false;
  }
}
