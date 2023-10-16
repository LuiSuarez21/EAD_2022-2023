/**
 * @file HeaderGestores.h
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Header que define dados relativos aos Gestores
 * @version EAD - Projeto Prático (Fase 2) (LESI-PL)
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define U 20
#define L 30 

#pragma region Struct que define um manager

/**
 * @brief Struct que define um manager;
 * 
 */
typedef struct manager{
    char userName[U];
    int id;
    char password[U];
    char location[L];
    struct manager* next;
}manager;

/**
 * @brief Struct da lista Gestores que contem Gestor
 * 
 */
typedef struct managers
{
    struct manager m;
    struct managers* next;
    
}managers;

#pragma endregion


#pragma region Métodos 

//-----------FuncGestores.c-------------------
managers* NewNodsManagers(manager* ct);
manager* NewManager(int idG ,char* userNameG, char* passwordG, char* locationG);
managers* InsertManager(managers* ms, manager* m);
bool RemoveManager(managers* cs, int id);
bool AlterManager(managers* c, int idC, char* nomeC, char* locationC, char *passwordC);
bool SaveManagersTxt(managers* cs);
bool SaveManagersTxt2(managers* cs, int id);
bool SaveManagersBinary(managers* cs);
bool SaveManagersBinary2(managers* cs, int id);
managers* ReadFileManager(managers* newManagers);


//------------Teste das funções e prints dos resultados----------------
void TestAddManager(managers* listM);
void TestRemoveManager(managers* listM);
void TestAlterManager(managers* listM);

#pragma endregion

