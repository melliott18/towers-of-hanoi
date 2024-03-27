// tower.c

#include "stack.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "srn:"

void stack(int n, char i, char j, char k, int *count);

void iteration(Stack *a, Stack *b, Stack *c, int *count);

Stack *getLeft(Stack *peg, Stack *a, Stack *b, Stack *c);

Stack *getRight(Stack *peg, Stack *a, Stack *b, Stack *c);

void moveDisk(Stack *i, Stack *j);

void printMove(int n, Stack *i, Stack *j);

void recursion(int n, char i, char j, char k, int *count);

int main(int argc, char *argv[]) {
  int option = 0;
  int numDisks = 5;
  int count;
  int *p = &count;
  int stackBool = 0;
  int recurBool = 0;

  if (argc == 1) {
    puts("Error: no arguments supplied!");
    return -1;
  }

  if (argc > 5) {
    puts("Error: too many arguments!");
    return -1;
  }

  // Determine which tests to run
  while ((option = getopt(argc, argv, OPTIONS)) != -1) {
    switch (option) {
    case 's': // Runs in stack mode
      stackBool = 1;
      break;
    case 'r': // Runs in recursive mode
      recurBool = 1;
      break;
    case 'n': // Get number of disks
      numDisks = atoi(optarg);
      break;
    default:
      printf("%s\n", "Error: invalid argument!");
      exit(EXIT_FAILURE);
    }
  }

  if (numDisks <= 0) {
    printf("%s\n", "Error: invalid number of disks!");
    exit(EXIT_FAILURE);
  }

  count = 1;

  for (int i = 0; i < numDisks; i++) {
    count = 2 * count;
  }

  count--;

  if (stackBool == 0 && recurBool == 0) {
    printf("%s\n", "Error: invalid argument!");
    exit(EXIT_FAILURE);
  }

  if (stackBool == 1) {
    printf("================================\n");
    printf("----------   STACKS   ----------\n");
    printf("================================\n");
    stack(numDisks, 'A', 'B', 'C', p);
    printf("\nNumber of moves: %d\n", count);
  }

  if (stackBool == 1 && recurBool == 1) {
    printf("\n");
  }

  count = 0;

  if (recurBool == 1) {
    printf("================================\n");
    printf("--------   RECURSION   ---------\n");
    printf("================================\n");
    recursion(numDisks, 'A', 'B', 'C', p);
    printf("\nNumber of moves: %d\n", count);
  }

  printf("\n");

  return EXIT_SUCCESS;
}

void stack(int n, char i, char j, char k, int *count) {
  // These stacks represent the three pegs in the game
  Stack *a = stack_create(n, i);
  Stack *b;
  Stack *c;

  // Push all of the disks onto the first peg
  for (int e = n; e >= 1; e--) {
    stack_push(a, e);
  }

  // The game is played differently depending
  // on whether the number of disks is even or odd
  if (n % 2 == 1) {
    b = stack_create(n, j);
    c = stack_create(n, k);
  } else {
    b = stack_create(n, k);
    c = stack_create(n, j);
  }

  iteration(a, b, c, count);

  // Free the memory contained in the stacks
  stack_delete(a);
  stack_delete(b);
  stack_delete(c);
}

void iteration(Stack *a, Stack *b, Stack *c, int *count) {
  Stack *min;
  Stack *left;
  Stack *right;

  // count is the minimum number of moves needed
  for (int e = 1; e <= *count; e++) {
    if (a->items[a->top] == 1) {
      min = a;
    } else if (b->items[b->top] == 1) {
      min = b;
    } else if (c->items[c->top] == 1) {
      min = c;
    }

    // The smallest disk moves on every odd numbered move
    // If the number of disks is odd then odd numbered
    // disks always move to the right and even numbered
    // disks move to the left
    // If the number of disks is even then odd numbered
    // disks always move to the left and even numbered
    // disks move to the right
    if (e % 2 == 1) {
      right = getRight(min, a, b, c);
      printMove(min->items[min->top], min, right);
      moveDisk(min, right);
    } else {
      left = getLeft(min, a, b, c);
      right = getRight(min, a, b, c);

      // If the peg to the right of the smallest disk
      // is empty then move the left disk to the right peg
      if (right->top == -1) {
        printMove(left->items[left->top], left, right);
        moveDisk(left, right);
        continue;
      }

      // If the peg to the left of the smallest disk
      // is empty then move the right disk to the left peg
      if (left->top == -1) {
        printMove(right->items[right->top], right, left);
        moveDisk(right, left);
        continue;
      }

      // If the disk to the right of the smallest disk
      // is bigger than the left disk then move the left
      // disk to the right peg
      if (right->items[right->top] > left->items[left->top]) {
        printMove(left->items[left->top], left, right);
        moveDisk(left, right);
        continue;
      }

      // If the disk to the left of the smallest disk
      // is bigger than the right disk then move the right
      // disk to the left peg
      if (left->items[left->top] > right->items[right->top]) {
        printMove(right->items[right->top], right, left);
        moveDisk(right, left);
        continue;
      }
    }
  }
}

// Get the stack to the left of the current stack
Stack *getLeft(Stack *peg, Stack *a, Stack *b, Stack *c) {
  if (peg == a) {
    return c;
  } else if (peg == b) {
    return a;
  } else {
    return b;
  }
}

// Get the stack to the right of the current stack
Stack *getRight(Stack *peg, Stack *a, Stack *b, Stack *c) {
  if (peg == a) {
    return b;
  } else if (peg == b) {
    return c;
  } else {
    return a;
  }
}

// Move a disk from one peg to another
void moveDisk(Stack *i, Stack *j) {
  int popDisk = stack_pop(i);
  stack_push(j, popDisk);
}

void printMove(int n, Stack *i, Stack *j) {
  printf("Move disk %d from peg %c to peg %c\n", n, i->name, j->name);
}

void recursion(int n, char i, char j, char k, int *count) {
  // Move the smallest disk from the source peg to the destination peg
  if (n == 1) {
    printf("Move disk %d from peg %c to peg %c\n", 1, i, j);
    (*count)++;
  } else {
    // Move n-1 disks from the source peg to the temporary peg
    recursion(n - 1, i, k, j, count);
    // Move  disk n from peg i to peg j
    printf("Move disk %d from peg %c to peg %c\n", n, i, j);
    (*count)++;
    // Move n-1 disks from the temporary peg to the destination peg
    recursion(n - 1, k, j, i, count);
  }
}
