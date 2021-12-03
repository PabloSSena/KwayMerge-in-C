#include "stdio.h"
#include "stdint.h"
#include "bufferEntrada.h"
typedef struct ARCHIVECONTROL{
    FILE *archive;
    int position;
    int size;
    ITEM_VENDA *buffer;
}ARCHIVECONTROL;

void merge(char *archiveName, int qttArch, int k, int size);
int searchmaller(ARCHIVECONTROL *archive, int qttArchive, int K, int* small);
void dataReceive(ARCHIVECONTROL control[], int k);