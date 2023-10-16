/**
 * @file HeaderGrafo.h
 * @author José Luis Cunha Esteves (a16960@alunos.ipca.pt)
 * @brief  Este ficheiro serve para declarar as funções que controlam os grafos;
 * @version Trabalho prático EDA Fase 2
 * @date 2023-06-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include "HeaderClientes.h"
#include "HeaderTransportes.h"
#define N 50
#pragma warning (disable: 4996)


#pragma region Structs das Adjacencias


/**
 * @brief Struct que define uma adjacencia
 * 
 */
typedef struct Adj {
	int cod;		
	float dist;		
	struct Adj *next;
}Adj;


/**
 * @brief Struct que define uma adjacencia no ficheiro
 * 
 */
typedef struct AdjFile {
	int codOrigem;
	int codDestino;		
	float weight;		
}AdjFile;


#pragma endregion

#pragma region Structs dos vertices


/**
 * @brief Struct que define um vertice do grafo
 * 
 */
typedef struct Vertice {
	int cod;					
	char nome[N];				
	bool visitado;
	struct Vertice* next;		
	struct Adj* adjacentes;		
} Vertice;


/**
 * @brief Struct que define um vértice no grafo e vai ser guardado no ficheiro
 * 
 */
typedef struct VerticeFile {
	int cod;					
	char nome[N];
} VerticeFile;

#pragma endregion

#pragma region GRAFO

Vertice* InsereVertice(Vertice* g, Vertice* novo);
Vertice* CriaVertice(char* nome, int tot);
void MostraGrafo(Vertice* g);
int ProcuraCodigoVertice(Vertice* g, char* nome);
Vertice* ProcuraVertice(Vertice* g, char* nome);
Vertice* ProcuraVerticeCod(Vertice* g, int cod);
Vertice* DestroyGraph(Vertice* g);


#pragma endregion

Vertice* CriaVerticeClientes(Vertice* v, clients* c);
Vertice* CriaVerticeMobilidades(Vertice* v, transports* m);
Vertice* CriaAdjacenciasClientesMobilidades(Vertice* v, clients*c, transports* m);
Vertice* CriaAdjacenciasMobilidades(Vertice* v, transports* m);
bool PrintMobilitiesWithinWeight(Vertice* v, clients* c, transports* m, int id, char mobilityType[N], float weight);

#pragma region ADJACENCIAS

Vertice* InsereAdjacenteVertice(Vertice* g, char* origem, char* dest, float peso);
Vertice* InsereAdjacenteVerticeCod(Vertice* g, int origem, int dest, float peso);

#pragma region LISTA_ADJACENCIAS

Adj* CriaAdj(int cod, float peso);
Adj* InsereAdj(Adj* h, Adj* novo);
bool ExisteAdjacentes(Adj* h, int cod);
void MostraAdjacencias(Adj* h);
Adj* DestroyAdj(Adj* h);

#pragma endregion

#pragma endregion

#pragma region ALGORITMOS

int CountPaths(Vertice* g, int src, int dst, int pathCount);
int CountPathsVerticesName(Vertice* g, char* src, char* dest, int pathCount);

bool DepthFirstSearchRec(Vertice* g, int origem, int dest);
bool DepthFirstSearchNamesRec(Vertice* g, char* src, char* dest);

Vertice* ResetVerticesVisitados(Vertice* g);

#pragma endregion

#pragma region PRESERVA��O

int SaveGraph(Vertice* h, char* fileName);
int SaveAdj(Adj* h, char* fileName, int cod);
Vertice* LoadGraph(Vertice* h, char* fileName);
Vertice* LoadAdj(Vertice* g);


#pragma endregion


#pragma region Automatizar os métodos

void TestOpGrafos(transports* listT, clients* listC, Vertice* listV);

#pragma endregion