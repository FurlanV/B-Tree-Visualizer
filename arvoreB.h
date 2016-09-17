/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arvoreB.h
 * Author: Vinicius Furlan
 *
 * Created on June 21, 2016, 4:23 AM
 */

#ifndef __ARVOREB__
#define __ARVOREB__


#define M 2
#define MM  (M * 2)
#define FALSE 0
#define TRUE  1

typedef long TipoChave;
typedef struct TipoRegistro {
  int Chave;
  /*outros componentes*/
} TipoRegistro;
typedef struct TipoPagina* TipoApontador;
typedef struct TipoPagina {
  int n;//quantidade de itens
  TipoRegistro r[MM];//vetor de itens
  TipoApontador p[MM + 1];//vetor de ponteiro
} TipoPagina;

FILE *arqDot;

#endif