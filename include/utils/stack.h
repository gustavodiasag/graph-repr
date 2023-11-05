#ifndef STACK_H
#define STACK_H

#include "list.h"

/** Structure representing a stack implemented based on a linked list. */
typedef List Stack;

/** Evaluates the number of elements in a stack. */
#define stack_size list_size

/** 
 * Evaluates the data stored in the element at the top of a stack specified by
 * `s`.
 */
#define stack_peek(s) ((s)->_head ? (s)->_head->_data : NULL)

/**
 * Creates a stack. Since a stack is based on a linked list and requires being
 * created in the same way, `stack_new` is defined as `list_new`.
 */
#define stack_new list_new

/** 
 * Initializes a stack. Since a stack is based on a linked list and requires
 * the same initialization, `stack_init` is defined as `list_init`.
 */
#define stack_init list_init

/**
 * Destroys a stack. Since a stack is a linked-list and requires being destroyed
 * in the same way, `stack_destroy` is defined to `list_destroy`.
*/
#define stack_destroy list_destroy

/**
 * Determines whether a stack specified by `s` is empty. Since a stack is a
 * linked list, `stack_is_empty` is defined as `list_is_empty`.
 */
#define stack_is_empty list_is_empty

/**
 * Prints a stack specified by `s`. Since a stack is a linked list and requires
 * being printed in the same way, `stack_print` is defined as `list_print`.
 */
#define stack_print list_print

/**
 * Pushes an element onto the top of a stack specified by `s`.
 * 
 * Returns true if pushing the element is successfull, or false otherwise. 
 */
bool stack_push(Stack* s, const void* data);

/**
 * Pops an element off of a stack specified by `s`. Once finished, `data`
 * points to the data stored in the element that was popped.
 * 
 * Returns true if popping the element was successfull, or false otherwise.
 */
bool stack_pop(Stack* s, void** data);

/** 
 * Checks if a stack specified by `s` contains an element with the same content
 * of `data`.
 * 
 * Returns true if the stack contains the element, or false otherwise. 
 */
bool stack_contains(const Stack* s, const void* data);

#endif