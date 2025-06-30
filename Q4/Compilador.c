#include <stdio.h>
#include <stdlib.h>

int main()
{

    int system_result = system("gcc -o Main  ../Main.c ../Funcionario/Funcionario.c ../Hash/Hash.c ../BD/Coletar_dados.c ../Utilitarios/Utilitarios.c ");

    if (system_result == 0)
    {
        #ifdef _WIN32
            system("Main");
        #else
            system("./Main.exe");
        #endif
    }

    return 0;
}