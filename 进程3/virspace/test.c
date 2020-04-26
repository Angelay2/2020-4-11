#include <stdio.h>
#include <unistd.h>

int main(){
    int aa = 10;
    int pid = fork();
    if(pid < 0){
        perror("fork");
        return 0;
    }
    else if(pid == 0){
        aa += 10;
        printf("i am a child, aa = [%d][%p]\n", aa, &aa);
    }
    else{
        aa -= 10;
        printf("i am a father, aa = [%d][%p]\n", aa, &aa);
    }

    return 0;
}
