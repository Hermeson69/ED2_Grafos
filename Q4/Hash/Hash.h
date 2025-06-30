#include "../Funcionario/Funcionario.h"


#pragma once

short int inserir_funcionario_hash_A(FUNCIONARIO *vetor, int tamanho, FUNCIONARIO inserir, int *colisoes);

FUNCIONARIO *buscar_funcionario_hash_A(FUNCIONARIO *vetor, int tamanho, const char *matricula);

short int inserir_funcionario_hash_B(FUNCIONARIO *vetor, int tamanho, FUNCIONARIO inserir, int *colisoes);

FUNCIONARIO *buscar_funcionario_hash_B(FUNCIONARIO *vetor, int tamanho, const char *matricula);
