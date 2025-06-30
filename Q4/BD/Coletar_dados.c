#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Coletar_dados.h"

FUNCIONARIO *coletar_dados_BD_funcionario(int tamanho_vetor, int tamanho_BD, const char *nome_arquivo)
{
    FUNCIONARIO *vetor = inicializar_vetor_funcionarios(tamanho_vetor); // Inicializa o vetor de funcionários

    FILE *arquivo = fopen(nome_arquivo, "r"); // Abre o arquivo de funcionários para leitura
    if (arquivo != NULL)
    {

        for (int i = 0; i < tamanho_BD; i++)
        {

            char linha[256]; // Buffer para ler cada linha do arquivo
            if (fgets(linha, sizeof(linha), arquivo) == NULL)
            {
                fprintf(stderr, "Erro ao ler a linha do arquivo.\n");
                break;
            }

            char matricula[7];
            char nome[100];
            char funcao[100];
            float salario;

            // Lê os dados do funcionário a partir da linha
            if (sscanf(linha, "%6[^;];%49[^;];%29[^;];%f", matricula, nome, funcao, &salario) != 4)
            {
                fprintf(stderr, "Erro ao dividir a linha do arquivo.\n");
                break;
            }

            vetor[i] = criar_funcionario(matricula, nome, funcao, salario);
        }

        fclose(arquivo); // Fecha o arquivo
    }
    else
    {
        fprintf(stderr, "Erro ao abrir o arquivo de funcionários.\n");
        exit(EXIT_FAILURE); // Encerra o programa se não conseguir abrir o arquivo
    }

    return vetor; // Retorna o vetor de funcionários preenchido
}
    