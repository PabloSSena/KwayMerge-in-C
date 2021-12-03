#include"bufferEntrada.h"
int  LIMIT = 8 * 1024 * 1024;// LIMIT == B
#define N_REGISTER 256000
int E = 1024 * N_REGISTER;

void s_archive(char *archive, ITEM_VENDA *array, int n_registros){
    int counter;
    FILE *newArchive = fopen(archive,"a");

    for(counter = 0; counter < n_registros; counter++){
        fwrite(array,sizeof(ITEM_VENDA),n_registros,newArchive);
    }
}

void switchPlaces(int *a, int small, int big,ITEM_VENDA item[]){  
    ITEM_VENDA receiver;


    int aux = a[big];
    a[big] =  a[small];
    a[small] = aux;

    receiver.id = item[big].id;
    receiver.id_venda = item[big].id_venda;
    receiver.data = item[big].data;
    receiver.desconto = item[big].desconto;
    strcpy(receiver.obs,item[big].obs);

    item[big].id = item[small].id;
    item[big].id_venda = item[small].id_venda;
    item[big].data = item[small].data;
    item[big].desconto = item[small].desconto;
    strcpy(item[big].obs,item[small].obs); 

    item[small].id = receiver.id;
    item[small].id_venda = receiver.id_venda;
    item[small].data = receiver.data;
    item[small].desconto = receiver.desconto;
    strcpy(item[small].obs,receiver.obs);
};

int partition(int *a, int first, int last, ITEM_VENDA item[]){
    int pivot;
    int yellowLine, purpleLine;

    pivot = a[last];
    yellowLine =  first-1;

    for (purpleLine = first; purpleLine < last; purpleLine++){
        if(a[purpleLine] <= pivot){
            yellowLine++;
            switchPlaces(a,yellowLine,purpleLine,item);
        }
    }
    switchPlaces(a,yellowLine+1,last,item);

    return yellowLine + 1;
}
void quickSort(int *array,int initial, int final, ITEM_VENDA item[]){
    int pointer;

    if( initial < final ) {
        pointer = partition(array,initial,final,item);
        quickSort(array,initial,pointer-1,item);
        quickSort(array,pointer+1,final,item);
    }
}

void create(char *archive){
    ITEM_VENDA receiver;
    int archiveNumber = 0, numberOfBuffer = 0,i = 0,readed, aux;
    char *nameDefiner[30]; // O pica ta

    int S = LIMIT / 8;
    int K = ceil(E / LIMIT);
    int qttRegisterBuffer = 217;
    ITEM_VENDA toSave[218];// Lembrar que se guardar mais coisa aqui do que ele aguenta vai dar pau
    uint32_t arrayToquick[qttRegisterBuffer];

    FILE *archiveToRead = fopen(archive,"r");
    int archiveSize = N_REGISTER * 1024; //Pegando tamanho do arquivo, para fazer o calculo

    if(archiveToRead == NULL){
        fprintf(stderr,"\nErro ao abrir arquivo\n");
    }

    while (i != K){
        readed = fread(&toSave[i],sizeof(ITEM_VENDA),qttRegisterBuffer,archiveToRead);

            printf("%d\n",i);
        
            archiveNumber++;
            sprintf(nameDefiner,"testeTemp%d.txt",archiveNumber);
            for(int y = 0; y < qttRegisterBuffer;y++){
                arrayToquick[y] = toSave[y].id;
            }
            quickSort(arrayToquick,0,qttRegisterBuffer - 1,toSave);
            s_archive(nameDefiner,&toSave,qttRegisterBuffer);
        
        i++;
    }

    merge(archive,archiveNumber,K,qttRegisterBuffer);
    //fclose(archiveToRead);

}