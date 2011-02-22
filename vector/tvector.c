#include "vector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "algorithms.h"

char *carray[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W","X","Y","Z"};

void 
free_elements ( void *ptr ) {
    if ( ptr ) {
	char *t = (char*) ptr;
	free ( t );
    }
    return;
}

void 
print_elements ( void *v ) {
    char *ch = ( char *) v ;
    printf ( "==> %s\n", ch );
}

void
test_push_back() {
    int array[] = { 0,1,2,3,4,5,6,7,8,9};
    int i = 0;
    vector *vec = vector_new ( 10 ,NULL);
    for ( i = 0; i < sizeof ( array ) / sizeof ( array[0] ); i++) {
	vector_push_back( vec, &i );
    }
    for ( i = 0; i < vector_size(vec); i++) {
	int *v = (int*)vector_element_at ( vec, i );
	if ( v ) {
	    /*printf ( "[%d] --> [%d]\n", i, *v );*/
	}
    }
    vector_clear( vec );
}
void
test_push_back_2() {
    int i = 0;
    char *v;
    vector *vec = vector_new ( 10 ,free_elements );
    for ( i = 0; i < sizeof ( carray ) / sizeof ( carray[0] ); i++) {
	char *t = strdup ( carray[i] );
	vector_push_back( vec, t);
    }
    for ( i = 0; i < vector_size(vec); i++) {
	char *v = (char*)vector_element_at ( vec, i );
	if ( v ) {
	    /*printf ( "[%d] --> [%s]\n", i, v );*/
	}
    }
    for_each ( vector_begin(vec), 
	       vector_end ( vec ), 
	       print_elements);

    vector_clear( vec );
}
void print_elem ( void *v) {
    int i = *(int*)v;
    printf ( "%d\n", i);
}
void
test_algorithms_for_each(){
    int array[] = { 0,1,2,3,4,5,6,7,8,9};
    int i = 0;
    int *v;
    vector *vec = vector_new ( 10 ,NULL);
    int size = sizeof ( array ) / sizeof ( array[0] );
    for ( i = 0; i < size; i++) {
	int *v = ( int *) malloc ( sizeof ( int ));
	memcpy ( v, &i, sizeof ( int ));
	vector_push_back( vec, v );
    }
    for ( i = 0; i < vector_size(vec); i++) {
	int *v = (int*)vector_element_at ( vec, i );
	if ( v ) {
	    printf ( "[%d] --> [%d]\n", i, *v );
	}
    }

    for_each ( vector_begin(vec), 
	       vector_end ( vec ), 
	       print_elem);
    vector_clear( vec );
}
void
test_algorithms_count() {
    int array[] = { 0,1,2,3,2,5,2,7,2,9};
    int i = 0;
    int *v;
    vector *vec = vector_new ( 10 ,NULL);
    int size = sizeof ( array ) / sizeof ( array[0] );
    for ( i = 0; i < size; i++) {
	int *v = ( int *) malloc ( sizeof ( int ));
	memcpy ( v, &i, sizeof ( int ));
	vector_push_back( vec, v );
    }

}

int main ( int argc, char **argv ) {
    test_push_back(); 
    test_push_back_2(); 
    test_algorithms_for_each();
    test_algorithms_count();
    return 0;
}

