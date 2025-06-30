#include <stdio.h>
#include <stdlib.h>
#include "Hash/Hash.h"
#include "BD/Coletar_dados.h"
#include "Utilitarios/Utilitarios.h"

#define TAMANHO_VETOR_1 121 // Definindo o tamanho do vetor de funcionários
#define TAMANHO_VETOR_2 180 // Definindo o tamanho do vetor de funcionários para o segundo exemplo
#define TAMANHO_BD 10000 // Definindo o tamanho do vetor de funcionários para o terceiro exemplo


void teste_funcao_hash_A()
{
    printf("Teste da função hash A\n\n");

    FUNCIONARIO *vetor = inicializar_vetor_funcionarios(TAMANHO_VETOR_1); // Inicializa o vetor de funcionários com tamanho 121

    FUNCIONARIO funcionario1 = criar_funcionario("123456", "Joao Silva", "Gerente", 5000.00);
    FUNCIONARIO funcionario2 = criar_funcionario("234567", "Maria Oliveira", "Analista", 4500.00);
    FUNCIONARIO funcionario3 = criar_funcionario("345678", "Carlos Pereira", "Desenvolvedor", 4000.00);

    //Funcionario 4 com matrícula repetida para testar colisão
    FUNCIONARIO funcionario4 = criar_funcionario("123456", "Ana Costa", "Gerente", 6000.00);
    FUNCIONARIO funcionario5 = criar_funcionario("123456", "Pedro Santos", "Analista", 4800.00);

    // Inserindo funcionários no vetor usando a função hash A
    short int resultado1 = inserir_funcionario_hash_A(vetor, TAMANHO_VETOR_1, funcionario1, NULL); // Passando NULL para o contador de colisões
    short int resultado2 = inserir_funcionario_hash_A(vetor, TAMANHO_VETOR_1, funcionario2, NULL);
    short int resultado3 = inserir_funcionario_hash_A(vetor, TAMANHO_VETOR_1, funcionario3, NULL);
    short int resultado4 = inserir_funcionario_hash_A(vetor, TAMANHO_VETOR_1, funcionario4, NULL);
    short int resultado5 = inserir_funcionario_hash_A(vetor, TAMANHO_VETOR_1, funcionario5, NULL);

    // Verificando os resultados da inserção

    if (resultado1 > 0)
    {
        printf("Funcionario 1 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 1.\n");
    }


    if (resultado2 > 0)
    {
        printf("Funcionario 2 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 2.\n");
    }


    if (resultado3 > 0)
    {
        printf("Funcionario 3 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 3.\n");
    }


    if (resultado4 > 0)
    {
        printf("Funcionario 4 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 4.\n");
    }

    if (resultado5 > 0)
    {
        printf("Funcionario 5 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 5.\n");
    }

    // Imprimindo os funcionários inseridos
    printf("\nFuncionarios inseridos:\n");
    imprimir_vetor_funcionarios(vetor, TAMANHO_VETOR_1);


    // Buscando funcionários no vetor usando a função hash A
    FUNCIONARIO *buscado1 = buscar_funcionario_hash_A(vetor, TAMANHO_VETOR_1, "123456");
    FUNCIONARIO *buscado2 = buscar_funcionario_hash_A(vetor, TAMANHO_VETOR_1, "234567");


    // Verificando os resultados da busca

    if (buscado1 != NULL)
    {
        printf("\nFuncionario buscado 1:\n");
        imprimir_funcionario(*buscado1); // Imprime os detalhes do funcionário buscado 1
    }
    else
    {
        printf("Funcionario buscado 1 não encontrado.\n");
    }

    if (buscado2 != NULL)
    {
        printf("Funcionario buscado 2:\n");
        imprimir_funcionario(*buscado2); // Imprime os detalhes do funcionário buscado 2
    }
    else
    {
        printf("Funcionario buscado 2 não encontrado.\n");
    }

    free(vetor); // Libera a memória alocada para o vetor de funcionários

    printf("\n\nTeste da função hash A concluído.\n\n");
}

void teste_funcao_hash_B()
{
    printf("Teste da função hash B\n\n");

    FUNCIONARIO *vetor = inicializar_vetor_funcionarios(TAMANHO_VETOR_1); // Inicializa o vetor de funcionários com tamanho 121

    FUNCIONARIO funcionario1 = criar_funcionario("123456", "Joao Silva", "Gerente", 5000.00);
    FUNCIONARIO funcionario2 = criar_funcionario("234567", "Maria Oliveira", "Analista", 4500.00);
    FUNCIONARIO funcionario3 = criar_funcionario("345678", "Carlos Pereira", "Desenvolvedor", 4000.00);

    //Funcionario 4 com matrícula repetida para testar colisão
    FUNCIONARIO funcionario4 = criar_funcionario("123456", "Ana Costa", "Gerente", 6000.00);
    FUNCIONARIO funcionario5 = criar_funcionario("123456", "Pedro Santos", "Analista", 4800.00);

    // Inserindo funcionários no vetor usando a função hash A
    short int resultado1 = inserir_funcionario_hash_B(vetor, TAMANHO_VETOR_1, funcionario1, NULL);
    short int resultado2 = inserir_funcionario_hash_B(vetor, TAMANHO_VETOR_1, funcionario2, NULL);
    short int resultado3 = inserir_funcionario_hash_B(vetor, TAMANHO_VETOR_1, funcionario3, NULL);
    short int resultado4 = inserir_funcionario_hash_B(vetor, TAMANHO_VETOR_1, funcionario4, NULL);
    short int resultado5 = inserir_funcionario_hash_B(vetor, TAMANHO_VETOR_1, funcionario5, NULL);

    // Verificando os resultados da inserção

    if (resultado1 > 0)
    {
        printf("Funcionario 1 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 1.\n");
    }


    if (resultado2 > 0)
    {
        printf("Funcionario 2 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 2.\n");
    }


    if (resultado3 > 0)
    {
        printf("Funcionario 3 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 3.\n");
    }


    if (resultado4 > 0)
    {
        printf("Funcionario 4 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 4.\n");
    }

    if (resultado5 > 0)
    {
        printf("Funcionario 5 inserido com sucesso\n");
    }
    else
    {
        printf("Erro ao inserir o Funcionario 5.\n");
    }

    // Imprimindo os funcionários inseridos
    printf("\nFuncionarios inseridos:\n");
    imprimir_vetor_funcionarios(vetor, TAMANHO_VETOR_1);

    // Buscando funcionários no vetor usando a função hash B
    FUNCIONARIO *buscado1 = buscar_funcionario_hash_B(vetor, TAMANHO_VETOR_1, "123456");
    FUNCIONARIO *buscado2 = buscar_funcionario_hash_B(vetor, TAMANHO_VETOR_1, "234567");

    // Verificando os resultados da busca

    if (buscado1 != NULL)
    {
        printf("\nFuncionario buscado 1:\n");
        imprimir_funcionario(*buscado1); // Imprime os detalhes do funcionário buscado 1
    }
    else
    {
        printf("Funcionario buscado 1 não encontrado.\n");
    }

    if (buscado2 != NULL)
    {
        printf("Funcionario buscado 2:\n");

        imprimir_funcionario(*buscado2); // Imprime os detalhes do funcionário buscado 2
    }
    else
    {
        printf("Funcionario buscado 2 não encontrado.\n");
    }

    free(vetor); // Libera a memória alocada para o vetor de funcionários

    printf("\n\nTeste da funcao hash B concluido.\n\n");
}


int main()
{
    // teste_funcao_hash_A(); // Chama a função de teste para a função hash A

    // teste_funcao_hash_B(); // Chama a função de teste para a função hash B

    FUNCIONARIO *BD = coletar_dados_BD_funcionario(TAMANHO_BD, TAMANHO_BD, "../BD/funcionarios.txt");

    limpar_tela(); // Limpa a tela para melhor visualização

    //==================== TABELA HASH A 1 ===================
    printf("Tabela Hash A %d posicoes\n\n", TAMANHO_VETOR_1);
    //Vetor 121
    FUNCIONARIO *vetor_A_121 = inicializar_vetor_funcionarios(TAMANHO_VETOR_1); // Inicializa o vetor de funcionários com tamanho 121
    int count_colisoes_A_121 = 0; // Variável para contar colisões

    for (int i = 0; i < TAMANHO_BD; i++)
    {
        if (BD[i].matricula[0] != '\0') // Verifica se a matrícula não está vazia
        {
            if (inserir_funcionario_hash_A(vetor_A_121, TAMANHO_VETOR_1, BD[i], &count_colisoes_A_121) > 0) // Insere o funcionário no vetor usando a função hash A
            {
                // printf("%d: Funcionario %s inserido com sucesso na tabela hash A.\n", i+1, BD[i].matricula);
            }
            else
            {
                printf("%d: Erro ao inserir o Funcionario %s na tabela hash A.\n", i+1, BD[i].matricula);
            }
        }
    }

    printf("\nFuncionarios inseridos na tabela hash A %d: Com %d colisoes\n", TAMANHO_VETOR_1, count_colisoes_A_121);
    // Imprime os funcionários inseridos na tabela hash A
    imprimir_vetor_funcionarios(vetor_A_121, TAMANHO_VETOR_1); // Imprime os funcionários inseridos na tabela hash A
    

    free(vetor_A_121); // Libera a memória alocada para o vetor de funcionários da tabela hash A

    pausar_tela(); // Pausa a tela para visualização dos resultados
    limpar_tela(); // Limpa a tela para melhor visualização


    //==================== TABELA HASH A 2 ===================


    printf("Tabela Hash A %d posicoes\n\n", TAMANHO_VETOR_2);
    //Vetor 180
    FUNCIONARIO *vetor_A_180 = inicializar_vetor_funcionarios(TAMANHO_VETOR_2); // Inicializa o vetor de funcionários com tamanho 180
    int count_colisoes_A_180 = 0; // Variável para contar colisões

    for (int i = 0; i < TAMANHO_BD; i++)
    {
        if (BD[i].matricula[0] != '\0') // Verifica se a matrícula não está vazia
        {
            if (inserir_funcionario_hash_A(vetor_A_180, TAMANHO_VETOR_2, BD[i], &count_colisoes_A_180) > 0) // Insere o funcionário no vetor usando a função hash A
            {
                // printf("%d: Funcionario %s inserido com sucesso na tabela hash A.\n", i+1, BD[i].matricula);
            }
            else
            {
                printf("%d: Erro ao inserir o Funcionario %s na tabela hash A.\n", i+1, BD[i].matricula);
            }
        }
    }

    printf("\nFuncionarios inseridos na tabela hash A %d: Com %d colisoes\n", TAMANHO_VETOR_2, count_colisoes_A_180);
    // Imprime os funcionários inseridos na tabela hash A
    imprimir_vetor_funcionarios(vetor_A_180, TAMANHO_VETOR_2); // Imprime os funcionários inseridos na tabela hash A

    free(vetor_A_180); // Libera a memória alocada para o vetor de funcionários da tabela hash A

    pausar_tela(); // Pausa a tela para visualização dos resultados
    limpar_tela(); // Limpa a tela para melhor visualização

    //==================== TABELA HASH B 1===================
    printf("Tabela Hash B %d posicoes\n\n", TAMANHO_VETOR_1);

    //Vetor 121
    FUNCIONARIO *vetor_B_121 = inicializar_vetor_funcionarios(TAMANHO_VETOR_1); // Inicializa o vetor de funcionários com tamanho 121
    int count_colisoes_B_121 = 0; // Variável para contar colis

    for (int i = 0; i < TAMANHO_BD; i++)
    {
        if (BD[i].matricula[0] != '\0') // Verifica se a matrícula não está vazia
        {
            if (inserir_funcionario_hash_B(vetor_B_121, TAMANHO_VETOR_1, BD[i], &count_colisoes_B_121) > 0) // Insere o funcionário no vetor usando a função hash B
            {
                // printf("%d: Funcionario %s inserido com sucesso na tabela hash B.\n", i+1, BD[i].matricula);
            }
            else
            {
                printf("%d: Erro ao inserir o Funcionario %s na tabela hash B.\n", i+1, BD[i].matricula);
            }
        }
    }

    printf("\nFuncionarios inseridos na tabela hash B: Com %d colisoes\n", count_colisoes_B_121);
    // Imprime os funcionários inseridos na tabela hash B
    imprimir_vetor_funcionarios(vetor_B_121, TAMANHO_VETOR_1);
    free(vetor_B_121); // Libera a memória alocada para o vetor de funcionários da tabela hash B

    pausar_tela(); // Pausa a tela para visualização dos resultados
    limpar_tela(); // Limpa a tela para melhor visualização

    //==================== TABELA HASH B 2===================
    printf("Tabela Hash B %d posicoes\n\n", TAMANHO_VETOR_2);
    //Vetor 180
    FUNCIONARIO *vetor_B_180 = inicializar_vetor_funcionarios(TAMANHO_VETOR_2); // Inicializa o vetor de funcionários com tamanho 180
    int count_colisoes_B_180 = 0; // Variável para contar colisões

    for (int i = 0; i < TAMANHO_BD; i++)
    {
        if (BD[i].matricula[0] != '\0') // Verifica se a matrícula não está vazia
        {
            if (inserir_funcionario_hash_B(vetor_B_180, TAMANHO_VETOR_2, BD[i], &count_colisoes_B_180) > 0) // Insere o funcionário no vetor usando a função hash B
            {
                // printf("%d: Funcionario %s inserido com sucesso na tabela hash B.\n", i+1, BD[i].matricula);
            }
            else
            {
                printf("%d: Erro ao inserir o Funcionario %s na tabela hash B.\n", i+1, BD[i].matricula);
            }
        }
    }

    printf("\nFuncionarios inseridos na tabela hash B %d: Com %d colisoes\n", TAMANHO_VETOR_2, count_colisoes_B_180);
    // Imprime os funcionários inseridos na tabela hash B
    imprimir_vetor_funcionarios(vetor_B_180, TAMANHO_VETOR_2); // Imprime os funcionários inseridos na tabela hash B

    free(vetor_B_180); // Libera a memória alocada para o vetor de funcionários da tabela hash B

    pausar_tela(); // Pausa a tela para visualização dos resultados
    limpar_tela(); // Limpa a tela para melhor visualização

    free(BD); // Libera a memória alocada para o vetor de funcionários coletados do banco de dados


    printf("\nFuncionarios inseridos na tabela hash A %d: Com %d colisoes\n", TAMANHO_VETOR_1,count_colisoes_A_121);
    printf("\nFuncionarios inseridos na tabela hash A %d: Com %d colisoes\n", TAMANHO_VETOR_2,count_colisoes_A_180);
    printf("\nFuncionarios inseridos na tabela hash B %d: Com %d colisoes\n", TAMANHO_VETOR_1,count_colisoes_B_121);
    printf("\nFuncionarios inseridos na tabela hash B %d: Com %d colisoes\n", TAMANHO_VETOR_2,count_colisoes_B_180);
    printf("\n\nFim do programa.\n\n");

    return 0;
}