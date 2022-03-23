/**
 * linked_list.c
 *
 * Implements an unsorted linked list with ops insert, append, print, delete.
 * To keep track of list, you'll pass in its head and then update it (if
 * necessary) using double pointers.
 *
 * Compile:  gcc -g -Wall -o linked_list linked_list.c
 * Run:      ./linked_list
 */

#include <stdio.h>
#include <stdlib.h>

struct list_node {
   int data;
   struct list_node *next;
};

/** Insert at the beginning (head) of the list. */
int insert(struct list_node **head, int val) {
    struct list_node *current = *head;
    struct list_node *new_node = malloc(sizeof(struct list_node));
    new_node->data = val;
    new_node->next = current;
    *head = new_node; //*head = *new_node;
    return 0;
}

/** Inserts at a particular position in the list. */
int insert_at(struct list_node **head, int val, int index) {
    struct list_node *current = *head;
    if (index == 0) {
        return insert(head, val);
    }
    //i--; // supposed to be index--; ?
    if (head == NULL) {
        return -1;
    } else {
        int i = 0;
        while ((i < index - 1) && current != NULL) {
            current = current->next;
            i++;
        }
        if (current == NULL) {
            return -1;
        }
        struct list_node *new_node = malloc(sizeof(struct list_node));
        new_node->next = current->next;
        new_node->data = val;
        current->next = new_node;
    }
    return 0;
}

/** Appends to the end of the list */
//can add a tail pointer to make append much quicker
int append(struct list_node **head, int val) {
    struct list_node *current = *head;
    if (current == NULL) {
        return insert(&current, val);
    }
    struct list_node *new_node = malloc(sizeof(struct list_node));
    new_node->data = val;
    new_node->next = NULL;
    while (current->next != NULL) {
        current = current->next; 
    }
    current->next = new_node;
    return 0;
}

/** Prints the list contents */
void print(struct list_node *head) {
    int count = 0;
    struct list_node *current = head;
    while (current->next != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
    printf("\n");
}

/**
 * Deletes a particular value from the list (if there are duplicate values, the
 * first is deleted. */
int delete(struct list_node **head, int val) {
    struct list_node *current = *head;
    struct list_node *previous;
    while (current != NULL && current->data != val) {
        previous = current;
        current = current->next;
    }
    if (current->data != val) {
        return -1;
    }
    previous->next = current->next;
    free(current);
    return 0;
}

/** Delete the node at a particular position in the list */
int delete_at(struct list_node **head, int index) {
    struct list_node *current = *head;
    struct list_node *prev;
    int i = 0;
    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }
    if (current == NULL) { //printf("Position exceded list length\n");
        return -1;
    }
    prev->next = current->next;
    free(current);
    return 0;
}

/**
 * Locate a particular node. Returns the node index if found, or -1 on failure.
 */
int search(struct list_node **head, int val) {
    struct list_node *current = *head;
    int i = 0;
    while (current != NULL && current->data != val) {
        current = current->next;
        i++;
    }
    if (current == NULL || current->data != val) {
        return -1;
    }
    return i;
}

// TODO each function should return 0 to indicate success, -1 on failure.

int main(void)
{
    /* start with empty list */
    struct list_node* head = NULL;
    //printf("%p", head);
    insert(&head, 6);
    //printf("%p", head);
    insert(&head, 13);
    insert(&head, 27);
    insert(&head, 4);
    insert(&head, 1);
    insert(&head, 5);
    insert(&head, 32);
    insert(&head, 8);
    insert(&head, 3);
    print(head);
    //insert_at
    delete(&head, 1);
    print(head);
    append(&head, 11);
    print(head);
    delete_at(&head, 5);
    print(head);
    printf("%d", search(&head, 27));

    return 0;
}