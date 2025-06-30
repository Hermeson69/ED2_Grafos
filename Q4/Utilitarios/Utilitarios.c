#include <stdio.h>
#include <stdlib.h>
#include "Utilitarios.h"

void verificar_alocacao(void *ptr, const char *mensagem)
{
    if (!ptr)
    {
        fprintf(stderr, "Erro de alocacao: %s\n", mensagem);
        exit(EXIT_FAILURE);
    }
}

void limpar_buffer()
{
#ifdef _WIN32
    fflush(stdin); // Para Windows
#else
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Para Linux e MacOS
#endif
}

void limpar_tela()
{
#ifdef _WIN32
    system("cls"); // Para Windows
#else
    system("clear"); // Para Linux e MacOS
#endif
}

void pausar_tela()
{
#ifdef _WIN32
    system("pause"); // Para Windows
#else
    system("read -n 1 -s -p \"Pressione qualquer tecla para continuar...\""); // Para Linux e MacOS
#endif
}