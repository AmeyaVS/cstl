/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  This file is part of clib library
 *  Copyright (C) 2011 Avinash Dongre ( dongre.avinash@gmail.com )
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 * 
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "c_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int 
compare_e ( void *left, void *right ) {
    int *l = (int*) left;
    int *r = (int*) right;
    return *l == *r ;
}
static void 
free_e ( void *ptr ) {
    if ( ptr )
    free ( ptr);
}

void 
test_c_deque() {
    int flip = 1;
    int i = 0;
    int limit = 20;

    clib_deque_ptr myDeq = new_c_deque ( 10, compare_e, NULL);
    assert ( clib_deque_null != myDeq );

    for ( i = 0; i <= limit; i++ ) { 
        if ( flip ) {
            push_back_c_deque ( myDeq, &i , sizeof(int));
            flip = 0;
        } else {
            push_front_c_deque ( myDeq, &i, sizeof(int) );
            flip = 1;
        }
    }
   {
       int element;
       front_c_deque ( myDeq, &element );
       assert ( element == limit - 1 );

       back_c_deque ( myDeq, &element );
       assert ( element == limit);
    }
    {
        int element;
        while ( empty_c_deque(myDeq) != clib_true ) {
            pop_front_c_deque ( myDeq, &element );
            printf ( "%d\n", element );
        }
    }
    {
        delete_c_deque(myDeq);
    }
    {
        myDeq = new_c_deque ( 10, compare_e, free_e); 
        for ( i = 0; i <= limit; i ++ ) { 
            int *v = ( int *) malloc ( sizeof ( int ));
            memcpy ( v, &i, sizeof ( int ));
            push_back_c_deque ( myDeq, &v , sizeof(int*));
        }   
    }
    {
        int i = 0;
        int j = 0;
        for ( i = myDeq->head + 1; i < myDeq->tail; i++ ){
            int *elem;
            if ( element_at_c_deque( myDeq, i, &elem ) == CLIB_ERROR_SUCCESS ) {
                assert ( *elem == j++ );
            }
        }
    }
    {
        delete_c_deque(myDeq);
    } 

}
