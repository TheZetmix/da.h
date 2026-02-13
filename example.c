#include <stdio.h>
#include <stdlib.h>
#include "./da.h"

// defining the type
typedef struct {
    int x, y;
} Point;

da_declare(Point); // create a dynamic array type for Point

// the dynamic array type name for Point will be da_Point (dynamic_array_Point)

// dynamic array types can be defined for any
// existing type, including int, float, char, etc

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
