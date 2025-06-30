#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Hash.h"

void rotacao_esquerda(char *str)
{
    int tamanho = strlen(str); // Obtém o tamanho da string

    if (tamanho > 1)
    {
        char primeiro = str[0]; // Salva o primeiro caractere

        // Move todos os caracteres para a esquerda
        for (int i = 0; i < tamanho - 1; i++)
        {
            str[i] = str[i + 1];
        }

        str[tamanho - 1] = primeiro; // Coloca o primeiro caractere no final
    }
}

// Conta a partir de 1
char extrair_caractere(const char *str, int posicao)
{
    int tamanho = strlen(str);
    if (posicao < 1 || posicao > tamanho)
    {
        return '\0'; // Retorna nulo se a posição for inválida
    }

    return str[posicao - 1];
}

int resto_divisao(int a, int b)
{
    if (b == 0)
    {
        fprintf(stderr, "Erro: Divisão por zero.\n");
        exit(EXIT_FAILURE);
    }
    return a % b;
}

// Esse fold shift é especifico para a questão 4 letra B do trabalho de ED2
void fold_shift(const char *entrada, char *saida)
{
    // Extração dos caracteres

    char conjunto1[3] = {0};
    char conjunto2[3] = {0};
    char conjunto3[3] = {0};

    // Extração dos caracteres de acordo com a posição
    conjunto1[0] = extrair_caractere(entrada, 1);
    conjunto1[1] = extrair_caractere(entrada, 2);
    conjunto1[2] = '\0'; // Null terminator

    conjunto2[0] = extrair_caractere(entrada, 6);
    conjunto2[1] = extrair_caractere(entrada, 3);
    conjunto2[2] = '\0'; // Null terminator

    conjunto3[0] = extrair_caractere(entrada, 4);
    conjunto3[1] = extrair_caractere(entrada, 5);
    conjunto3[2] = '\0'; // Null terminator

    // Conversão para inteiros e soma dos valores

    int valor1 = atoi(conjunto1);
    int valor2 = atoi(conjunto2);
    int valor3 = atoi(conjunto3);

    int soma = valor1 + valor2 + valor3;

    // Retirar primeiro digito caso ultrupassar 3 digitos

    if (soma > 999)
    {
        // Remove o primeiro dígito
        int primeiro_digito = soma / 1000;
        soma -= primeiro_digito * 1000;
    }

    // Conversão da soma para string
    sprintf(saida, "%d", soma);
    saida[3] = '\0'; // Garantir que a string esteja terminada
}

// Trata colisão somando dígito da matrícula ao resultado

int tratar_colisao(int resultado, int digito)
{
    // Verifica se o digito é 0, casos seja, soma ao menos 1 para evitar colisão infinita
    if (digito == 0)
    {
        digito = 1; // Se o dígito for 0, substitui por 1 para evitar colisão infinita
    }

    return resultado + digito; // Soma o dígito ao resultado
}

//================ FUNÇÕES HASH A==========

int funcao_hash_A(const char *matricula, int tamanho)
{
    char matricula_aux[7];
    strncpy(matricula_aux, matricula, sizeof(matricula_aux) - 1);
    matricula_aux[sizeof(matricula_aux) - 1] = '\0'; // Garantir que a string esteja terminada

    // Rotação duas vezes para a esquerda
    rotacao_esquerda(matricula_aux); // Rotaciona a matrícula para a esquerda
    rotacao_esquerda(matricula_aux); // Rotaciona novamente para a esquerda

    char numeros_extraidos[4] = {0};

    numeros_extraidos[0] = extrair_caractere(matricula_aux, 2);
    numeros_extraidos[1] = extrair_caractere(matricula_aux, 4);
    numeros_extraidos[2] = extrair_caractere(matricula_aux, 5);
    numeros_extraidos[3] = '\0'; // Null terminator

    int resultado = atoi(numeros_extraidos); // Converte os caracteres extraídos para inteiro

    resultado = resto_divisao(resultado, tamanho); // Calcula o resto da divisão pelo tamanho do vetor

    return resultado; // Retorna o resultado da função hash
}

short int inserir_funcionario_hash_A(FUNCIONARIO *vetor, int tamanho, FUNCIONARIO inserir, int *colisoes)
{
    short int retorno = 0; // Variavel para indicar sucesso ou falha na inserção

    int resultado = funcao_hash_A(inserir.matricula, tamanho); // Calcula o resultado da função hash

    // Verifica se a matricula é igual
    if (strcmp(vetor[resultado].matricula, inserir.matricula) != 0)
    {

        short int valido = 1; // Variável para verificar se o loop é válido
        short int loop = 0;
        short int loop_maximo = 0;          // Variável para controlar o loop
        int resultado_original = resultado; // Armazena o resultado original para verificar colisões

        // Extrai o primeiro dígito da matrícula para tratar colisões
        char digito = extrair_caractere(inserir.matricula, 1);
        int primeiro_digito = atoi(&digito); // Extrai o primeiro dígito da matrícula

        if (primeiro_digito == 0) // Se o primeiro dígito for 0, substitui por 1 para evitar colisão infinita
        {
            primeiro_digito = 1;
        }

        // Define o loop máximo com base no tamanho do vetor e no primeiro dígito
        if (tamanho % primeiro_digito == 0) // Se o tamanho for divisível pelo primeiro dígito
        {
            // Se o digito for divisível pelo tamanho
            loop_maximo = 2;
        }
        else if (((primeiro_digito % 2 == 0 && tamanho % 2 == 0) || (primeiro_digito % 2 != 0 && tamanho % 2 != 0)))
        {
            // Se o digito não for divisível pelo tamanho e ambos forem pares ou ímpares
            loop_maximo = 3;
        }
        else
        {
            // Se o digito não for divisível pelo tamanho e ambos forem diferentes
            loop_maximo = primeiro_digito;
        }

        while (valido)
        {
            //Faz loop ate o fim do vetor ou ate o a posição original ser atingida novamente
            if (resultado >= tamanho || (resultado == resultado_original && loop + 1 >= loop_maximo)) // Verifica se o resultado é maior ou igual ao tamanho do vetor
            {
                resultado = resto_divisao(resultado, tamanho); // Redefine o resultado para o resto da divisão pelo tamanho do vetor
                loop++;                                        // Aumenta o contador de loops

                if (loop >= loop_maximo) // Se ja tiver feito um loop entra aqui
                {
                    valido = 0;

                    // Não tinha posições livres, então insere na posição original, mesmo que tenha colidido
                    vetor[resultado_original] = inserir; // Insere o funcionário na posição original
                    retorno = 2;                         // Retorno 2 indica que não havia posições livres e foi inserido na posição original
                }
            }
            else
            {
                // Verifica se a matricula é igual
                if (strcmp(vetor[resultado].matricula, inserir.matricula) == 0)
                {
                    valido = 0; // Define como inválido para sair do loop
                }
                else if (vetor[resultado].matricula[0] == '\0') // Verifica se a posição está livre
                {
                    vetor[resultado] = inserir; // Insere o funcionário na posição livre
                    valido = 0;                 // Define como inválido para sair do loop
                    retorno = 1;
                }
                else
                {
                    if (colisoes != NULL) // Verifica se o ponteiro de colisões não é nulo
                    {
                        *colisoes = (*colisoes) + 1; // Incrementa o contador de colisões
                    }

                    resultado = tratar_colisao(resultado, primeiro_digito); // Trata colisão somando o primeiro dígito da matrícula
                }
            }
        }
    }

    // if (colisoes != NULL) // Verifica se o ponteiro de colisões não é nulo
    // {
    //    printf("Colisoes: %d\n", *colisoes); // Imprime o número de colisões
    // }

    return retorno; // Retorna a posição onde o funcionário foi inserido
}

FUNCIONARIO *buscar_funcionario_hash_A(FUNCIONARIO *vetor, int tamanho, const char *matricula)
{
    FUNCIONARIO *funcionario = NULL;

    int resultado = funcao_hash_A(matricula, tamanho); // Calcula o resultado da função hash

    short int nao_achado = 1; // Variável para verificar se o loop é válido
    short int loop = 0;
    short int loop_maximo = 0;          // Variável para controlar o loop
    int resultado_original = resultado; // Armazena o resultado original para verificar colisões

    // Extrai o primeiro dígito da matrícula para tratar colisões
    char digito = extrair_caractere(matricula, 1);
    int primeiro_digito = atoi(&digito); // Extrai o primeiro dígito da matrícula

    if (primeiro_digito == 0) // Se o primeiro dígito for 0, substitui por 1 para evitar colisão infinita
    {
        primeiro_digito = 1;
    }

    // Define o loop máximo com base no tamanho do vetor e no primeiro dígito
    if (tamanho % primeiro_digito == 0) // Se o tamanho for divisível pelo primeiro dígito
    {
        // Se o digito for divisível pelo tamanho
        loop_maximo = 2;
    }
    else if (((primeiro_digito % 2 == 0 && tamanho % 2 == 0) || (primeiro_digito % 2 != 0 && tamanho % 2 != 0)))
    {
        // Se o digito não for divisível pelo tamanho e ambos forem pares ou ímpares
        loop_maximo = 3;
    }
    else
    {
        // Se o digito não for divisível pelo tamanho e ambos forem diferentes
        loop_maximo = primeiro_digito;
    }

    while (nao_achado)
    {
        if (resultado >= tamanho) // Verifica se o resultado é maior ou igual ao tamanho do vetor
        {
            resultado = resto_divisao(resultado, tamanho); // Redefine o resultado para o resto da divisão pelo tamanho do vetor

            loop++; // Aumenta o numero de loops feitos

            if (loop >= loop_maximo) // Se ja tiver feito um loop entra aqui
            {
                nao_achado = 0;
            }
        }
        else
        {
            // Verifica se a matricula é igual
            if (strcmp(vetor[resultado].matricula, matricula) == 0)
            {
                nao_achado = 0;                  // Define para sair do loop
                funcionario = &vetor[resultado]; // Atribui o endereço do funcionário encontrado
            }
            else
            {

                resultado = tratar_colisao(resultado, primeiro_digito); // Trata colisão somando o primeiro dígito da matrícula
            }
        }
    }

    return funcionario; // Retorna o funcionário encontrado ou NULL se não encontrado
}

//================ FUNÇÕES HASH B==========

int funcao_hash_B(const char *matricula, int tamanho)
{
    char matricula_aux[7];
    strncpy(matricula_aux, matricula, sizeof(matricula_aux) - 1);
    matricula_aux[sizeof(matricula_aux) - 1] = '\0'; // Garantir que a string esteja terminada

    char saida[3] = {0}; // Array para armazenar o resultado do fold shift

    fold_shift(matricula_aux, saida); // Aplica o fold shift na matrícula

    int resultado = atoi(saida); // Converte o resultado do fold shift para inteiro

    resultado = resto_divisao(resultado, tamanho); // Calcula o resto da divisão pelo tamanho do vetor

    return resultado; // Retorna o resultado da função hash
}

short int inserir_funcionario_hash_B(FUNCIONARIO *vetor, int tamanho, FUNCIONARIO inserir, int *colisoes)
{
    short int retorno = 0; // Variavel para indicar sucesso ou falha na inserção

    int resultado = funcao_hash_B(inserir.matricula, tamanho); // Calcula o resultado da função hash

    // Verifica se a matricula é igual
    if (strcmp(vetor[resultado].matricula, inserir.matricula) != 0)
    {

        short int valido = 1;               // Variável para verificar se o loop é válido
        short int loop = 0;                 // Variável para controlar o loop
        short int loop_maximo = 0;          // Variável para controlar o loop
        short int ultimo_caso = 0; // Variável para controlar o último caso de colisão
        int resultado_original = resultado; // Armazena o resultado original para verificar colisões

        // Extrai os dígitos da matrícula para tratar colisões
        char digitos[3] = {0};                                // Array para armazenar os dígitos da matrícula
        digitos[0] = extrair_caractere(inserir.matricula, 1); // Extrai o primeiro dígito da matrícula
        digitos[1] = extrair_caractere(inserir.matricula, 6); // Extrai o segundo dígito da matrícula
        digitos[2] = '\0';

        // Verifica se os dígitos extraídos são válidos
        int digito_tratamento = atoi(digitos); // Converte os dígitos extraídos para inteiro

        if (digito_tratamento == 0) // Se o dígito for 0, substitui por 1 para evitar colisão infinita
        {
            digito_tratamento = 1;
        }

        // Define o loop máximo com base no tamanho do vetor e no dígito de tratamento
        if (tamanho % digito_tratamento == 0) // Se o tamanho for divisível pelo primeiro dígito
        {
            // Se o digito for divisível pelo tamanho
            loop_maximo = 2;
        }
        else if (((digito_tratamento % 2 == 0 && tamanho % 2 == 0) || (digito_tratamento % 2 != 0 && tamanho % 2 != 0)))
        {
            // Se o digito não for divisível pelo tamanho e ambos forem pares ou ímpares
            loop_maximo = 3;
        }
        else
        {
            // Se o digito não for divisível pelo tamanho e ambos forem diferentes
            loop_maximo = digito_tratamento;
            
        }

        while (valido)
        {
            if (resultado >= tamanho || (resultado == resultado_original && loop + 1 >= loop_maximo)) // Verifica se o resultado é maior ou igual ao tamanho do vetor
            {
                resultado = resto_divisao(resultado, tamanho); // Redefine o resultado para o resto da divisão pelo tamanho do vetor

                loop++;                  // Define que já foi feita uma iteração
                if (loop >= loop_maximo) // Se ja tiver feito um loop entra aqui
                {
                    valido = 0;

                    // Não tinha posições livres, então insere na posição original, mesmo que tenha colidido
                    vetor[resultado_original] = inserir; // Insere o funcionário na posição original
                    retorno = 2;                         // Retorno 2 indica que não havia posições livres e foi inserido na posição original
                }
            }
            else
            {
                // Verifica se a matricula é igual
                if (strcmp(vetor[resultado].matricula, inserir.matricula) == 0)
                {
                    valido = 0; // Define como inválido para sair do loop
                }
                else if (vetor[resultado].matricula[0] == '\0') // Verifica se a posição está livre
                {
                    vetor[resultado] = inserir; // Insere o funcionário na posição livre
                    valido = 0;                 // Define como inválido para sair do loop
                    retorno = 1;
                }
                else
                {
                    if (colisoes != NULL) // Verifica se o ponteiro de colisões não é nulo
                    {
                        *colisoes = (*colisoes) + 1; // Incrementa o contador de colisões
                    }

                    resultado = tratar_colisao(resultado, atoi(digitos)); // Trata colisão somando o primeiro dígito da matrícula
                }
            }
        }
    }

    return retorno; // Retorna a posição onde o funcionário foi inserido
}

FUNCIONARIO *buscar_funcionario_hash_B(FUNCIONARIO *vetor, int tamanho, const char *matricula)
{
    FUNCIONARIO *funcionario = NULL;

    int resultado = funcao_hash_B(matricula, tamanho); // Calcula o resultado da função hash

    short int nao_achado = 1;  // Variável para verificar se a posição está livre
    short int loop = 0;        // Variável para controlar o loop
    short int loop_maximo = 0; // Variável para controlar o loop
    int resultado_original = resultado; // Armazena o resultado original para verificar colisões
    
    // Extrai os dígitos da matrícula para tratar colisões
    char digitos[3] = {0};                                // Array para armazenar os dígitos da matrícula
    digitos[0] = extrair_caractere(matricula, 1); // Extrai o primeiro dígito da matrícula
    digitos[1] = extrair_caractere(matricula, 6); // Extrai o segundo dígito da matrícula
    digitos[2] = '\0';

    // Verifica se os dígitos extraídos são válidos
    int digito_tratamento = atoi(digitos); // Converte os dígitos extraídos para inteiro

    if (digito_tratamento == 0) // Se o dígito for 0, substitui por 1 para evitar colisão infinita
    {
        digito_tratamento = 1;
    }

    // Define o loop máximo com base no tamanho do vetor e no dígito de tratamento
    if (tamanho % digito_tratamento == 0) // Se o tamanho for divisível pelo primeiro dígito
    {
        // Se o digito for divisível pelo tamanho
        loop_maximo = 2;
    }
    else if (((digito_tratamento % 2 == 0 && tamanho % 2 == 0) || (digito_tratamento % 2 != 0 && tamanho % 2 != 0)))
    {
        // Se o digito não for divisível pelo tamanho e ambos forem pares ou ímpares
        loop_maximo = 3;
    }
    else
    {
        // Se o digito não for divisível pelo tamanho e ambos forem diferentes
        loop_maximo = digito_tratamento;
    }

    while (nao_achado)
    {
        if (resultado >= tamanho || (resultado == resultado_original && loop + 1 >= loop_maximo)) // Verifica se o resultado é maior ou igual ao tamanho do vetor
        {
            resultado = resto_divisao(resultado, tamanho); // Redefine o resultado para o resto da divisão pelo tamanho do vetor
            loop++;                                        // Define que já foi feita uma iteração

            if (loop >= loop_maximo) // Se ja tiver feito um loop entra aqui
            {
                nao_achado = 0; // Define que não foi encontrado
            }
        }
        else
        {
            // Verifica se a matricula é igual
            if (strcmp(vetor[resultado].matricula, matricula) == 0)
            {
                nao_achado = 0;                  // Define para sair do loop
                funcionario = &vetor[resultado]; // Atribui o endereço do funcionário encontrado
            }
            else
            {

                resultado = tratar_colisao(resultado, digito_tratamento); // Trata colisão somando o primeiro dígito da matrícula
            }
        }
    }

    return funcionario; // Retorna o funcionário encontrado ou NULL se não encontrado
}