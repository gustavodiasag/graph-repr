#ifndef SET_H
#define SET_H

#include <stdlib.h>

#include "common.h"
#include "list.h"

typedef List Set;

/** Evaluates the number of elements in a set specified by `s`. */
#define set_size list_size

/**
 * Creates a set. Since a set is a linked list and requires being created in
 * the same way, `set_new` is defined as `list_new`.
 */
#define set_new list_new

/** 
 * Initializes a set. Since a set is a linked list and requires the same
 * initialization, `set_init` is defined as `list_init`.
 */
#define set_init list_init

/** 
 * Destroys a set. Since a set is a linked list and requires being destroyed in
 * the same way, `set_destroy` is defined as `list_destroy`.
 */
#define set_destroy list_destroy

/** 
 * Prints a set. Since a set is a linked list and requires being formatted in
 * the same way, `set_print` is defined as `list_print`.
 */
#define set_print list_print

/**
 * Inserts a member into the set specified by `s`. The new member contains a
 * pointer to `data`, so the memory referenced by `data` must remain valid as
 * long as the element remains in the set.
 * 
 * Returns true if inserting the member is successfull, or false otherwise.
 */
bool set_ins(Set* s, const void* data);

/**
 * Removes the member matching `data` from the set specified by `s`. Once
 * finished, `data` points to the data stored in the member that was removed.
 * 
 * Returns true if removing the member is successfull, or false otherwise.
*/
bool set_rm(Set* s, void** data);

/**
 * Builds a set that is the union of `s1` and `s2`. Once finished, `s_u`
 * contains the union. Given that `s_u` points to data in `s1` and `s2`, the
 * memory referenced by them must remain valid until `s_u` is freed. 
 * 
 * Returns true if computing the union is successfull, or false otherwise.
 */
bool set_union(Set* s_u, const Set* s1, const Set* s2);

/**
 * Builds a set that is the intersection of `s1` and `s2`. Once finished, `s_i`
 * contains the intersection. Given that `s_i` points to data in `s1` and `s2`,
 * the memory referenced by them must remain valid until `s_i` is freed.
 * 
 * Returns true if computing the intersection is successfull, or false otherwise. 
 */
bool set_intersec(Set* s_i, const Set* s1, const Set* s2);

/**
 * Builds a set that is the difference of `s1` and `s2`. Once finished, `s_d`
 * contains the difference. Given that `s_d` points to data in `s1` and `s2`,
 * the memory referenced by them must remain valid until `s_d` is freed.
 * 
 * Returns true if computing the difference is successfull, or false otherwise.
 */
bool set_diff(Set* s_d, const Set* s1, const Set* s2);

/**
 * Determines whether the data specified by `data` matches that of a member in
 * the set specified by `s`.
 * 
 * Returns 1 if the member is found, or 0 otherwise. 
 */
bool set_is_mem(const Set* s, const void* data);

/**
 * Determines whether the set specified by `s1` is a subset of the set
 * specified by `s2`.
 * 
 * Returns true if the set is a subset, or false otherwise.
*/
bool set_is_sub(const Set* s1, const Set* s2);

/**
 * Determines whether the set specified by `s1` is equal to the set specified
 * by `s2`.
 * 
 * Returns true if the set is equal, or false otherwise.
 */
bool set_is_eq(const Set* s1, const Set* set2);

#endif