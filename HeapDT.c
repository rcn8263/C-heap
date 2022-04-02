//
// file: HeapDT.c
// description: Heap implementation
//
// @author Ryan Nowak rcn8263

#include <stdio.h>
#include <stdlib.h>
#include "HeapDT.h"

/// Define a Heap structure
struct heap_s {
    void  **array;
    size_t capacity;
    size_t size;
    int (*cmp_fun) (const void * lhs, const void * rhs);
    void (*print_item) (const void * item, FILE * outfp);
};

/// Heap constructor
Heap hdt_create( size_t capacity
               , int (*cmp_fun)( const void * lhs, const void * rhs )
               , void (*print_item)( const void * item, FILE * outfp ) ) {
    
    Heap heap = (Heap) malloc(sizeof(struct heap_s*));
    heap->array = (void **) calloc(capacity, sizeof(void *) * capacity);
    heap->size = 0;
    heap->cmp_fun = cmp_fun;
    heap->print_item = print_item;
    
    return heap;
}

/// Heap destructor
void hdt_destroy( Heap heap ) {
    free(heap->array);
    free(heap);
}

/// Return index of parent of node at index i
static size_t parent(size_t i) {
    return (i - 1) / 2;
}

/// Return index of left child of node at index i
static size_t leftchild(size_t i) {
    return 1 + (i * 2);
}

/// Return index of right child of node at index i
static size_t rightchild(size_t i) {
    return 2 + (i * 2);
}

/// Compares the values of the parent , left child, and right child node
/// and returns the index of the value that should come first
static size_t first_of_3(Heap heap, size_t index) {
    size_t lt = leftchild(index);
    size_t rt = rightchild(index);
    void *thisVal = heap->array[index];
    void *lVal = heap->array[lt];
    void *rVal = heap->array[rt];
    
    if (rt < heap->size) {
        if (heap->cmp_fun(lVal, thisVal) || heap->cmp_fun(rVal, thisVal)) {
            if (heap->cmp_fun(lVal, rVal)) {
                return lt;
            }
            else {
                return rt;
            }
        }
        else {
            return index;
        }
    }
    else if (lt < heap->size) {
        lVal = heap->array[lt];
        
        if (heap->cmp_fun(lVal, thisVal)) {
            return lt;
        }
        else {
            return index;
        }
    }
    else {
        return index;
    }
}

/// Swap two nodes in the heap
static void node_swap(void **array, size_t n1, size_t n2) {
    void *temp = array[n1];
    array[n1] = array[n2];
    array[n2] = temp;
}

/// Sift the heap up
static void sift_up(Heap heap, size_t node_index) {
    void **array = heap->array;
    size_t i = node_index;
    
    while (i > 0 && heap->cmp_fun(array[parent(i)], array[i]) == 0) {
        node_swap(array, parent(i), i);
        i = parent(i);
    }
    
    return;
}

/// Sift the heap down
static void sift_down(Heap heap, size_t start_index) {
    void **array = heap->array;
    size_t curr_index = start_index;
    size_t swap_index = first_of_3(heap, curr_index);
    
    while (swap_index != curr_index) {
        node_swap(array, swap_index, curr_index);
        
        curr_index = swap_index;
        swap_index = first_of_3(heap, curr_index);
    }
}

/// Gets the number of items in the heap
size_t hdt_size( Heap heap ) {
    return heap->size;
}

/// Gets the topmost item in the heap
const void * hdt_top(const Heap heap) {
    return heap->array[0];
}

/// Removes the topmost item from the heap
void * hdt_remove_top( Heap heap ) {
    void *res = heap->array[0];
    heap->size -= 1;
    heap->array[0] = heap->array[heap->size];
    heap->array[heap->size] = 0;
    sift_down(heap, 0);
    
    return res;
}

/// Inserts an item in the heap
void hdt_insert_item( Heap heap, const void * item ) {
    if (heap->size == heap->capacity) {
        heap->array = NULL;
        size_t new_capacity = heap->capacity + 1000;
        char ** temp = (char **) realloc(heap->array, new_capacity * sizeof(void *));
        size_t new_space = heap->capacity * sizeof(void *);
        char *ptr = (char *) temp + new_space;
        
        for (size_t j = 0; j < new_capacity * sizeof(void *) - new_space; j++) {
            ptr[j] = '\0';
        }
        
        heap->array = (void **) temp;
        heap->capacity = new_capacity;
    }
    
    heap->array[heap->size] = (void *) item;
    sift_up(heap, heap->size);
    heap->size += 1;
    
    return;
}

/// Recusrsion function to print Hepa items into specified output
static void hdt_print_rec( Heap heap, size_t index, FILE * outfp ) {
    if (index < heap->size) {
        heap->print_item(heap->array[index], outfp);
        hdt_print_rec(heap, leftchild(index), outfp);
        hdt_print_rec(heap, rightchild(index), outfp);
    }
}

/// Prints the Heap items into specified output
void hdt_print( Heap heap, FILE * outfp ) {
    size_t start_index = 0;
    /**if (start_index < heap->size) {
        heap->print_item(heap->array[start_index], outfp);
        hdt_print_rec(heap, leftchild(start_index), outfp);
        hdt_print_rec(heap, rightchild(start_index), outfp);
    }**/
    
    hdt_print_rec(heap, start_index, outfp);
}
