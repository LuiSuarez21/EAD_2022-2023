/**
 * @file FuncGestores.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Ficheiro que trata de manipular dados dos Gestores
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
#include "HeaderGestores.h"


#pragma region Métodos CRUD dos Gestores


/**
 * @brief Função que trata de acrexentar um nó a lista de Managers
 * 
 * @param ct 
 * @return managers* 
 */
managers* NewNodsManagers(manager* ct)
{
    managers* new_manager = (managers*)malloc(sizeof( managers));
    strcpy(new_manager->m.userName, ct->userName);
    strcpy(new_manager->m.password, ct->password);
    strcpy(new_manager->m.location, ct->location);
    new_manager->m.id = ct->id;
    return new_manager;
}


/**
 * @brief Função que trata de criar um novo Manager
 * 
 * @param idG 
 * @param userNameG 
 * @param passwordG 
 * @param locationG 
 * @return manager* 
 */
manager* NewManager(int idG ,char* userNameG, char* passwordG, char* locationG)
{
    manager* new = (manager*)malloc(sizeof(manager));
    strcpy(new->userName , userNameG);
    strcpy(new->location , locationG);
    strcpy(new->password , passwordG);
    new->id = idG;
    new->next = NULL;
    return new;
}



/**
 * @brief Função que insere um novo manager na lista
 * 
 * @param ms 
 * @param newM 
 * @return managers* 
 */
managers* InsertManager(managers* ms, manager* newM)
{
    managers* verify = ms;
    //se p for null retorna a lista original sem fazer nenhuma alteração
    if (newM == NULL)
    {
        return ms;
    }

    while (verify != NULL)
    {
        if (verify->m.id == newM->id)
        {
            return ms;  // Retorna a lista original sem adicionar o novo cliente
        }
        verify = verify->next;
    }


    managers* new = NewNodsManagers(newM);
    if(ms == NULL)
    {
        ms = new;
    } 
    else
    {
        managers* actual = ms;
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        
        actual->next = new;
    }
    return ms;
}


/**
 * @brief Função que remove um manager da lista
 * 
 * @param cs 
 * @param id 
 * @return true 
 * @return false 
 */
bool RemoveManager(managers* cs, int id) {

    managers* temporario = cs;
    managers* anterior = cs;
    managers* atual = cs;
    bool b = true;

    //Se não existir retorna false
    if(cs == NULL)
    {
        return false;
    }

    //Se existir no primeiro nodo, apaga o manager e retorna true
    if(cs->m.id == id)
    {
        cs = cs->next;
        free(temporario);
        b = SaveManagersTxt2(cs, id);
        b = SaveManagersBinary2(cs, id);
        return b;
    }
    //Percorre a lista ate encontrar o manager com o nif igual, elimina e retorna true
    while(atual != NULL)
    {
        if(atual->m.id == id)
        {
            anterior->next = atual->next;
            free(atual);
            b = SaveManagersTxt2(cs, id);
            b = SaveManagersBinary2(cs, id);
            return b;
        }
        anterior = atual;
        atual = atual->next;
    }

    //Se não encontrar retorna false
    return false;
    
}


/**
 * @brief Altera a informação de um manager
 * 
 * @param c 
 * @param idC 
 * @param nomeC 
 * @param locationC 
 * @param passwordC 
 * @return true 
 * @return false 
 */
bool AlterManager(managers* c, int idC, char* nomeC, char* locationC, char *passwordC) {

    managers* temporario = c;
    bool b = true;

    //Se não existir retorna false
    if(c == NULL)
    {
        return false;
    }

    while(temporario !=NULL)
    {
        if(temporario->m.id == idC)
        {
            strcpy(temporario->m.userName, nomeC );
            strcpy(temporario->m.location , locationC);
            strcpy(temporario->m.password , passwordC);
            b = SaveManagersTxt(temporario);
            b = SaveManagersBinary(temporario);
            return b;
        }
        temporario = temporario->next;

    }

    return false;

}

#pragma endregion



#pragma region Manipulação de ficheiros


/**
 * @brief Guarda os dados dos managers num txt
 * 
 * @param cs 
 * @return true 
 * @return false 
 */
bool SaveManagersTxt(managers* cs)
{
    FILE* file = fopen("DadosGestores.txt", "w");
    if(file == NULL)
    {
        return false;
    }

    managers* new = cs;
    while(new != NULL)
    {
        
        fprintf(file,"%d;%s;%s;%s;\n", new->m.id, new->m.userName, new->m.password, new->m.location);
        new = new->next;
    }

    fclose(file);
    return true;
}



/**
 * @brief Guarda os dados dos managers num txt
 * 
 * @param cs 
 * @param id
 * @return true 
 * @return false 
 */
bool SaveManagersTxt2(managers* cs, int id)
{
    FILE* file = fopen("DadosGestores.txt", "w");
    if(file == NULL)
    {
        return false;
    }

    managers* new = cs;
    while(new != NULL && id != cs->m.id) 
    {
        
        fprintf(file,"%d;%s;%s;%s;\n", new->m.id, new->m.userName, new->m.password, new->m.location);
        new = new->next;
    }

    fclose(file);
    return true;
}


/**
 * @brief Guarda os dados dos managers em binário
 * 
 * @param cs 
 * @return true 
 * @return false 
 */
bool SaveManagersBinary(managers* cs)
{
    FILE* file = fopen("DadosGestoresBinario.txt", "wb");
    if(file == NULL)
    {
        return false;
    }

    managers* atual = cs;
    while(atual != NULL)
    {
        fwrite(&atual->m, sizeof(managers), 1, file);
        atual = atual->next;
    }

    fclose(file);
    return true;
}



/**
 * @brief Guarda os dados dos managers em binário
 * 
 * @param cs 
 * @param id
 * @return true 
 * @return false 
 */
bool SaveManagersBinary2(managers* cs, int id)
{
    FILE* file = fopen("DadosGestoresBinario.txt", "wb");
    if(file == NULL)
    {
        return false;
    }

    managers* atual = cs;
    while(atual != NULL && cs->m.id)
    {
        fwrite(&atual->m, sizeof(managers), 1, file);
        atual = atual->next;
    }

    fclose(file);
    return true;
}


/**
 * @brief Le os dados dos managers em txt
 * 
 * @return managers* 
 */
managers* ReadFileManager(managers* newManagers){

   FILE* file = fopen("DadosGestores.txt", "r");
   if (file == NULL) 
   {
        return NULL;
   }

   manager g;

   while (fscanf(file, " %d;%[^;];%[^;];%[^;];", &g.id, g.userName, g.password, g.location) == 4)
   {
        manager *m1 = NewManager(g.id, g.userName, g.password, g.location);
        newManagers = InsertManager(newManagers, m1);
   }

   fclose(file);
   return newManagers;
}

#pragma endregion


#pragma region Automizar os métodos


/**
 * @brief Função que vai testar a adição de managers
 * 
 * @param listM 
 */
void TestAddManager(managers* listM){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    manager* m1 = NewManager(0,"Joao", "mt", "Rua de Braga");
    listM = InsertManager(listM , m1);
    b = SaveManagersBinary(listM);
    b = SaveManagersTxt(listM);
    if (b == false)wprintf(L"\nErro na inserção de dados!\n");
    else{
        wprintf(L"\nSucesso!Inserção bem feita!\n");
    }
}


/**
 * @brief Função que vai testar a remoção de managers
 * 
 * @param listM
 */
void TestRemoveManager(managers* listM){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    b = RemoveManager(listM, 0);
    b = SaveManagersBinary(listM);
    b = SaveManagersTxt(listM);
    if (b == false)wprintf(L"\nErro na remoção de dados!\n");
    else{
        wprintf(L"\nSucesso!Inserção bem feita!\n");
    }
}



/**
 * @brief Função que vai testar a alteração de managers
 * 
 * @param listM
 */
void TestAlterManager(managers* listM){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    b = AlterManager(listM, 0, "Luis","Braga","mmm");
    b = SaveManagersBinary(listM);
    b = SaveManagersTxt(listM);
    if (b == false)wprintf(L"\nErro na alterção de dados!\n");
    else{
        wprintf(L"\nSucesso!Alteração bem feita!\n");
    } 
}


#pragma endregion