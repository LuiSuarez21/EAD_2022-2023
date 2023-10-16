/**
 * @file HeaderAux.h
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Header do projecto
 * @version EAD - Projeto Prático (Fase 2) (LESI-PL)
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "HeaderGestores.h"
#include "HeaderGrafo.h"


#pragma region Métodos

//-----------FuncAux.c-------------------
int Menu (Vertice* listV,managers* listM, clients* listC, transports* listT);
bool LoadFiles(managers* listM, clients* listC, transports* listT);

#pragma endregion