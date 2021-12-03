#include "stdio.h"
#include "stdint.h"


typedef struct ITEM_VENDA{
uint32_t id;
uint32_t id_venda;
uint32_t data;
float desconto;
char obs[1008];
}ITEM_VENDA;

void create(char *archive);
void merge_sort(ITEM_VENDA *array, int e, int d);
void s_archive(char *archive, ITEM_VENDA *array, int n_registros);
void switchPlaces(int *a, int small, int big,ITEM_VENDA item[]);
int partition(int *a, int first, int last, ITEM_VENDA item[]);
void quickSort(int *array,int initial, int final, ITEM_VENDA item[]);