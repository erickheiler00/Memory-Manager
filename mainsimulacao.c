/**
* \author Erick Heiler, Halena Kulmann Duarte and Eder Augusto Penharbel
* \date March, 21, 2023.
* \version June, 29, 2023.
**/

#include "gerenciador.h"

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>


/* -----VARIAVEIS GLOBAIS----- */

//#define TAMANHO_MEMORIA 512 * 1024 * 1024
#define TAMANHO_MEMORIA 1 << 30


/* -----VARIAVEIS EXTERNAS----- */

extern void *memBase;
extern MemInfo *memInfo;


/* -----DEFINICOES----- */

int main()
{
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Define o ambiente local para português do Brasil com UTF-8

    inicializar(TAMANHO_MEMORIA);

    /* Testes */

    int loop = 1; // numero de processos que serao criados
    int NALOCACOES = 10;
    int NDESALOCACOES = 5;

    void* allocatedAddresses[NALOCACOES];  // array para armazenar os endereços alocados
    void *bla;

    srand(time(NULL));
    
    pid_t pid; // Variável que armazena o ID do processo

    // Loop para criar vários processos
    for (int processos = 0; processos < loop; processos++)
    {
        //printf("\nProcesso %i\n", processos);
        pid = fork(); // Cria um novo processo

        if (pid < 0)
        {
            perror("Erro ao criar o processo");
            exit(EXIT_FAILURE);
        }
        else if (!pid)
        {
            // Processo filho

            // Simulação de operações de alocação/desalocação de memória no processo filho
            int i;

            for (i = 0; i < NALOCACOES; i++)
            {
                void* endereco = (void*)(uintptr_t)(rand() % 1073741824);
                //printf("%p: ", endereco);
                int comprimento = rand() % 100000;
                bla = kalloc(memBase + (uintptr_t)endereco, comprimento);
                allocatedAddresses[i] = bla;
            }

            for (i = 0; i < NDESALOCACOES; i++) {

                //int index = rand() % NALOCACOES; // escolhe um indice aleatório = endereco aleatório dos já alocados
                int index = i;
                
                //while(int index = rand() % i){
                if (allocatedAddresses[index] != NULL)
                {
                    kfree(allocatedAddresses[index]);  // libera o endereço
                    allocatedAddresses[index] = NULL; // libera no array
                }
                

                /*

                int index;

                do {
                    index = rand() % NALOCACOES; // escolhe um índice aleatório = endereço aleatório dos já alocados
                } while (allocatedAddresses[index] == NULL);

                kfree(allocatedAddresses[index]);  // libera o endereço
                allocatedAddresses[index] = NULL; // libera no array
                */
            }
                //int index = rand() % NALOCACOES; // escolhe um indice aleatório = endereco aleatório dos já alocados
                //int index = 0;
                /*
                while(int index = rand() % i){
                if (allocatedAddresses[index] != NULL)
                {
                    kfree(allocatedAddresses[index]);  // libera o endereço
                    allocatedAddresses[index] = NULL; // libera no array
                }
                
        }}*/
        
        

            lpa_printfLpa(memInfo->lpa);

            //exit(EXIT_SUCCESS); 
        }
        else
        {
            // Processo pai

            // Esperando o processo filho terminar:
            waitpid(pid, NULL, 0);
        }
    }

    /*
    int l, i;
    for(l = 0; l < loop; l++)
    {
        for(i = 0; i < NALOCACOES; i++)
        {
            void* endereco = (void*)(uintptr_t)(rand() % 1073741824);
            printf("%p: ", endereco);
            int comprimento = rand() % 100000;
            bla = kalloc(memBase + (uintptr_t)endereco, comprimento);
            allocatedAddresses[i] = endereco;
        }

        for (i = 0; i < NDESALOCACOES; i++) {
            int index = rand() % NALOCACOES;  // escolhe um indice aleatório = endereco aleatório dos já alocados
            if (allocatedAddresses[index] != NULL) {
                kfree(allocatedAddresses[index]);  // libera o endereço
                allocatedAddresses[index] = NULL;  // libera no array
            }
        }
    }
    */

    //void *bla1 = kalloc(memBase + 4096, 2048);
    /*void *bla2 = kalloc(memBase + 6146, 2048);
    void *bla3 = kalloc(memBase + 8296, 2048);
    void *bla4 = kalloc(memBase + 12000, 2048);
    void *bla5 = kalloc(memBase + 17900, 2048);
    void *bla6 = kalloc(memBase + 26130, 2048);
    void *bla7 = kalloc(memBase + 14500, 2048);
    void *bla8 = kalloc(memBase + 20000, 2048);
    void *bla9 = kalloc(memBase + 23100, 2048);
    void *bla10 = kalloc(memBase + 30000, 2048);
    void *bla11 = kalloc(memBase + 33000, 2048);
    void *bla12 = kalloc(memBase + 37000, 2048);
    void *bla13 = kalloc(memBase + 40000, 2048);*/

    //kfree(memBase + 4096);
    /*kfree(memBase + 14500);
    kfree(memBase + 8296);*/

    /*void *bla14 = kalloc(memBase + 30000, 2048);
    void *bla15 = kalloc(memBase + 33000, 2048);
    void *bla16 = kalloc(memBase + 37000, 2048);
    void *bla17 = kalloc(memBase + 40000, 2048);
    void *bla18 = kalloc(memBase + 8296, 2048);*/

    //lpa_printfLpa(memInfo->lpa);

    finalizar();

    return 0;
}