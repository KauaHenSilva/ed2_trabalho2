#include "Unity/unity.h"
#include "include/tratamento_de_arquivo.h"
#include "include/arvore_2_3.h"
#include <stdio.h>
#include <stdlib.h>

Arvore_2_3 *raiz;

void setUp()
{
  raiz = NULL;
}
void tearDown()
{
  free_arvore_2_3(raiz);
}

void test_ler_indentificar_linha_caso_1();
void test_ler_indentificar_linha_caso_2();
void test_prencher_arvore_por_linha();
void test_ler_blocos();
void test_ler_blocos_2();

int main()
{
  UNITY_BEGIN();
  RUN_TEST(test_ler_indentificar_linha_caso_1);
  RUN_TEST(test_ler_indentificar_linha_caso_2);
  RUN_TEST(test_prencher_arvore_por_linha);
  RUN_TEST(test_ler_blocos);
  return UNITY_END();
}

void test_ler_indentificar_linha_caso_1()
{
  char linha[] = "% Unidade 2";
  TipoEntrada tipo = ler_indentificar_linha(linha);
  TEST_ASSERT_EQUAL_INT(NOME_UNIDADE, tipo);
}

void test_ler_indentificar_linha_caso_2()
{
  char linha[] = "Bus: onibus, barramento;";
  TipoEntrada tipo = ler_indentificar_linha(linha);
  TEST_ASSERT_EQUAL_INT(PALAVRA_INGLES_PORTUGUES, tipo);
}

void test_prencher_arvore_por_linha()
{
  char linha[] = "Bus: onibus, barramento;";

  int resultado = prencher_arvore_por_linha(&raiz, linha, "Unidade 1");
  TEST_ASSERT_EQUAL_INT(1, resultado);
  TEST_ASSERT_NOT_NULL(raiz);

  TEST_ASSERT_EQUAL_STRING("Bus", raiz->info1.arv_binaria_palavra_ingles->info.palavra_ingles);
  TEST_ASSERT_EQUAL_STRING("barramento", raiz->info1.palavra_portugues);

  TEST_ASSERT_EQUAL_STRING("Bus", raiz->info2.arv_binaria_palavra_ingles->info.palavra_ingles);
  TEST_ASSERT_EQUAL_STRING("onibus", raiz->info2.palavra_portugues);

  TEST_ASSERT_EQUAL_STRING("Unidade 1", raiz->info1.arv_binaria_palavra_ingles->info.unidades->nome_unidade);
  TEST_ASSERT_EQUAL_STRING("Unidade 1", raiz->info2.arv_binaria_palavra_ingles->info.unidades->nome_unidade);

  TEST_ASSERT_NULL(raiz->centro);
  TEST_ASSERT_NULL(raiz->direita);
  TEST_ASSERT_NULL(raiz->esquerda);
}

void test_ler_blocos()
{
  FILE *fp = freopen("output/test_ler_blocos.txt", "w", stdout);
  int resultado = ler_blocos(&raiz);
  show_arvore_2_3(raiz);
  fclose(fp);
  freopen("/dev/tty", "w", stdout);

  TEST_ASSERT_EQUAL_INT(1, resultado);

  FILE *fp2 = fopen("output/test_ler_blocos.txt", "r");
  char buffer[1024];
  char *experado[] = {
    "Palavra em portugues: barramento\n",
    "Possivel traducao em ingles: Bus\n",
    "Apareceu em: Unidade 1\n",
    "Palavra em portugues: bicicleta\n",
    "Possivel traducao em ingles: Bicycle\n",
    "Apareceu em: Unidade 2\n",
    "Possivel traducao em ingles: Bike\n",
    "Apareceu em: Unidade 1\n",
    "Palavra em portugues: inseto\n",
    "Possivel traducao em ingles: Bug\n",
    "Apareceu em: Unidade 2, Unidade 1\n",
    "Palavra em portugues: onibus\n",
    "Possivel traducao em ingles: Bus\n",
    "Apareceu em: Unidade 1\n",
    "Palavra em portugues: problema\n",
    "Possivel traducao em ingles: Bug\n",
    "Apareceu em: Unidade 1\n",
    "Palavra em portugues: rede de computadores\n",
    "Possivel traducao em ingles: Network\n",
    "Apareceu em: Unidade 1\n",
    "Palavra em portugues: rede de relacionamento\n",
    "Possivel traducao em ingles: Network\n",
    "Apareceu em: Unidade 2\n",
    "Palavra em portugues: sistema\n",
    "Possivel traducao em ingles: System\n",
    "Apareceu em: Unidade 1\n",
    "Palavra em portugues: ventilador\n",
    "Possivel traducao em ingles: Coller\n",
    "Apareceu em: Unidade 1\n",
    "Possivel traducao em ingles: Fan\n",
    "Apareceu em: Unidade 2\n"
  };

  for (int i = 0; i < 31; i++)
    TEST_ASSERT_EQUAL_STRING(experado[i], fgets(buffer, 1024, fp2));
}
