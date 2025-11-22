// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // tolower

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
  int soma;
  soma = x + y;
  return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ // função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a)
{
  int val;
  if (a == 2)
    val = 3;
  else
    val = 4;

  return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int datavalida = 1;

  // quebrar a string data em strings sDia, sMes, sAno
  DataQuebrada dq = quebraData(data);

  if (dq.iDia <= 0 || dq.iDia > 30)
  {
    datavalida = 0;
  }

  if (dq.iMes <= 0 || dq.iMes > 12)
  {
    datavalida = 0;
  }

  if (dq.iAno < 0)
  {
    datavalida = 0;
  }

  // ano bissexto
  int bissexto = (dq.iAno % 400 == 0 || (dq.iAno % 4 == 0 && dq.iAno % 100 != 0));

  if (dq.iMes == 2)
  {
    if (bissexto)
    {
      if (dq.iDia > 29)
        datavalida = 0;
    }
    else
    {
      if (dq.iDia > 28)
        datavalida = 0;
    }
  }

  if (datavalida)
    return 1;
  else
    return 0;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal.
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
  DiasMesesAnos dma;

  if (q1(datainicial) == 0)
  {
    dma.retorno = 2;
    return dma;
  }
  else if (q1(datafinal) == 0)
  {
    dma.retorno = 3;
    return dma;
  }
  else
  {
    DataQuebrada dq1 = quebraData(datainicial);
    DataQuebrada dq2 = quebraData(datafinal);

    if (dq2.iAno < dq1.iAno)
    {
      dma.retorno = 4;
      return dma;
    }
    else if (dq2.iMes < dq1.iMes)
    {
      dma.retorno = 4;
      return dma;
    }
    else if (dq2.iDia < dq1.iDia)
    {
      dma.retorno = 4;
      return dma;
    }

    dma.qtdAnos = dq2.iAno - dq1.iAno;
    dma.qtdMeses = dq2.iMes - dq1.iMes;
    dma.qtdDias = dq2.iDia - dq1.iDia;

    dma.retorno = 1;
    return dma;
  }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
  int qtdOcorrencias = 0;

  if (isCaseSensitive != 1)
  {
    c = tolower(c);

    for (int i = 0; texto[i] != '\0'; i++)
    {
      if (tolower(texto[i]) == c)
        qtdOcorrencias++;
    }
  }
  else
  {
    for (int i = 0; texto[i] != '\0'; i++)
    {
      if (texto[i] == c)
        qtdOcorrencias++;
    }
  }

  return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única
    ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve
    ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será
    amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra
    de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte
    forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
  int qtdOcorrencias = 0;
  int tamTexto = strlen(strTexto);
  int tamBusca = strlen(strBusca);

  for (int i = 0; i <= tamTexto - tamBusca; i++)
  {
    int encontrou = 1;
    for (int j = 0; j < tamBusca; j++)
    {
      if (strTexto[i + j] != strBusca[j])
      {
        encontrou = 0;
        break;
      }
    }

    if (encontrou)
    {
      posicoes[2 * qtdOcorrencias] = i + 1;
      posicoes[2 * qtdOcorrencias + 1] = i + tamBusca;
      qtdOcorrencias++;
    }
  }

  return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int numInvertido = 0;

  while (num > 0)
  {
    int digito = num % 10;
    numInvertido = numInvertido * 10 + digito;
    num = num / 10;
  }

  return numInvertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
  char base[20], busca[10];
  sprintf(base, "%d", numerobase);
  sprintf(busca, "%d", numerobusca);

  int qtdOcorrencias = 0;

  int tamBusca = strlen(busca);
  int tamBase = strlen(base);

  for (int i = 0; i <= tamBase - tamBusca; i++)
  {
    int j;
    for (j = 0; j < tamBusca; j++)
    {
      if (base[i + j] != busca[j])
        break;
    }
    if (j == tamBusca)
      qtdOcorrencias++;
  }

  return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

char *inverterString(char palavra[5])
{
  static char palavraInvertida[5];

  palavraInvertida[5] = '\0';

  int index = 0;
  for (int i = 4; i >= 0; i--)
  {
    palavraInvertida[index] = palavra[i];
    index++;
  }
  return palavraInvertida;
}

int q7(char matriz[8][10], char palavra[6])
{
  int achou = 0;

  char temp[6];
  // Horizontal
  for (int l = 0; l < 8; l++)
  {
    for (int times = 0; times <= 5; times++)
    {

      int idx = 0;
      for (int c = times; c < times + 5; c++)
      {
        temp[idx] = matriz[l][c];
        idx++;
      }
      temp[5] = '\0';

      char *tempI = inverterString(temp);
      if (strcmp(temp, palavra) == 0 || strcmp(tempI, palavra) == 0)
      {
        achou = 1;
        return achou;
      }
    }
  }
  // Vertical
  for (int c = 0; c < 10; c++)
  {
    for (int times = 0; times < 4; times++)
    {

      int idx = 0;
      for (int l = times; l < times + 5; l++)
      {
        temp[idx] = matriz[l][c];
        idx++;
      }
      temp[5] = '\0';

      char *tempI = inverterString(temp);
      if (strcmp(temp, palavra) == 0 || strcmp(tempI, palavra) == 0)
      {
        achou = 1;
        return achou;
      }
    }
  }

  // Diagonal esquerda -> direita
  for (int l = 0; l <= 3; l++)
  {
    for (int c = 0; c <= 5; c++)
    {
      int idx = 0;
      for (int k = 0; k < 5; k++)
      {
        temp[idx] = matriz[l + k][c + k];
        idx++;
      }
      temp[5] = '\0';

      char *tempI = inverterString(temp);
      if (strcmp(temp, palavra) == 0 || strcmp(tempI, palavra) == 0)
      {
        achou = 1;
        return achou;
      }
    }
  }

  // Diagonal direita -> esquerda
  for (int l = 0; l <= 3; l++)
  {
    for (int c = 9; c >= 4; c--)
    {
      int idx = 0;
      for (int k = 0; k < 5; k++)
      {
        temp[idx] = matriz[l + k][c - k];
        idx++;
      }
      temp[5] = '\0';

      char *tempI = inverterString(temp);
      if (strcmp(temp, palavra) == 0 || strcmp(tempI, palavra) == 0)
      {
        achou = 1;
        return achou;
      }
    }
  }

  return achou;
}

DataQuebrada quebraData(char data[])
{
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++)
  {
    sDia[i] = data[i];
  }
  if (i == 1 || i == 2)
  {                 // testa se tem 1 ou dois digitos
    sDia[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  int j = i + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++)
  {
    sMes[i] = data[j];
    i++;
  }

  if (i == 1 || i == 2)
  {                 // testa se tem 1 ou dois digitos
    sMes[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  j = j + 1; // anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '\0'; j++)
  {
    sAno[i] = data[j];
    i++;
  }

  if (i == 2 || i == 4)
  {                 // testa se tem 2 ou 4 digitos
    sAno[i] = '\0'; // coloca o barra zero no final
  }
  else
  {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}
