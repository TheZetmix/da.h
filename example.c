#include <stdio.h>
#include <stdlib.h>
#include "./da.h"

// defining the type
typedef struct {
    int x, y;
} Point;

da_declare(Point); // create a dynamic array type for Point

// da_declare for Point will create a structure like this:
/*
  typedef struct {
      Point *items; // array itself
      size_t size;  // size of the array
      size_t cap;   // capacity of the array (need for optimization)
  } da_Point;
 */

// arr.cap is the size of the allocated memory for the array (in elements), to get
// the size of the array in bytes you need to multiply arr.cap by the size of the type
// for example, the array size for int would be arr.cap * sizeof(int)
// this field is needed in order not to allocate new memory every time an element is
// added to the array, since this is a rather expensive operation; instead, we allocate
// many bytes at once

// dynamic array types can be defined for any
// existing type, including int, float, char, and of course for user declared types (such as Point)

int main() {
    // create an array
    da_Point points = da_init();
    
    // adding elements
    da_append(points, (Point){1, 2});
    da_append(points, (Point){3, 4});
    da_append(points, (Point){5, 6});
    
    // see what's inside
    printf("=== after adding ===\n");
    printf("size: %zu\n", points.size); // to get the size of the array use arr.size
    
    // indexing of array elements is carried out through the items field
    
    for (int i = 0; i < points.size; i++) {
        printf("points[%d] = (%d, %d)\n", i, points.items[i].x, points.items[i].y);
    }
    
    // if you want to get the last element without removing it, use da_last()
    // then the array will remain the same, with the same number of elements
    
    Point last = da_last(points);
    printf("\n=== da_last ===\n");
    printf("last element: (%d, %d)\n", last.x, last.y);
    printf("the size is still %zu\n", points.size);
    
    // and if you want to get the last element and remove it immediately, use da_pop()
    // you will get the value of the last element and it will be removed
    
    Point popped = da_pop(points);
    printf("\n=== da_pop ===\n");
    printf("element removed: (%d, %d)\n", popped.x, popped.y);
    printf("new size: %zu\n", points.size);
    printf("now the last element is (%d, %d)\n", 
           points.items[points.size-1].x, points.items[points.size-1].y);
    
    // clearing memory
    da_free(points);
    
    return 0;
}
