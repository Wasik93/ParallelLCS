#include <stdio.h>     
#include <stdlib.h>     
#include <time.h> 
using namespace std;

int STRING_LENGTH = 8000;

int main(int argc, char* argv[]){
    srand (time(NULL));
    int z;
    z = 50; //liczba zestawow
    if(argc > 1){
        z = atoi(argv[1]);
    }
    if(argc > 2){
        STRING_LENGTH = atoi(argv[2]);
    }
    printf("%d\n",z);
    while (z--)
    {
        for(int i = 0; i < STRING_LENGTH; i++){
            printf("%c",(char)(rand()%26 + 65));
        }        
        printf(" ");
        for(int i = 0; i < STRING_LENGTH; i++){
            printf("%c",(char)(rand()%26 + 65));
        }       
        printf("\n"); 
    }
    return 0;
}