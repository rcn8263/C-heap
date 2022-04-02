//
// file: test_HeapDT.c 
// 
// test_HeapDT.c is a simple test of a Heap abstract data type implementation.
// 
// @author CS @ RIT.EDU
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "HeapDT.h"

/// less-than-or-equal compares entries as pointers to int values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 <= *item2
/// @pre values are pointers to integer values.

static int cmpintmin( const void * item1, const void * item2 ) {
    int v1 = *(int*)item1;
    int v2 = *(int*)item2;
    return v1 <= v2;
}

/// greater-than-or-equal compares entries as pointers to int values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 >= *item2
/// @pre values are pointers to integer values.

static int cmpintmax( const void * item1, const void * item2 ) {
    int v1 = *(int*)item1;
    int v2 = *(int*)item2;
    return v1 >= v2;
}

/// prints entry as an int value.
///
/// @param item1 pointer to the value to print
/// @param outfp pointer to output file stream
/// @pre values are pointers to integer values.

static void print_int( const void * item1, FILE * outfp ) {
    if ( ! item1 ) {
        fprintf( outfp, "\n\tWARNING: null entry! This should not happen.\n" );
        return;
    }
    int v1 = *(int*)item1;
    fprintf( outfp, "%d\n", v1 );
    return;
}


/// less-than-or-equal compares entries as pointers to char values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 <= *item2
/// @pre values are pointers to char values.

static int cmpcharmin( const void * item1, const void * item2 ) {
    char v1 = *(char*)item1;
    char v2 = *(char*)item2;
    return v1 <= v2;
}

/// greater-than-or-equal compares entries as pointers to char values.
///
/// @param item1 pointer to the left hand side of the comparison
/// @param item2 pointer to the right hand side of the comparison
/// @return non-zero if *item1 >= *item2
/// @pre values are pointers to char values.

static int cmpcharmax( const void * item1, const void * item2 ) {
    char v1 = *(char*)item1;
    char v2 = *(char*)item2;
    return v1 >= v2;
}

/// prints entry as a single char value.
///
/// @param item1 pointer to the value to print
/// @param outfp pointer to output file stream
/// @pre values are pointers to char values.

static void print_char( const void * item1, FILE * outfp ) {
    if ( ! item1 ) {
        fprintf( outfp, "\n\tWARNING: null entry! This should not happen.\n" );
        return;
    }
    char v1 = *(char*)item1;
    fprintf( outfp, "%c\n", v1 );
    return;
}


/// test_int_heap tests an integer heap.
///
/// @param max_flag is true if heap is a maxheap.

void test_int_heap( bool max_flag ) {

    printf( "test_int_heap using %s ordering\n"
          , (max_flag ? "max" : "min") );

    int test_data[] = { 1, 9, 3, 8, 5, 7, 10, 9, 6, 4, 2, -1 };

    printf( "test data: [ " );
    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( int ); i++ ) {
        printf( "%d ", test_data[i] );
    }
    printf( "]\n" );

    Heap theheap = NULL;
    if ( max_flag ) {
        theheap = hdt_create( 10, cmpintmax, print_int );
    } else {
        theheap = hdt_create( 10, cmpintmin, print_int );
    }

    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( int ); i++ ) {
        hdt_insert_item( theheap, (void*)&test_data[i] );
    }

    printf( "Heap size is now %zu\n", hdt_size( theheap ) );
    fprintf( stderr, "hdt_print to stderr:\n" );
    hdt_print( theheap, stderr ); 

    printf( "Emptying the heap: " );
    while ( hdt_size( theheap ) ) {
        int value = *(int*)hdt_remove_top( theheap );
        printf( "%d ", value );
    }
    printf( "\n" );

    hdt_destroy( theheap );

    return;
}

/// test_char_heap tests a character heap.
///
/// @param max_flag is true if heap is a maxheap.

void test_char_heap( bool max_flag ) {

    printf( "test_char_heap using %s ordering\n"
          , (max_flag ? "max" : "min") );

    char test_data[] = { 'a', 'c', 'g', 'e', 'm', 'u', 'i', 'e', 'o', 'y', 'A' };

    printf( "test data: [ " );
    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( char ); i++ ) {
        printf( "%c ", test_data[i] );
    }
    printf( "]\n" );

    Heap theheap = NULL;
    if ( max_flag ) {
        theheap = hdt_create( 10, cmpcharmax, print_char );
    } else {
        theheap = hdt_create( 10, cmpcharmin, print_char );
    }
    assert( theheap );

    for ( size_t i = 0; i < sizeof( test_data ) / sizeof( char ); i++ ) {
        hdt_insert_item( theheap, (void*)&test_data[i] );
    }

    printf( "Heap size is now %zu\n", hdt_size( theheap ) );
    fprintf( stderr, "hdt_print to stderr:\n" );
    hdt_print( theheap, stderr );

    printf( "Emptying the heap: " );
    while ( hdt_size( theheap ) ) {
        char value = *(char*)hdt_remove_top( theheap );
        printf( "%c ", value );
    }
    printf( "\n" );

    hdt_destroy( theheap );

    return;
}


/// main function runs tests using integer and char data payloads.
/// The tests use both a minheap and a maxheap.
///
/// @return EXIT_SUCCESS

int main( void ) {

    test_int_heap( false );     // minheap
    test_int_heap( true );      // maxheap

    test_char_heap( false );
    test_char_heap( true );

    return EXIT_SUCCESS;
}

