#include "stdio.h"
#include "stdint.h"
#include "bufferSaida.h"
#define LIMIT 10

void merge(char *archiveName, int qttArch, int k, int size){ //Define struct para nos ajudar nos controles de arquivo,Recebe os arquivos ordenados e passa para o searchSmaller                           
    ARCHIVECONTROL *auxStruct;                               
    char nameDefiner[30];
    ITEM_VENDA *buffer = (int*) malloc(size*sizeof(ITEM_VENDA));
    int small = 0;
    int qttBuffer = 0;

    auxStruct = (ARCHIVECONTROL*)malloc(qttArch*sizeof(ARCHIVECONTROL));

    for(int i = 0; i < qttArch; i++){
        sprintf(nameDefiner,"temp%d.txt",i+1); // Definindo nome pra leitura
        auxStruct[i].archive = fopen(nameDefiner,"r");
        auxStruct[i].size = 0;
        auxStruct[i].position = 0;
        auxStruct[i].buffer = (ITEM_VENDA*)malloc(size*sizeof(ITEM_VENDA));
        dataReceive(auxStruct,k);
    }

    while(searchmaller(auxStruct, qttArch, size, &small) == 1){
        buffer[qttBuffer].id = small;
        qttBuffer++;

        if(qttBuffer == size){
            s_archive(archiveName, buffer, size);
            qttBuffer = 0;
        }
    }

    if(qttBuffer != 0) 
        s_archive(archiveName, buffer, qttBuffer);

    for(int i=0; i<qttArch; i++){
        free(auxStruct[i].buffer);
        sprintf(nameDefiner,"temp%d.txt",i+1); // Definindo nome pra leitura
        remove(nameDefiner);
    }
    free(auxStruct);
    free(buffer);
    


}

int searchmaller(ARCHIVECONTROL *archive, int qttArchive, int K, int* small){ //Procura o menor
    int foundPosition = -1;

    for(int i=0; i<qttArchive; i++){ //procura pelo menor elmento
        if(archive[i].position < archive[i].size){
            if(foundPosition == -1)
                foundPosition = i;
            else{
                if(archive[i].buffer[archive[i].position].id < archive[foundPosition].buffer[archive[foundPosition].position].id)
                    foundPosition = i;
            }
        }
    }

    if(foundPosition != -1){ //preenche o buffer com tods os mnores elementos econtrados
        small = archive[foundPosition].buffer[archive[foundPosition].position].id;
        archive[foundPosition].position++;
        if(archive[foundPosition].position == archive[foundPosition].size)
            dataReceive(&archive[foundPosition], K);
    return 1;
    }
    return 0;
}

void dataReceive(ARCHIVECONTROL control[], int k){
    int counter;

    if(control == NULL){
        return;
    }
    control->position = 0;
    control->size = 0;
    for(counter = 0; counter < k; counter++){
        if(fread(control->buffer,sizeof(ITEM_VENDA),217,control->archive)){
            fread(control->buffer,sizeof(ITEM_VENDA),217,control->archive);
            control->size++;
        }
        else{
            fclose(control->archive);
            control->archive = NULL;
            break;
        }
    }
    
}
