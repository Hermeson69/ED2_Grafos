#include <stdio.h>
#include <stdlib.h>
#include "Hanoi/Hanoi.h"
#include "Algoritmos/Algoritmos.h"
#include "Cronometro/Cronometro.h"

#define N_PINOS 3       // Número de pinos (torres) para a Torre de Hanói
#define N_DISCOS 4      // Número de discos para a Torre de Hanói
#define N_TESTES 100     // Número de testes para o desempenho
// Lembrando que o grafo começa do vertice 1, Não tem vértice 0
//  Portanto, o vértice 1 é o primeiro vértice do grafo.
//  Apenas por questões esteticas...
#define VERTICE_INICIAL 1 // Vértice inicial para os algoritmos de caminho mínimo
#define VERTICE_FINAL 27   // Vértice final para os algoritmos de caminho mínimo


short int aresta_hanoi(const CONFIGURACOES v1, const CONFIGURACOES v2)
{
    short int retorno = 1; // Assume que a aresta é válida

    int diff_count = 0;
    int disco_movido_idx = -1; // Índice do disco que mudou de pino
    int pino_origem = -1;
    int pino_destino = -1;

    // Verifica se apenas um disco se moveu
    for (int i = 0; i < N_DISCOS; ++i)
    {
        if (v1.configuracao[i] != v2.configuracao[i])
        {
            diff_count++;
            disco_movido_idx = i;
            pino_origem = v1.configuracao[i];
            pino_destino = v2.configuracao[i];
        }
    }

    if (diff_count != 1)
    {
        retorno = 0; // Mais de um disco se moveu ou nenhum disco se moveu
    }

    // Verifica se o disco movido é o disco do topo do pino de origem
    if (disco_movido_idx != disco_no_topo(v1, pino_origem, N_DISCOS))
    {
        retorno = 0; // O disco movido não era o disco do topo do pino de origem
    }

    // Verifica se o disco movido é colocado sobre um disco maior (ou pino vazio) no pino de destino
    for (int i = 0; i < N_DISCOS; ++i)
    {
        if (i != disco_movido_idx && v2.configuracao[i] == pino_destino)
        {
            // Se outro disco 'i' está no pino de destino de v2
            if (i < disco_movido_idx)
            {                // Se esse outro disco 'i' (menor índice = menor disco) é MENOR que o disco que foi movido
                retorno = 0; // Movimento inválido: disco menor sobre disco maior
            }
        }
    }

    return retorno;
}

void construir_grafo_hanoi(GRAFO *grafo, HANOI *hanoi)
{
    // Inicializa o grafo com as configurações da Torre de Hanói
    for (int i = 0; i < max_possibilidades_hanoi(hanoi->n_discos, hanoi->n_torres); i++)
    {
        for (int j = 0; j < max_possibilidades_hanoi(hanoi->n_discos, hanoi->n_torres); j++)
        {
            // Se o movimento é válido, adiciona uma aresta com peso 1
            if (aresta_hanoi(hanoi->config[i], hanoi->config[j]))
            {
                criar_aresta(grafo, i + 1, j + 1, 1); // Adiciona aresta com peso 1
            }
        }
    }
}

int main()
{
    // Iniciando a Torre de Hanói coma as especificações dadas e criando todas as configurações possíveis
    HANOI hanoi = criar_hanoi(N_DISCOS, N_PINOS);

    printf("Torre de Hanoi com %d discos e %d pinos.\nCom %d possibilidades de configuracoes.\n", hanoi.n_discos, hanoi.n_torres, max_possibilidades_hanoi(N_DISCOS, N_PINOS));

    // Inicializando o grafo com n vertices igual ao número de configurações possíveis
    // O grafo não é ponderado e nem direcionado.
    GRAFO grafo_hanoi = criar_grafo(0, 0, max_possibilidades_hanoi(N_DISCOS, N_PINOS)); // Não Ponderado, Não Direcionado

    printf("\nGrafo de Hanoi criado com %d vertices.\n\n", grafo_hanoi.n_vertices);

    // Criando as arestas do grafo de Hanoi com base nas configurações válidas
    construir_grafo_hanoi(&grafo_hanoi, &hanoi);

    // Imprimindo a matriz de adjacência do grafo de Hanoi
    imprimir_matriz_grafo(&grafo_hanoi);

    printf("\nGrafo de Hanoi construído.\n\n");

    printf("\nVertice inicial: %d\n\n", VERTICE_INICIAL);

    printf("Calculando caminho minimo usando Dijkstra...\n\n");

    VETOR_CAMINHO_MINIMO *caminho_dijkstra = dijkstra(&grafo_hanoi, VERTICE_INICIAL); // Calcula o caminho mínimo a partir do vértice 1

    if (caminho_dijkstra == NULL)
    {
        printf("Nenhum caminho encontrado.\n");
    }

    // Imprimindo o vetor de caminho mínimo encontrado por Dijkstra
    printf("\nVetor de caminho minimo encontrado por Dijkstra:\n");
    imprimir_vetor_caminho_minimo(caminho_dijkstra, grafo_hanoi.n_vertices); // Imprime o vetor de caminho mínimo encontrado por Dijkstra

    printf("\n\nCalculando caminho minimo usando Bellman-Ford...\n\n");
    int tem_ciclo_negativo = 0; // Flag para verificar se há ciclo negativo

    VETOR_CAMINHO_MINIMO *caminho_bellman_ford = bellman_ford(&grafo_hanoi, VERTICE_INICIAL, &tem_ciclo_negativo); // Calcula o caminho mínimo a partir do vértice 1

    if (caminho_bellman_ford == NULL)
    {
        printf("Nenhum caminho encontrado (Bellman-Ford).\n");
    }

    // Imprimindo o vetor de caminho mínimo encontrado por Bellman-Ford
    printf("\nVetor de caminho minimo encontrado por Bellman-Ford:\n");
    imprimir_vetor_caminho_minimo(caminho_bellman_ford, grafo_hanoi.n_vertices); // Imprime o vetor de caminho mínimo encontrado por Bellman-Ford


    printf("\n\n");
    // Imprimindo o caminho mínimo encontrado por Dijkstra
    imprimir_caminho(caminho_dijkstra, VERTICE_INICIAL, VERTICE_FINAL); // Imprime o caminho do vértice 

    printf("\n\n");
    // Imprimindo o caminho mínimo encontrado por Bellman-Ford
    imprimir_caminho(caminho_bellman_ford, VERTICE_INICIAL, VERTICE_FINAL); // Imprime o caminho do vértice


    //==============TESTES DE DESEMPENHO=========================

    printf("\n\n");
    printf("Iniciando teste de desempenho EXECUTANDO %d VEZES os algoritmos de caminho mínimo...\n", N_TESTES);

    VETOR_CAMINHO_MINIMO *caminho_teste = NULL;
    double tempo_dijkstra = 0.0;
    double tempo_bellman_ford = 0.0;

    clock_t cronometro = cronometro_iniciar(); // Inicia o cronômetro

    for (int i = 0; i < N_TESTES; i++)
    {
        caminho_teste = dijkstra(&grafo_hanoi, VERTICE_INICIAL); // Executa o algoritmo de Dijkstra
        if (caminho_teste == NULL)
        {
            printf("Nenhum caminho encontrado no teste %d.\n", i + 1);
        }
        liberar_vetor_caminho_minimo(&caminho_teste); // Libera a memória alocada pelo vetor de caminho mínimo
    }

    cronometro = cronometro_finalizar(cronometro); // Finaliza o cronômetro

    printf("Teste de desempenho de Dijkstra concluido.\n");

    tempo_dijkstra = converter_para_milisegundos(cronometro); // Converte o tempo para milissegundos

    cronometro = cronometro_iniciar(); // Reinicia o cronômetro

    for (int i = 0; i < N_TESTES; i++)
    {
        caminho_teste = bellman_ford(&grafo_hanoi, VERTICE_INICIAL, &tem_ciclo_negativo); // Executa o algoritmo de Bellman-Ford
        if (caminho_teste == NULL)
        {
            printf("Nenhum caminho encontrado no teste %d.\n", i + 1);
        }
        liberar_vetor_caminho_minimo(&caminho_teste); // Libera a memória alocada pelo vetor de caminho mínimo
    }

    cronometro = cronometro_finalizar(cronometro); // Finaliza o cronômetro

    printf("Teste de desempenho de Bellman-Ford concluido.\n\n");

    tempo_bellman_ford = converter_para_milisegundos(cronometro); // Converte o tempo para microsegundos

    printf("Resultados dos testes de desempenho:\n");
    printf("Dijkstra: %.5f ms\n", tempo_dijkstra);
    printf("Bellman-Ford: %.5f ms\n", tempo_bellman_ford);

    // Liberando a memória alocada
    liberar_grafo(&grafo_hanoi);
    liberar_hanoi(&hanoi);
    liberar_vetor_caminho_minimo(&caminho_dijkstra);
    liberar_vetor_caminho_minimo(&caminho_bellman_ford);

    return 0;
}