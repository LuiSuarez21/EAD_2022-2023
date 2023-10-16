/**
 * @file FuncAux.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief  Este ficheiro serve para chamar a função que trata do menu do programa;
 * @version Trabalho prático EDA Fase 2
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "HeaderAux.h"


#pragma region Menu da aplicação

/**
 * @brief Função que imprime um menu para o utilizador poder utilizar
 * 
 * @return int 
 */
int Menu (Vertice* listV, managers* listM, clients* listC, transports* listT)
{

   setlocale(LC_ALL, "Portuguese");
   int opc;
   opc = 0;
   bool b = true;
   b = LoadFiles(listM, listC, listT);
   
   while (opc != 14 && b == true)
   {
   printf("\n----------------Menu--------------------\n");
   printf("1) Adicionar um Cliente;\n");
   printf("2) Remover um Cliente;\n");
   printf("3) Alterar um Cliente;\n");
   printf("4) Adicionar um Gestor;\n");
   printf("5) Remover um Gestor;\n");
   printf("6) Alterar um Gestor;\n");
   printf("7) Adicionar um Transporte;\n");
   printf("8) Remover um Transporte;\n");
   printf("9) Alterar um Transporte;\n");
   wprintf(L"10) Registo do aluguer de um determinado meio de mobilidade elétrica;\n");
   wprintf(L"11) Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia;\n");
   wprintf(L"12) Listagem dos meios de mobilidade elétrica existentes numa localização com determinado geocódigo;\n");
   wprintf(L"13) Realizar operações com grafos;\n");
   wprintf(L"14) Sair;\n");
   wprintf(L"\n\nInsira a opção que deseja selecionar: ");
   scanf("%d", &opc);
    
    while (opc < 0 || opc > 14 || opc == 0)
    {
        wprintf(L"\nErro! Por favor insira outro número entre 1 e 14!\n");
        wprintf(L"Insira a opção que deseja selecionar: ");
        scanf("%d", &opc);

    }
    switch (opc)
    {
    case 1:
        listC = TestAddClient(listC);
        break;
    case 2:
        TestRemoveClient(listC);
        break;
    case 3:
        TestAlterClient(listC);
        break;
    case 4:
        TestAddManager(listM);
        break;
    case 5:
        TestRemoveManager(listM);
        break;
    case 6:
        TestAlterManager(listM);
        break;
    case 7:
        TestAddTransport(listT);
        break;
    case 8:
        TestRemoveTransport(listT);
        break;
    case 9:
        TestAlterTransport(listT);
        break;
    case 10:
        break;
    case 11:
        TestOrg(listT);
        break;
    case 12:
        TestListMobilitiesGeo(listT);
        break;
    case 13:
        TestOpGrafos(listT, listC, listV);
    default:
        break;
    }    
    
   }
   
}


#pragma endregion


#pragma region Load dos Files

bool LoadFiles(managers* listM, clients* listC, transports* listT){

    listM = ReadFileManager(listM);
    if (listM == NULL) printf("\nLista dos Managers Vazia!!!");
    listC = ReadFileClient(listC);
    if (listC == NULL) printf("\nLista dos Clientes Vazia!!!");
    listT = ReadFileTransport(listT);
    if (listT == NULL) printf("\nLista dos Transportes Vazia!!!");

    return true;
}

#pragma endregion
