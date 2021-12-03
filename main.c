#include <stdlib.h>
#include<stdint.h>
#include <stdio.h>
//#include "bufferEntrada.h"
#include<limits.h>
#include <math.h>

//CFV
#include<string.h>


typedef struct ITEM_VENDA{
uint32_t id;
uint32_t id_venda;
uint32_t data;
float desconto;
char obs[1008];
}ITEM_VENDA;

typedef struct ARCHIVECONTROL{
    FILE *archive;
    int position;
    int size;
    ITEM_VENDA *buffer;
}ARCHIVECONTROL;

////////////////////////////buffer Entrada abaixo////////////////////////




int main(){
    create("teste.dat");

}
