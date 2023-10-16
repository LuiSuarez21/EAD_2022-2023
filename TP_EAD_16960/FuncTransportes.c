/**
 * @file FuncTransportes.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Ficheiro que trata de lidar com os dados dos Transportes
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
#include "HeaderTransportes.h"



#pragma region CRUD dos Transportes

/**
 * @brief Adiciona um novo elemento a lista
 * 
 * @param ct 
 * @return transports* 
 */
transports* NewNodsTransports(transport* ct)
{
    transports* new_transport = (transports*)malloc(sizeof(transports));
    strcpy(new_transport->t.typeT, ct->typeT);
    strcpy(new_transport->t.location, ct->location);
    strcpy(new_transport->t.available , ct->available);
    new_transport->t.battery = ct->battery;
    new_transport->t.autonomy = ct->autonomy;
    new_transport->t.price = ct->price;
    new_transport->t.id = ct->id;
	new_transport->t.x = ct->x;
	new_transport->t.y = ct->y;
    new_transport->next = NULL;
    return new_transport;
}


/**
 * @brief Cria um novo transporte
 * 
 * @param idT
 * @param type 
 * @param locationT 
 * @param availableT 
 * @param batteryT 
 * @param autonomyT 
 * @param priceT 
 * @param x 
 * @param y 
 * @return transport* 
 */
transport* NewTransport(int idT, char* type, char* locationT, char* availableT, int batteryT, int autonomyT, int priceT, int x, int y)
{
    transport* new_transport = (transport*)malloc(sizeof(transport));
    strcpy(new_transport->typeT, type);
    strcpy(new_transport->location, locationT);
    strcpy(new_transport->available , availableT);
    new_transport->battery = batteryT;
    new_transport->autonomy = autonomyT;
    new_transport->price = priceT;
    new_transport->id = idT;
	new_transport->x = x;
	new_transport->y = y;
    return new_transport;
}


/**
 * @brief Insere um novo elemento na lista, neste caso, um transporte
 * 
 * @param cs 
 * @param ct 
 * @return transports* 
 */
transports* InsertTransport(transports* cs, transport* ct)
{
    transports* verify = cs;
    //se p for null retorna a lista original sem fazer nenhuma alteração
    if (ct == NULL)
    {
        return cs;
    }

    while (verify != NULL)
    {
        if (verify->t.id == ct->id)
        {
            return cs;  // Retorna a lista original sem adicionar o novo transporte
        }
        verify = verify->next;
    }


    transports* new = NewNodsTransports(ct);
    if(cs == NULL)
    {
        cs = new;
    } 
    else
    {
        transports* actual = cs;
        while (actual->next != NULL)
        {
            actual = actual->next;
        }
        
        actual->next = new;
    }
    return cs;
}


/**
 * @brief Remove um transporte da lista
 * 
 * @param cs 
 * @param id 
 * @return true 
 * @return false 
 */
bool RemoveTransport(transports* cs, int id) {

    transports* temporario = cs;
    transports* anterior = cs;
    transports* atual = cs;

    //Se não existir retorna false
    if(cs == NULL)
    {
        return false;
    }

    //Se existir no primeiro nodo, apaga o transporte e retorna true
    if(cs->t.id == id)
    {
        cs = cs->next;
        free(temporario);
        SaveTransportsTxt2(cs, id);
        SaveTransportsBinary2(cs, id);
        return true;
    }
    //Percorre a lista ate encontrar o transporte com o id igual, elimina e retorna true
    while(atual != NULL)
    {
        if(atual->t.id == id)
        {
            anterior->next = atual->next;
            free(atual);
            SaveTransportsTxt2(cs, id);
            SaveTransportsBinary2(cs, id);
            return true;
        }
        anterior = atual;
        atual = atual->next;
    }


    //Se não encontrar retorna false
    return false;
    
}


/**
 * @brief Altera a informação de um transporte
 * 
 * @param c 
 * @param idC 
 * @param type 
 * @param locationT 
 * @param availableT 
 * @param batteryT 
 * @param autonomyT 
 * @param priceT 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool AlterTransport(transports* c, int idC, char* type, char* locationT, char* availableT, int batteryT, int autonomyT, int priceT, int x, int y) {

    transports* temporario = c;

    //Se não existir retorna false
    if(c == NULL)
    {
        return false;
    }

    while(temporario !=NULL)
    {
        if(temporario->t.id == idC)
        {
             
            strcpy(temporario->t.typeT, type);
            strcpy(temporario->t.location, locationT);
            strcpy(temporario->t.available , availableT);
            temporario->t.battery = batteryT;
            temporario->t.autonomy = autonomyT;
            temporario->t.price = priceT;
            temporario->t.id = idC;
	        temporario->t.x = x;
	        temporario->t.y = y;
            SaveTransportsTxt(temporario);
            SaveTransportsBinary(temporario);
            return true;
        }
        temporario = temporario->next;

    }

    return false;

}

#pragma endregion


#pragma region Manipulação de ficheiros


/**
 * @brief Guarda os dados em txt
 * 
 * @param cs 
 * @return true 
 * @return false 
 */
bool SaveTransportsTxt(transports* cs)
{
    FILE* file = fopen("DadosTransportes.txt", "w");
    if(file == NULL)
    {
        return false;
    }

    transports* new = cs;
    while(new != NULL)
    {
        fprintf(file,"%d;%s;%s;%s;%d;%d;%d;%d;%d;\n", new->t.id, new->t.typeT, new->t.location, new->t.available, new->t.battery, new->t.autonomy, new->t.price, new->t.x, new->t.y);
        new = new->next;
    }

    fclose(file);

    return true;
}


/**
 * @brief Guarda os dados em txt
 * 
 * @param cs 
 * @param id
 * @return true 
 * @return false 
 */
bool SaveTransportsTxt2(transports* cs, int id)
{
    FILE* file = fopen("DadosTransportes.txt", "w");
    if(file == NULL)
    {
        return false;
    }

    transports* new = cs;
    while(new != NULL && id != cs->t.id)
    {
        fprintf(file,"%d;%s;%s;%s;%d;%d;%d;%d;%d;\n", new->t.id, new->t.typeT, new->t.location, new->t.available, new->t.battery, new->t.autonomy, new->t.price, new->t.x, new->t.y);
        new = new->next;
    }

    fclose(file);

    return true;
}



/**
 * @brief Guarda os dados em binário
 * 
 * @param cs 
 * @return true 
 * @return false 
 */
bool SaveTransportsBinary(transports* cs)
{
    FILE* file = fopen("DadosTransportesBinario.txt", "wb");
    if(file == NULL)
    {
        return false;
    }

    transports* atual = cs;
    while(atual != NULL)
    {
        fwrite(&atual->t, sizeof(transports), 1, file);
        atual = atual->next;
    }

    fclose(file);

    return true;
}


/**
 * @brief Guarda os dados em binário
 * 
 * @param cs 
 * @param id
 * @return true 
 * @return false 
 */
bool SaveTransportsBinary2(transports* cs, int id)
{
    FILE* file = fopen("DadosTransportesBinario.txt", "wb");
    if(file == NULL)
    {
        return false;
    }

    transports* atual = cs;
    while(atual != NULL && id != cs->t.id)
    {
        fwrite(&atual->t, sizeof(transports), 1, file);
        atual = atual->next;
    }

    fclose(file);

    return true;
}


/**
 * @brief Le os dados dos transportes
 * 
 * @return transports* 
 */
transports* ReadFileTransport(transports* newTransport){

   FILE* file = fopen("DadosTransportes.txt", "r");
   if (file == NULL) 
   {
        return NULL;
   }

   transport t;

   while (fscanf(file, "%d;%[^;];%[^;];%[^;];%d;%d;%d;%d;%d;", &t.id, t.typeT, t.location, t.available, &t.battery, &t.autonomy, &t.price, &t.x, &t.y) == 9)
   {
        transport *t1 = NewTransport(t.id, t.typeT, t.location, t.available, t.battery, t.autonomy, t.price, t.x, t.y);
        newTransport = InsertTransport(newTransport, t1);
   }

   fclose(file);
   return newTransport;
}


#pragma endregion


#pragma region Listagem de informação


/**
 * @brief Lista os transportes com uma determinada localização
 * 
 * @param listT 
 * @param newLocation 
 */
bool ListMobilitiesGeo (transports* t, char* newLocation){
    transports* new;
    FILE* fp;
    fp=fopen("TransportesOrdenadosGeoCode.txt", "w");

    if(fp==NULL){
        printf("\nErro ao abrir o ficheiro!");
        return false;
    }
    else{
        while(new != NULL)
    {
        if(strcmp(new->t.location, newLocation) == 0){
        fprintf(fp,"\n-------------------------------\n");
        fprintf(fp,"Transport ID: %d\n", new->t.id);
        fprintf(fp,"Transport type: %s\n", new->t.typeT);
        fprintf(fp,"Battery level: %d\n", new->t.battery);
        fprintf(fp,"Price: %d\n", new->t.price);
        fprintf(fp,"Autonomy: %d\n", new->t.autonomy);
        fprintf(fp,"Available: %d\n", new->t.available);
        fprintf(fp,"Location: %s\n", new->t.location);
        }
        new = new->next;
    }

    }
    fclose(fp);
    return true;
}


/**
 * @brief Organiza as mobilidades em ordem descendente
 * 
 * @param m 
 * @return true 
 * @return false 
 */
bool OrgDesc(transports* m)
{
    transports* atual = m;
    transports* prox = NULL;
    transports temporario;
    bool b = true;

    if(m == NULL)
    {
        return false;
    }

    while(atual != NULL)
    {
        prox = atual->next;
        while(prox != NULL)
        {
            if(atual->t.autonomy < prox->t.autonomy)
            {
                temporario.t = atual->t;
                atual->t = prox->t;
                prox->t = temporario.t;
            }
            prox = prox->next;
        }
        atual = atual->next;
    }

    b = SaveTransportsTxt(m);
    b = SaveTransportsBinary(m);
    return b;
}


#pragma endregion


#pragma region Automizar os métodos


/**
 * @brief Método que vai testar a adição de transportes
 * 
 * @param listT 
 */
void TestAddTransport(transports* listT){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
	transport* m2 = NewTransport(0, "trotinete", "Braga", "True", 48, 9, 15, 2, 1);
	transport* m3 = NewTransport(1,  "carro", "Porto", "True", 50, 9, 15, 5, 3);
	transport* m4 = NewTransport(2,  "trotinete", "Braga", "True", 56, 45, 40, 6, 4);
	transport* m5 = NewTransport(3,  "trotinete", "Braga", "True", 45, 45, 23, 10, 12);
	transport* m6 = NewTransport(4,  "trotinete", "Braga", "True", 46, 123, 13, 14, 15);
	transport* m7 = NewTransport(5,  "trotinete", "Braga", "True", 42, 435, 13, 4, 43);
    listT = InsertTransport(listT, m2);
    listT = InsertTransport(listT, m3);
    listT = InsertTransport(listT, m4);
    listT = InsertTransport(listT, m5);
    listT = InsertTransport(listT, m6);
    listT = InsertTransport(listT, m7);
    b = SaveTransportsBinary(listT);
    b = SaveTransportsTxt(listT);
    if (b == false)wprintf(L"\nErro na inserção de dados!\n");
    else{
        wprintf(L"\nSucesso!Inserção bem feita!\n");
    }
}


/**
 * @brief Método que vai testar a remoção de transportes
 * 
 * @param listT 
 */
void TestRemoveTransport(transports* listT){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    b = RemoveTransport(listT, 0);
    b = SaveTransportsBinary(listT);
    b = SaveTransportsTxt(listT);
    if (b == false)wprintf(L"\nErro na remoção de dados!\n");
    else{
        wprintf(L"\nSucesso!Inserção bem feita!\n");
    }
}


/**
 * @brief Métpdo que vai testar a alteração
 * 
 * @param listT 
 */
void TestAlterTransport(transports* listT){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
    b = AlterTransport(listT, 1,"trotinete","Braga","true",21,21,21,4,3);
    b = SaveTransportsBinary(listT);
    b = SaveTransportsTxt(listT);
    if (b == false)wprintf(L"\nErro na alterção de dados!\n");
    else{
        wprintf(L"\nSucesso!Alteração bem feita!\n");
    } 
}


/**
 * @brief Método que vai listar
 * 
 * @param listT 
 */
void TestListMobilitiesGeo(transports* listT){

	bool b = true;
    setlocale(LC_ALL, "Portuguese");
    if (listT == NULL){
        wprintf(L"Erro!!! Lista de transportes vazia!!!");
    }
	b = ListMobilitiesGeo(listT,"Braga");
    if (b == false)wprintf(L"\nErro na listagem dos dados!\n");
    else{
            wprintf(L"\nSucesso!Listagem bem feita!\n");
    }
}


/**
 * @brief Método que vai organizar
 * 
 * @param listT 
 */
void TestOrg(transports* listT){

    bool b = true;
    setlocale(LC_ALL, "Portuguese");
	b = OrgDesc(listT);
    b = SaveTransportsBinary(listT);
    b = SaveTransportsTxt(listT);
    if (b == false)wprintf(L"\nErro na listagem dos dados!\n");
    else{
            wprintf(L"\nSucesso!Listagem bem feita!\n");
    }
}

#pragma endregion