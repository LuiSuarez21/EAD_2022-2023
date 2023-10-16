/**
 * @file HeaderClientes.h
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


#pragma region Structs que definem um Cliente

/**
 * @brief truct que define um Cliente
 * 
 */
typedef struct client{
    int id;
    char userName[20];
    int nif;
    int cash;
    char location[50];
    char password[20];
    int x;
    int y;
    struct client* next;
}client;

/**
 * @brief Struct da lista de Clientes
 * 
 */
typedef struct clients
{
    struct client c;
    struct clients* next;
    
}clients;


#pragma endregion


#pragma region Métodos

//-----------FuncClientes.c-------------------
clients* NewNodsClients(client* c);
client* NewClient(int idC, char* nomeC, char* moradaC, char* passwordC, int nifC, int saldoC, int xC, int yC);
clients* InsertClient(clients* c, client* ct);
bool AlterClient(clients* c, int idC, char* nomeC, int nifC, int cashC, char* locationC, char *passwordC, int xC, int yC);
bool RemoveClient(clients* c, int id);
bool SaveClientsTxt(clients* cs);
bool SaveClientsTxt2(clients* cs, int id);
bool SaveClientsBinary(clients* cs);
bool SaveClientsBinary2(clients* cs, int id);
clients* ReadFileClient(clients* newClients);


//-----------Testar os métodos-------------------
void TestAddClient(clients* listS);
void TestRemoveClient(clients* listS);
void TestAlterClient(clients* listS);

#pragma endregion
