/**
 * \author Erick Heiler, Halena Kulmann Duarte and Eder Augusto Penharbel
 * \date March, 21, 2023.
 * \version June, 29, 2023.
 **/

#ifndef __GERENCIADOR_H__
#define __GERENCIADOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>

/* ----------STRUCTS E VARIAVEIS GLOBAIS---------- */

/* -----LISTAS----- */

typedef struct Node
{
    char status;               // L ou O / Livre ou Ocupado
    void *endereco;            // endereco onde comeca a entrada
    size_t comprimento; // comprimento da entrada
    unsigned long pos;         // pos dentro da lista prealocada
    struct ListaPreAlocada *pai;
    struct Node *next; // ponteiro para a proxima entrada
    struct Node *prev; // ponteiro para a entrada anterior
} Node;

#define NPREALOCADO 10
// #define NPREALOCADO 8
#define NBITMAP NPREALOCADO / 8

typedef struct ListaPreAlocada
{
    int livres;
    unsigned long bitmap[NBITMAP];
    Node nodes[NPREALOCADO];
    struct ListaPreAlocada *next;
} ListaPreAlocada;

/* -----MEMORIA----- */

#define MEMINFOADDR 1024 // inicio do mem info

typedef struct MemInfo
{
    long int nodesAlocados;
    Node *fim;
    long int memLivre;
    long int memTotal;
    ListaPreAlocada *lpa;
    Node *base;
} MemInfo;

/* ----------FUNCOES---------- */

/* -----MEMORIA----- */

void *criaMemoria(long tamanho);
void devolveMemoria(int *memoria);
void inicializar(long tamanho_);
void finalizar();
void debug();
void lpa_marcarUsado(void *ptr, size_t comprimento);
void lpa_devolverUsado(void *ptr);
void *kalloc(void *endereco, size_t tamanho_);
void kfree(void *ptr);

/* -----LISTAS----- */

/* listaPreAlocada, nodes */
Node *findParaAlocar(void *endereco, Node *base);
Node *findParaDesalocar(void *endereco, Node *base);
void lpa_init(ListaPreAlocada *lpa);
void lpa_memoriaLivre(ListaPreAlocada *lpa, size_t tamanho_, void *mem_base);
Node *lpa_getNode(ListaPreAlocada *lpa);
void lpa_devolverNode(Node *node);
void list_printNode(Node *n);
void lpa_printfLpa(ListaPreAlocada *lpa);
void lpa_printfLpaNode(ListaPreAlocada *lpa);

#endif