/**
 * @file HeaderTransportes.h
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Header que define dados relativos aos Transportes
 * @version EAD - Projeto Prático (Fase 2) (LESI-PL)
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define  N 50
#define T 20
#define A 10


#pragma region Structs que definem as Mobilidades Electricas

/**
 * @brief Struct que define os transportes
 * 
 */
typedef struct transport{
    int id;
    char typeT[T];
    int battery;
    int price;
    int autonomy;
    char available[A];
    char location[N];
	int x;
    int y;
    struct transport* next;
}transport;

/**
 * @brief Struct de lista de Mobilidades
 * 
 */
typedef struct transports
{
    struct transport t;
    struct transports* next;

}transports;

#pragma endregion


#pragma region Métodos criados

//-----------FuncTransportes.c-------------------
transports* NewNodsTransports(transport* ct);
transports* InsertTransport(transports* cs, transport* ct);
transport* NewTransport(int idT, char* type, char* locationT, char* availableT, int batteryT, int autonomyT, int priceT, int x, int y);
bool RemoveTransport(transports* cs, int id);
bool AlterTransport(transports* c, int idC, char* type, char* locationT, char* availableT, int batteryT, int autonomyT, int priceT, int x, int y);
bool SaveTransportsTxt(transports* cs);
bool SaveTransportsBinary(transports* cs);
bool SaveTransportsTxt2(transports* cs, int id);
bool SaveTransportsBinary2(transports* cs, int id);
transports* ReadFileTransport(transports* newTransport);
bool ListMobilitiesGeo (transports* listT, char* newLocation);
bool OrgDesc(transports* m);


//-----------Testar os métodos-------------------
void TestAddTransport(transports* listT);
void TestRemoveTransport(transports* listT);
void TestAlterTransport(transports* listT);
void TestListMobilitiesGeo(transports* listT);
void TestOrg(transports* listT);

#pragma endregion