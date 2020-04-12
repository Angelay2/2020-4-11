#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func3(){
    char* lp = (char*)malloc(20);
    strcpy(lp, "linux-68");
    printf("%s\n", lp);

    free(lp);
    free(lp);
}
void func2(){
    func3();
}
void func1(){
    func2();
}
void func(){
    func1();
}
int main(){
    printf("i am main func\n");
    func();
    return 0;
}
