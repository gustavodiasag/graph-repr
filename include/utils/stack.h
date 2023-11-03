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

/** FIXME: Describe macro. */
#define stack_new list_new

/** 
 * Initializes a stack. Since a stack is based on a linked list and requires
 * the same initialization, `stack_init` is defined as `list_init`.
 */
#define stack_init list_init

/**
 * Destroys a stack. Sine a stack is a linked-list and requires being destroyed
 * in the same way, `stack_destroy` is defined to `list_destroy`.
*/
#define stack_destroy list_destroy

/** FIXME: Describe function. */
#define stack_is_empty list_is_empty

/** FIXME: Describe function. */
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

/** FIXME: Describe function. */
bool stack_contains(const Stack* s, const void* data);

#endif