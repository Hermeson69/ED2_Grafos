#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para gerar um número aleatório entre 1 e 9
int gerarDigitoAleatorio()
{
    return rand() % 9 + 1;
}

// Função para gerar a matrícula de 6 dígitos sem o número 0
void gerarMatricula(char *matricula)
{
    for (int i = 0; i < 6; i++)
    {
        matricula[i] = (char)(gerarDigitoAleatorio() + '0'); // Converte o int para char
    }
    matricula[6] = '\0'; // Adiciona o terminador de string
}

// Funcao para gerar uma funcao aleatoria
void gerarFuncao(char *funcao)
{
    char funcoes[][30] = {"Analista", "Programador", "Gerente", "Diretor", "Contador", "Secretario", "Assistente", "Consultor", "Estagiario", "Coordenador"};

    strcpy(funcao, funcoes[rand() % 10]);
}

// Funcao para gerar um salario aleatorio
float gerarSalario()
{
    return 1000.0f + (rand() % 9000);
}

// Funcao para criar um arquivo de banco de dados com 10000 funcionarios
void criarBancoDeDados(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    int sucesso = 0;

    if (arquivo != NULL)
    {
        srand(time(NULL));

        // Array para controlar matrículas já utilizadas
        char *matriculasUsadas[10000];
        int totalMatriculas = 0;

        for (int i = 0; i < 10000; i++)
        {
            char matricula[7];
            char nome[100];
            char funcao[100];
            float salario;

            // Gera matrículas aleatórias sem repetição
            int matriculaUnica = 0;
            while (!matriculaUnica)
            {
                gerarMatricula(matricula);
                matriculaUnica = 1;

                // Verifica se a matrícula já foi usada
                for (int j = 0; j < totalMatriculas; j++)
                {
                    if (strcmp(matriculasUsadas[j], matricula) == 0)
                    {
                        matriculaUnica = 0;
                        break;
                    }
                }

                if (matriculaUnica)
                {
                    // Salva a matrícula no array de controle
                    matriculasUsadas[totalMatriculas] = strdup(matricula);
                    totalMatriculas++;
                }
            }

            sprintf(nome, "Funcionario%04d", i + 1);
            gerarFuncao(funcao);
            salario = gerarSalario();

            fprintf(arquivo, "%s;%s;%s;%.2f\n", matricula, nome, funcao, salario);
        }

        // Libera a memória alocada
        for (int i = 0; i < totalMatriculas; i++)
            free(matriculasUsadas[i]);

        fclose(arquivo);
        printf("Banco de dados criado com sucesso: %s\n", nomeArquivo);
        sucesso = 1;
    }

    if (sucesso == 0)
        printf("Erro ao criar o arquivo de banco de dados.\n");
}

int main()
{
    const char *nomeArquivo = "../funcionarios.txt";

    criarBancoDeDados(nomeArquivo);

    return 0;
}