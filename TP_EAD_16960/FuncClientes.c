/**
 * @file FuncClientes.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Ficheiro que trata de lidar com os dados dos clientes
 * @version Trabalho prático EDA Fase 2 (LESI-PL)
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "HeaderClientes.h"



#pragma region Métodos CRUD dos Clientes

/**
 * @brief Função que trata de adicionar um client diretamente na lista;
 * 
 * @param ct 
 * @return clients* 
 */
clients* NewNodsClients(client* ct)
{
    clients* new = (clients*)malloc(sizeof(clients));
    strcpy(new->c.userName ,ct->userName);
    strcpy(new->c.location ,ct->location);
    strcpy(new->c.password ,ct->password);
    new->c.id = ct->id;
    new->c.nif = ct->nif;
    new->c.cash = ct->cash;
    new->c.x = ct->x;
    new->c.y = ct->y;
    new->next = NULL;

    return new;
}


/**
 * @brief Função que trata de criar um novo cliente;
 * 
 * @param idC
 * @param nomeC 
 * @param moradaC 
 * @param passwordC 
 * @param nifC 
 * @param saldoC 
 * @param xC 
 * @param yC 
 * @return client* 
 */
client* NewClient(int idC, char* nomeC, char* moradaC, char* passwordC, int nifC, int saldoC, int xC, int yC)
{
    client* new = (client*)malloc(sizeof(client));
    strcpy(new->userName , nomeC);
    strcpy(new->location , moradaC);
    strcpy(new->password , passwordC);
    new->id = idC;
    new->nif = nifC;
    new->cash = saldoC;
    new->x = xC;
    new->y = yC;
    new->next = NULL;

    return new;
}

/**
 * @brief Insere um novo nodo no final da lista ligada Clientes
 * 
 * @param ct
 * @param cs 
 * @return Clientes* 
 */
clients* InsertClient(clients* cs, client* ct)
{
    clients* verify = cs;
    //se p for null retorna a lista original sem fazer nenhuma alteração
    if (ct == NULL)
    {
        return cs;
    }

    while (verify != NULL)
    {
        if (verify->c.nif == ct->nif)
        {
            return cs;  // Retorna a lista original sem adicionar o novo cliente
        }
        verify = verify->next;
    }


    clients* new = NewNodsClients(ct);
    if(cs == NULL)
    {
        cs = new;
    } 
    else
    {
        clients* actual = cs;
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        
        actual->next = new;
    }
    return cs;
}



/**
 * @brief Função que trata de remover um cliente;
 * 
 * @param cs 
 * @param id 
 * @return true 
 * @return false 
 */
bool RemoveClient(clients* cs, int id) {

    clients* temporario = cs;
    clients* anterior = cs;
    clients* atual = cs;

    //Se não existir retorna false
    if(cs == NULL)
    {
        return cs;
    }

    //Se existir no primeiro nodo, apaga o cliente e retorna true
    if(cs->c.id == id)
    {
        cs = cs->next;
        free(temporario);
        SaveClientsTxt2(cs, id);
        SaveClientsBinary2(cs, id);
        return true;
    }
    //Percorre a lista ate encontrar o cliente com o nif igual, elimina e retorna true
    while(atual != NULL)
    {
        if(atual->c.id == id)
        {
            anterior->next = atual->next;
            free(atual);
            SaveClientsTxt2(cs, id);
            SaveClientsBinary2(cs, id);
            return true;
        }
        anterior = atual;
        atual = atual->next;
    }

    //Se não encontrar retorna false
    return false;
    
}

/**
 * @brief Função de alteração de um Cliente;
 * 
 * @param c 
 * @param idC 
 * @param nomeC 
 * @param nifC 
 * @param cashC 
 * @param locationC 
 * @param passwordC 
 * @param xC 
 * @param yC 
 * @return true 
 * @return false 
 */
bool AlterClient(clients* c, int idC, char* nomeC, int nifC, int cashC, char* locationC, char *passwordC, int xC, int yC) {

    clients* temporario = c;

    //Se não existir retorna false
    if(c == NULL)
    {
        return false;
    }

    while(temporario !=NULL)
    {
        if(temporario->c.id == idC)
        {

            strcpy(temporario->c.userName, nomeC );
            strcpy(temporario->c.location , locationC);
            strcpy(temporario->c.password , passwordC);
            temporario->c.nif = nifC;
            temporario->c.cash = cashC;
            temporario->c.x = xC;
            temporario->c.y = yC;
            SaveClientsTxt(temporario);
            SaveClientsBinary(temporario);
            return true;
        }
        temporario = temporario->next;

    }

    return false;

}

#pragma endregion


#pragma region Manipulação de ficheiros

/**
 * @brief Guarda os clientes num txt;
 * 
 * @param cs 
 * @return true 
 * @return false 
 */
bool SaveClientsTxt(clients* cs)
{
    FILE* file = fopen("DadosClientes.txt", "w");
    if(file == NULL)
    {
        return false;
    }

    clients* actual = cs;
    while(actual != NULL)
    {
        fprintf(file, "%d;%s;%d;%d;%s;%s;%d;%d;\n", actual->c.id, actual->c.userName , actual->c.nif, actual->c.cash, actual->c.location, actual->c.password, actual->c.x, actual->c.y);
        actual = actual->next;
    }

    fclose(file);
    return true;
}


/**
 * @brief Save de clientes menos o pretendido
 * 
 * @param cs 
 * @return true 
 * @return false 
 */
bool SaveClientsTxt2(clients* cs, int id)
{
    FILE* file = fopen("DadosClientes.txt", "w");
    if(file == NULL)
    {
        return false;
    }

    clients* actual = cs;
    while(actual != NULL && id != actual->c.id)
    {
        fprintf(file, "%d;%s;%d;%d;%s;%s;%d;%d;\n", actual->c.id, actual->c.userName , actual->c.nif, actual->c.cash, actual->c.location, actual->c.password, actual->c.x, actual->c.y);
        actual = actual->next;
    }

    fclose(file);
    cs = ReadFileClient(cs);
    return true;
}

/**
 * @brief Função que trata de guardar os clientes num ficheiro binário
 * 
 * @param cs 
 * @return true 
 * @return false 
 */
bool SaveClientsBinary(clients* cs)
{
    FILE* file = fopen("DadosClientesBinario.txt", "wb");
    if(file == NULL)
    {
        return false;
    }

    clients* atual = cs;
    while(atual != NULL)
    {
        fwrite(&atual->c, sizeof(clients), 1, file);
        atual = atual->next;
    }

    fclose(file);

    return true;
}


bool SaveClientsBinary2(clients* cs, int id)
{
    FILE* file = fopen("DadosClientesBinario.txt", "wb");
    if(file == NULL)
    {
        return false;
    }

    clients* atual = cs;
    while(atual != NULL && id != cs->c.id)
    {
        fwrite(&atual->c, sizeof(clients), 1, file);
        atual = atual->next;
    }

    fclose(file);

    return true;
}


/**
 * @brief Função que lê o ficheiro "DadosClientes.txt" e guarda esses dados numa lista dedicada para o efeito;
 * 
 * @param listC 
 * @return true 
 * @return false 
 */
clients* ReadFileClient(clients* newClients){

   FILE* file = fopen("DadosClientes.txt", "r");
   if (file == NULL) 
   {
        return NULL;
   }

   client c;

   while (fscanf(file, "%d;%[^;];%d;%d;%[^;];%[^;];%d;%d;", &c.id, c.userName, &c.nif, &c.cash, c.location, c.password, &c.x, &c.y) == 8)
   {
        client *c1 = NewClient(c.id, c.userName, c.location, c.password, c.nif, c.cash, c.x, c.y);
        newClients = InsertClient(newClients, c1);
   }

   fclose(file);
   return newClients;
}

#pragma endregion


#pragma region Automizar os métodos


/**
 * @brief Num único método, trata de adicionar clientes novos a lista e depois ao grafo criado;
 * 
 * @param listS 
 */
clients* TestAddClient(clients* listS){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    client* p1 = NewClient(0,"Joao", "Rua de Braga", "mt", 999999999, 475.88, 1, 2);
	client* p2 = NewClient(1, "Maria", "Rua da avenida", "mt", 987654321, 100.56, 2, 9);
    client* p3 = NewClient(2, "Sergio", "Rua da avenida", "mt" , 981234321, 100.56, 7, 2);
    client* p4 = NewClient(3, "Luis", "Rua da avenida", "mt" , 987655521, 100.56, 6, 6);
    listS = InsertClient(listS, p1);
    listS = InsertClient(listS, p2);
    listS = InsertClient(listS, p3);
    listS = InsertClient(listS, p4);
    b = SaveClientsTxt(listS);
    b = SaveClientsBinary(listS);
    if (b == false)wprintf(L"\nErro na inserção de dados!\n");
    else{
        wprintf(L"\nSucesso!Inserção bem feita!\n");
    }
    return listS;
}

/**
 * @brief Num único método, trata de remover clientes novos a lista e depois ao grafo criado;
 * 
 * @param listC 
 */
void TestRemoveClient(clients* listC){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    b = RemoveClient(listC, 1);
    if (b == false)wprintf(L"\nErro na remoção de dados!\n");
    else{
        wprintf(L"\nSucesso!Inserção bem feita!\n");
    }
}


/**
 * @brief Num único método, trata de alterar clientes novos a lista e depois ao grafo criado;
 * 
 * @param listC 
 */
void TestAlterClient(clients* listC){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    b = AlterClient(listC, 0, "Luis",123141342,23,"Braga","mmm",1,2);
    if (b == false)wprintf(L"\nErro na alterção de dados!\n");
    else{
        wprintf(L"\nSucesso!Alteração bem feita!\n");
    } 
}

#pragma endregion