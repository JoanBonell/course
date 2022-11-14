#include <stdio.h>

int main(){
    int i = 2;
    printf("%d ", i);
    int *p = NULL;
    *p = 0;
    printf("%d ", *p);
    return 0;
}