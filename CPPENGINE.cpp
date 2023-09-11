#include <iostream>
using namespace std;

#include "defs.h"
#include "init.cpp"


int main() {
    AllInit();
    for(int index = 0; index < BRD_SQ_NUM; ++index){
        if(index%10==0) printf("\n");
        printf("%5d",Sq120ToSq64[index]);
    }

    printf("\n");
    printf("\n");

    for(int index = 0; index < 64; ++index){
        if(index%8==0) printf("\n");
        printf("%5d",Sq64ToSq120[index]);
    }
    return 0;
}