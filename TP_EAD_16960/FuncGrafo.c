/**
 * @file FuncGrafos.c
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief Ficheiro que trata de manipular dados dos Grafos
 * @version Trabalho prático EDA Fase 2 (LESI-PL)
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HeaderGrafo.h"


#pragma region Manipulação de vértices


Vertice* CriaVerticeClientes(Vertice* v, clients* c) 
{
    clients* cN = c;
	if (cN == NULL){
		printf("\nErro!!! Lista de clientes Vazia!!!\n");
		return v;
	}
    while (cN != NULL) {
        Vertice* novoVertice = CriaVertice(cN->c.userName, cN->c.nif);

        if (novoVertice != NULL) {
            v = InsereVertice(v, novoVertice);
        }

        cN = cN->next;
    }

    return v;
}


Vertice* CriaVerticeMobilidades(Vertice* v, transports* m) 
{
    transports* mN = m;

    while (mN != NULL) {
        Vertice* novoVertice = CriaVertice(mN->t.typeT, mN->t.id);

        if (novoVertice != NULL) {
            v = InsereVertice(v, novoVertice);
        }

        mN = mN->next;
    }

    return v;
}


/**
 * @brief Cria v�rtice para o grafo
 *
 * @param cidade	//!< nome da Cidade do V�rtice
 * @return
 * @author lufer
 */
Vertice* CriaVertice(char* nome, int cod) {
	Vertice* novo = (Vertice*)calloc(1, sizeof(Vertice));
	if (novo == NULL) return NULL;
	novo->cod = cod;
	strcpy(novo->nome, nome);
	novo->next = NULL;			
	novo->adjacentes = NULL;	
	return novo;
}

/**
 * @brief Inserir Vertice no grafo.
 *
 * @param g		Grafo
 * @param novo	Novo Vertice
 * @return		Grafo alterado
 * @author lufer
 *
 */
Vertice* InsereVertice(Vertice* g, Vertice* novo) {
	if (g == NULL) {
		g = novo;
		return g;
	}
	else
	{
		Vertice* aux = g;
		Vertice* ant = aux;
		while (aux && strcmp(aux->nome, novo->nome) < 0) {
			ant = aux;
			aux = aux->next;
		}
		if (aux == g) {
			novo->next = g;
			g = novo;
		}
		else
		{
			novo->next = aux;
			ant->next = novo;
		}
	}
	return g;
}


/// @brief Verifica qual o c�digo do vertice de uma determinada cidade
/// @param g 
/// @param cidade 
/// @return 
int ProcuraCodigoVertice(Vertice* g, char* nome) {
	if (g == NULL) return -1;
	if (strcmp(g->nome, nome) > 0) return -2;
	if (strcmp(g->nome, nome) == 0) return g->cod;
	return(ProcuraCodigoVertice(g->next, nome));
}

/**
 * @brief .
 *
 * @param g
 * @param cidade
 * @return
 * @author lufer
 *
 */
Vertice* ProcuraVertice(Vertice* g, char* nome) {
	if (g == NULL) return NULL;
	if (strcmp(g->nome, nome) == 0) return g;
	return(ProcuraVertice(g->next, nome));
}

Vertice* ProcuraVerticeCod(Vertice* g, int cod) {
	if (g == NULL) return NULL;
	if (g->cod == cod) return g;
	return(ProcuraVerticeCod(g->next, cod));
}

#pragma endregion


#pragma region Controlo de Adjacencias


Vertice* CriaAdjacenciasClientesMobilidades(Vertice* v, clients*c, transports* m)
{
	clients* novoC = c;
	transports* novoM = m;

    while (novoC != NULL)
    {
		novoM = m;
        while (novoM != NULL)
        {
            float weight = sqrt((novoC->c.x - novoM->t.x) * (novoC->c.x - novoM->t.x) + (novoC->c.y - novoM->t.y) * (novoC->c.y - novoM->t.y));
            v = InsereAdjacenteVerticeCod(v, novoC->c.nif, novoM->t.id, weight);
            novoM = novoM->next;
        }
        novoC = novoC->next;
    }

	return v;
}


Vertice* CriaAdjacenciasMobilidades(Vertice* v, transports* m)
{
	transports* mb = m;
	transports* mba = m;

    while (mb != NULL)
    {
        mba = m;
        while (mba != NULL)
        {
			if(mb->t.id != mba->t.id)
			{
				float weight = sqrt((mb->t.x - mba->t.x) * (mb->t.x - mba->t.x) + (mb->t.y - mba->t.y) * (mb->t.y - mba->t.y));
            	v = InsereAdjacenteVerticeCod(v, mb->t.id, mba->t.id, weight);
			}
			else
			{
				//nao faz nada
			}
            
            mba = mba->next;
        }
        mb = mb->next;
    }
	return v;
}


/**
 * @brief Cria novo nodo de adjec�ncia.
 *
 * @param cod
 * @param peso
 * @return
 * @author lufer
 *
 */
Adj* CriaAdj(int cod, float peso) {
	Adj* novo = (Adj*)calloc(1, sizeof(Adj));
	if (novo == NULL) return NULL;
	novo->cod = cod;
	novo->dist = peso;
	novo->next = NULL;
	return novo;
}

/**
 * @brief Insere nova adjec�ncia no grafo.
 *
 * @param g			Grafo orientado
 * @param origem	Nome de Vertice origem
 * @param tot		Total de v�rtices
 * @param dest		Nome de Vertice destino
 * @param peso		Peso
 * @return			Grafo alterado
 * @author lufer
 *
 */
Vertice* InsereAdjacenteVertice(Vertice* g, char* origem, char* dest, float peso)
{
#pragma region Valida��es

	if (g == NULL) return g;	//<! se grafo est� vazio, ignora opera��o

	Vertice* aux = ProcuraVertice(g, origem);	//<! procura vertice origem
	int cod = ProcuraCodigoVertice(g, dest);	//<! procura vertice destino
	//ou
	//Vertice* d = ProcuraVertice(g, dest);

	if (aux == NULL || cod < 0) return g;			//<! Se n�o encontrou vertice origem e destino, ignora opera��o

	if (ExisteAdjacentes(aux->adjacentes, cod) == true)
		return g; //Se j� foi registado esta adjacencia, ignorar a opera��o
#pragma endregion

#pragma region A��o
	//Insere nova adjacencia no vertice "Origem"
	Adj* novoAdj = CriaAdj(cod, peso);
	aux->adjacentes = InsereAdj(aux->adjacentes, novoAdj);
	return g;
	//Se for n�o orientado
	//return (InsereAdjacenteVertice(g, dest, origem, peso));
#pragma endregion

}


/**
 * @brief Insere Adjacente a partir dos c�digos dos vertices.
 *
 * @param g
 * @param codOrigem
 * @param codDest
 * @param peso
 * @return
 * @author lufer
 *
 */
Vertice* InsereAdjacenteVerticeCod(Vertice* g, int codOrigem, int codDest, float peso) {

#pragma region Valida��es

	if (g == NULL) return g;	//<! se grafo est� vazio, ignora opera��o

	Vertice* o = ProcuraVerticeCod(g, codOrigem);	//<! procura vertice origem
	Vertice* d = ProcuraVerticeCod(g, codDest);	//<! procura vertice destino
	if (o == NULL || d == NULL) return g;		//<! Se n�o encontrou vertice origem e destino, ignora opera��o

	if (ExisteAdjacentes(o->adjacentes, codDest) == true)
		return g; //Se j� foi registado esta adjacencia, ignorar a opera��o
#pragma endregion

#pragma region A��o
	//Insere nova adjacencia no vertice "Origem"
	Adj* novoAdj = CriaAdj(codDest, peso);
	o->adjacentes = InsereAdj(o->adjacentes, novoAdj);
	return g;
	//Se for n�o orientado
	//return (InsereAdjacenteVertice(g, dest, origem, peso));
#pragma endregion

}

#pragma region GERE_LISTA_ADJACENCIAS

/**
 * @brief	Verifica se determinado adj j� existe.
 *			Forma Recursiva
 *
 * @param h		Lista de Adjacencias
 * @param cod	C�digo a procurar
 * @return		Verdadeiro ou Falso
 * @author lufer
 *
 */
bool ExisteAdjacentes(Adj* h, int cod) {
	if (h == NULL) return false;
	if (h->cod == cod) return true;
	return ExisteAdjacentes(h->next, cod);
}

/**
 * @brief	Insere novo adjacente de um vertice.
 *			N�o admite vertices repetidos
 *
 * @param h
 * @param novo
 * @return
 * @author lufer
 *
 */
Adj* InsereAdj(Adj* h, Adj* novo) {
	if (novo == NULL)	//Se novo adjacente � nulo, ignora opera��o
		return h;

	if (ExisteAdjacentes(h, novo->cod) == true) return h; // Se novo adj existe, ignorar opera��o

	// Inserir nova adjacencia!
	if (h == NULL) {	//Se lista de adjacencias � vazia, esta � a primeira adjacencia
		h = novo;
		return h;
	}
	//sen�o insere no in�cio das adjac�ncias! Podia ser de outra forma!
	novo->next = h;
	h = novo;

	return h;
}

/**
 * @brief Mostra lista de adjacentes.
 *
 * @param h
 * @author lufer
 *
 */
void MostraAdjacencias(Adj* h) {
	if (h == NULL) return;
	printf("\tAdj: %d - (%.0f)\n", h->cod, h->dist);
	MostraAdjacencias(h->next);
}

/**
 * @brief .
 *
 * @param h
 * @return
 * @author lufer
 *
 */
Adj* DestroyAdj(Adj* h) {
	if (h == NULL) return NULL;
	Adj* aux = NULL;
	while (h) {
		if (h->next != NULL)
			aux = h->next;
		free(h);
		h = aux;
		aux = NULL;
	}
	return h;
}
#pragma endregion

#pragma endregion


#pragma region Algoritmos


/**
 * @brief .
 *
 * @param g
 * @return
 * @author lufer
 *
 */
Vertice* DestroyGraph(Vertice* g) {
	if (g == NULL) return NULL;
	Vertice* aux = NULL;
	while (g) {
		if (g->next)
			aux = g->next;
		g->adjacentes = DestroyAdj(g->adjacentes);
		free(g);
		g = aux;
		aux = NULL;
	}
	return g;
}

/**
 * @brief Apresenta grafo.
 *
 * @param g
 * @author lufer
 *
 */
void MostraGrafo(Vertice* g) {
	if (g == NULL) return;
	printf("V: %d - %s\n", g->cod, g->nome);
	MostraAdjacencias(g->adjacentes);
	MostraGrafo(g->next);
}


bool PrintMobilitiesWithinWeight(Vertice* v, clients* c, transports* m, int id, char mobilityType[N], float weight) 
{
    clients* cN = c;
	transports* mN = m;

	if(v == NULL)
	{
		return false;
	}
    
    // Find the client with the given ID
    while (cN != NULL) {
        if (cN->c.id == id) 
		{
            printf("ID: %d\t\t", id);
			printf("Nome: %s\t\t", cN->c.userName);
			printf("Type: %s\t\t", mobilityType);
			printf("Weight: %.2f\n", weight);
			printf("------------------------\n");
			break;
        }
        cN = cN->next;
    }

	while (v->adjacentes != NULL)
	{
		if(v->adjacentes->dist <= weight && strcmp(mN->t.typeT, mobilityType) == 0)
		{
			printf("\tAdj: %d - (%.0f)\n", v->adjacentes->cod, v->adjacentes->dist);
		}

		v->adjacentes = v->adjacentes->next;
	}

	return true;
}



/**
 * @brief Count all the paths between two vertices, recursively
 *
 * @param src
 * @param dst
 * @param vertice	- Grafo pesado, orientado
 * @return
 * @author lufer
 *
 */
int CountPaths(Vertice *g, int src, int dst, int pathCount) {
	if (g == NULL) return 0;

	// If current vertex is same as destination, then increment count
	if (src == dst) return (++pathCount);

	else { // Recur for all the vertices adjacent to this vertex
		Vertice *aux = ProcuraVerticeCod(g, src);
		Adj* hAdj = aux->adjacentes;
		while (hAdj) {
			Vertice* v = ProcuraVerticeCod(g, hAdj->cod);
			pathCount = CountPaths(g, v->cod, dst, pathCount);
			hAdj = hAdj->next;
		}
	}
	return pathCount;
}

/**
 * @brief	Count all the paths between two vertices, recursively.
 *			Using verticrs names
 *
 * @param g
 * @param src
 * @param dest
 * @param pathCount
 * @return
 * @author lufer
 *
 */
int CountPathsVerticesName(Vertice* g, char* src, char* dest, int pathCount) {
	int s = ProcuraCodigoVertice(g, src);
	int d = ProcuraCodigoVertice(g, dest);
	return CountPaths(g, s, d, 0);
}

/**
 * @brief	DFT Search Recursivo.
 *			Verifica se existe caminho entre dois vertices
 * @param g
 * @param origem
 * @param dest
 * @return
 * @author lufer
 *
 */
bool DepthFirstSearchRec(Vertice*g, int origem, int dest)
{

	if (origem == dest) return true;

	Vertice* aux = ProcuraVerticeCod(g, origem);
	aux->visitado = true;
	//printf(" Vertice: %s : %d\n", aux->cidade, aux->cod);

	Adj* adj = aux->adjacentes;
	while (adj) {
		Vertice*  aux = ProcuraVerticeCod(g, adj->cod);
		if (aux->visitado == false)
		{
			bool existe = DepthFirstSearchRec(g, adj->cod, dest);
			return existe;
		}
		else
			aux = aux->next;
	}
	return true;
}

/**
 * @brief	DFT Search Recursivo.
 *			Verifica se existe caminho entre dois vertices a partir dos seus nomes.
 *
 * @param g
 * @param src
 * @param dest
 * @return
 * @author lufer
 *
 */
bool DepthFirstSearchNamesRec(Vertice* g, char* src, char* dest) {
	int o = ProcuraCodigoVertice(g, src);
	int d = ProcuraCodigoVertice(g, dest);
	return DepthFirstSearchRec(g, o, d);
}

/**
 * @brief Limpa estado "visitado".
 *
 * @param g
 * @return
 * @author lufer
 *
 */
Vertice *ResetVerticesVisitados(Vertice* g) {
	Vertice* aux = g;
	while (aux) {
		aux->visitado = false;
		aux = aux->next;
	}
	return g;
}

#pragma endregion


#pragma region Manipulação de ficheiros

/**
 * @brief Grava Grafo em ficheiro bin�rio.
 *
 * @param h
 * @param fileName
 * @return
 * @author lufer
 *
 */
int SaveGraph(Vertice* h, char* fileName) {
	if (h == NULL) return -1;
	FILE* fp;
	int r;

	fp = fopen(fileName, "wb");
	if (fp == NULL) return -2;
	Vertice* aux = h;
	VerticeFile auxFicheiro;
	while (aux != NULL) {
		auxFicheiro.cod = aux->cod;
		strcpy(auxFicheiro.nome, aux->nome);
		fwrite(&auxFicheiro, 1, sizeof(VerticeFile), fp);
		//Pode gravar de imediato as adjacencias!
		if (aux->adjacentes) {
			r = SaveAdj(aux->adjacentes, aux->nome, aux->cod);
			//if (r <0) break;
		}
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}

/**
 * @brief Gravar Adj em ficheiro bin�rio.
 *
 * @param h
 * @param fileName
 * @return
 * @author lufer
 *
 */
int SaveAdj(Adj* h, char* fileName, int codVerticeOrigem) {
	FILE* fp;
	if (h == NULL) return -2;
	fp = fopen(fileName, "ab");
	if (fp == NULL) return -1;
	Adj* aux = h;
	AdjFile auxFile;
	while (aux) {
		auxFile.codDestino = aux->cod;
		auxFile.codOrigem = codVerticeOrigem;
		auxFile.weight = aux->dist;
		fwrite(&auxFile, 1, sizeof(AdjFile), fp);
		aux = aux->next;
	}
	fclose(fp);
	return 1;
}

/**
 * @brief Load de grafo de ficheiro.
 *
 * @param h
 * @param fileName
 * @return
 * @author lufer
 *
 */
Vertice* LoadGraph(Vertice* h, char* fileName) {
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) return NULL;
	VerticeFile aux;
	Vertice* novo;
	while (fread(&aux, 1, sizeof(VerticeFile), fp)) {
		novo = CriaVertice(aux.nome, aux.cod);
		h = InsereVertice(h, novo);
	}
	fclose(fp);
	return h;
}

/**
 * @brief Load de Adjacencias de um Grafo.
 *
 * @param g
 * @param fileName
 * @return
 * @author lufer
 *
 */
Vertice* LoadAdj(Vertice* g) {
	FILE* fp;

	AdjFile aux;
	Vertice* auxGraph = g;
	while (auxGraph) {
		fp = fopen(auxGraph->nome, "rb");
		if (fp != NULL) {
			while (fread(&aux, 1, sizeof(AdjFile), fp)) {
				g = InsereAdjacenteVerticeCod(g, aux.codOrigem, aux.codDestino, aux.weight);
			}
			fclose(fp);
		}
		auxGraph = auxGraph->next;
	}
	return g;
}

#pragma endregion



#pragma region Automatizar os métodos

/**
 * @brief Método que vai testar as operações com grafos
 * 
 * @param listT 
 */
void TestOpGrafos(transports* listT, clients* listC, Vertice* listV){

    listV = CriaVerticeClientes(listV, listC);
	listV = CriaVerticeMobilidades(listV, listT);
    listV = CriaAdjacenciasClientesMobilidades(listV, listC, listT);
	listV = CriaAdjacenciasMobilidades(listV, listT);
	int res1 = SaveGraph(listV, "Vertices.bin");
    MostraGrafo(listV);
    if (res1 > 0) puts("\nGrafo gravado em ficheiro");
    listV = DestroyGraph(listV);
	puts("\nGrafo em memoria:");
	listV = LoadGraph(listV, "Vertices.bin");
	if (listV != NULL) puts("\nVertices do Grafo lido de ficheiro\n");
    puts("\nLer Adjacencias do grafo de ficheiro\n");
	listV = LoadAdj(listV);
	MostraGrafo(listV);
	PrintMobilitiesWithinWeight(listV, listC, listT, 999999999, "bicicleta", 30);
}

#pragma endregion