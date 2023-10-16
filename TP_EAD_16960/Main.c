/**
 * @file Main.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Main do projecto 
 * @version EAD - Projeto Prático (Fase 2) (LESI-PL)
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "HeaderAux.h"

/**
 * @brief Função main 
 * 
 * @return int 
 */
int main (){

    int opc;
    opc = 0;
    clients *c = NULL;
    managers *m = NULL;
    transports *t = NULL;
    Vertice* v = NULL;

    opc = Menu(v, m, c, t);
    
    //A libertar a memória das listas utilizadas ao longo do programa;
    free(c);
    free(m);
    free(t);
    free(v);

    return 0;
}

