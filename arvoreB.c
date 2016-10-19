/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arvoreB.c
 * Author: Vinicius Furlan
 *
 * Created on June 26, 2016, 4:49 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include "arvoreB.h"
#include "Widgets-GTK.h"

int Pesquisa(TipoRegistro *x, TipoApontador Ap)
{
    long i = 1;
    if (Ap == NULL)
    {
        //printf("TipoRegistro nao esta presente na arvore\n");
        return 0;
    }
    while (i < Ap->n && x->Chave > Ap->r[i-1].Chave) 
        i++;
    
    if (x->Chave == Ap->r[i-1].Chave)
    {
        *x = Ap->r[i-1];
        return 1;
    }
    if (x->Chave < Ap->r[i-1].Chave)
        return Pesquisa(x, Ap->p[i-1]);
    else 
        return Pesquisa(x, Ap->p[i]);
}

void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir)
{
    short NaoAchouPosicao;
    int k;
    k = Ap->n;//quantidade de itens n. k é a quantidade de itens na pagina
    NaoAchouPosicao = (k > 0);//0 ou 1
    while (NaoAchouPosicao)
    {
        if (Reg.Chave >= Ap->r[k-1].Chave)
        {
            NaoAchouPosicao = FALSE;
            break;
        }
        Ap->r[k] = Ap->r[k-1];
        Ap->p[k+1] = Ap->p[k];
        k--;
        if (k < 1) NaoAchouPosicao = FALSE;
    }
    Ap->r[k] = Reg;//vetor de registros foi atualizado com novo valor.
    Ap->p[k+1] = ApDir;//ApDir é do parametro ApRetorno
    Ap->n++;// mais um item incluido na pagina.
}

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno)
{
    //*Ap é a pagina raiz
    long i = 1;
    long j;
    TipoApontador ApTemp;
    if (Ap == NULL)//Nova página criada ->árvore cresce
    {
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }
    while (i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)  i++;//percorre no vetor de registros e verifica a possibilidade de inserir
    if (Reg.Chave == Ap->r[i-1].Chave)//percorrendo o vetor de registros, r[i-1] contem o item a ser inserido
    {
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }
    if (Reg.Chave < Ap->r[i-1].Chave) i--;//Localiza a página filha adequada para a inserção
    //encontrou no vetor de Reg um valor menor, ou chegou no final deles.
    Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
    if (!*Cresceu) return;//se a arvore não cresceu, retorna.....
    if (Ap->n < MM)  //Pagina tem espaco
    {
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = FALSE;//como teve espaço na pagina, não foi necessario o crescimento da arvore
        return;
    }
    //Overflow: Pagina tem que ser dividida
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    if (i < M + 1)
    {
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    }
    else InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    for (j = M + 2; j <= MM; j++)
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M];
    *ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap)
{
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);//chama "Ins" para inserir e verificar caso cresceu na altura (variavel Cresceu)
    if (Cresceu)//Arvore cresce na altura pela raiz
    {
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->n = 1;//quantidde de itens
        ApTemp->r[0] = RegRetorno;//vetor de registros; Nova página criada torna-se filha à direita
        ApTemp->p[1] = ApRetorno;//vetor de ponteiros
        ApTemp->p[0] = *Ap;//vetor de ponteiros;Antiga página raiz torna-se filha à esquerda
        *Ap = ApTemp;//Nova página raiz
    }
}
void ImprimeI(TipoApontador p, int nivel,Widgets *widget)
{
    long i;
    if (p == NULL) return;  
    
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->n; i++){
        printf("%ld ",(long)p->r[i].Chave);
    }
    
    putchar('\n');
    nivel++;
  
    for (i = 0; i <= p->n; i++)
        ImprimeI(p->p[i], nivel,widget);
}

void Imprime(TipoApontador p,Widgets *widget)
{
    int  n = 0;
    ImprimeI(p, n,widget);
}

void Reconstitui(TipoApontador ApPag, TipoApontador ApPai,
                 int PosPai, short *Diminuiu)
{
    TipoPagina *Aux;
    long DispAux, j;
    if (PosPai < ApPai->n)  /* Aux = TipoPagina a direita de ApPag */
    {
        Aux = ApPai->p[PosPai+1];
        DispAux = (Aux->n - M + 1) / 2;
        ApPag->r[ApPag->n] = ApPai->r[PosPai];
        ApPag->p[ApPag->n + 1] = Aux->p[0];
        ApPag->n++;
        if (DispAux > 0)  /* Existe folga: transfere de Aux para ApPag */
        {
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
            ApPai->r[PosPai] = Aux->r[DispAux-1];
            Aux->n -= DispAux;
            for (j = 0; j < Aux->n; j++) Aux->r[j] = Aux->r[j + DispAux];
            for (j = 0; j <= Aux->n; j++) Aux->p[j] = Aux->p[j + DispAux];
            *Diminuiu = FALSE;
        }
        else /* Fusao: intercala Aux em ApPag e libera Aux */
        {
            for (j = 1; j <= M; j++)
                InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
            free(Aux);
            for (j = PosPai + 1; j < ApPai->n; j++)
            {
                ApPai->r[j-1] = ApPai->r[j];
                ApPai->p[j] = ApPai->p[j+1];
            }
            ApPai->n--;
            if (ApPai->n >= M) *Diminuiu = FALSE;
        }
    }
    else /* Aux = TipoPagina a esquerda de ApPag */
    {
        Aux = ApPai->p[PosPai-1];
        DispAux = (Aux->n - M + 1) / 2;
        for (j = ApPag->n; j >= 1; j--) ApPag->r[j] = ApPag->r[j-1];
        ApPag->r[0] = ApPai->r[PosPai-1];
        for (j = ApPag->n; j >= 0; j--) ApPag->p[j+1] = ApPag->p[j];
        ApPag->n++;
        if (DispAux > 0) /* Existe folga: transf. de Aux para ApPag */
        {
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[Aux->n - j],
                               Aux->p[Aux->n - j + 1]);
            ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
            ApPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
            Aux->n -= DispAux;
            *Diminuiu = FALSE;
        }
        else /* Fusao: intercala ApPag em Aux e libera ApPag */
        {
            for (j = 1; j <= M; j++)
                InsereNaPagina(Aux, ApPag->r[j-1], ApPag->p[j]);
            free(ApPag);
            ApPai->n--;
            if (ApPai->n >= M)  *Diminuiu = FALSE;
        }
    }
}

void Antecessor(TipoApontador Ap, int Ind,
                TipoApontador ApPai, short *Diminuiu)
{
    if (ApPai->p[ApPai->n] != NULL)
    {
        Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
        if (*Diminuiu)
            Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
        return;
    }
    Ap->r[Ind-1] = ApPai->r[ApPai->n - 1];
    ApPai->n--;
    *Diminuiu = (ApPai->n < M);
}

void Ret(TipoChave Ch, TipoApontador *Ap, short *Diminuiu)
{
    long j, Ind = 1;
    TipoApontador Pag;
    if (*Ap == NULL)
    {
        printf("Erro: registro nao esta na arvore\n");
        *Diminuiu = FALSE;
        return;
    }
    Pag = *Ap;
    while (Ind < Pag->n && Ch > Pag->r[Ind-1].Chave) Ind++;
    if (Ch == Pag->r[Ind-1].Chave)
    {
        if (Pag->p[Ind-1] == NULL)   /* TipoPagina folha */
        {
            Pag->n--;
            *Diminuiu = (Pag->n < M);
            for (j = Ind; j <= Pag->n; j++)
            {
                Pag->r[j-1] = Pag->r[j];
                Pag->p[j] = Pag->p[j+1];
            }
            return;
        }
        /* TipoPagina nao e folha: trocar com antecessor */
        Antecessor(*Ap, Ind, Pag->p[Ind-1], Diminuiu);
        if (*Diminuiu)
            Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
        return;
    }
    if (Ch > Pag->r[Ind-1].Chave) Ind++;
    Ret(Ch, &Pag->p[Ind-1], Diminuiu);
    if (*Diminuiu) Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
}

void Retira(TipoChave Ch, TipoApontador *Ap)
{
    short Diminuiu;
    TipoApontador Aux;
    Ret(Ch, Ap, &Diminuiu);
    if (Diminuiu && (*Ap)->n == 0)  /* Arvore diminui na altura */
    {
        Aux = *Ap;
        *Ap = Aux->p[0];
        free(Aux);
    }
}

void geraDotAux(TipoApontador no,FILE *out)/*Função que gera o código DOT através da ordem da arvore*/
{
    int i;
    
    fprintf(out,"\"%p\" [shape=box,height=.1,label=\"", no); /* %p - imprime o endereço do ponteiro*/
    for(i = 0; i < no->n; i++)
        fprintf(out,"%d ", no->r[i].Chave);
    
    fprintf(out,"\"];\n");

    for(i = 0; i < no->n; i++) {
        if(no->p[i]) {
           fprintf(out,"\"%p\" -> \"%p\";\n", no, no->p[i]);
           geraDotAux(no->p[i],out);
        }
    }
    if(no->p[i]) {
       fprintf(out,"\"%p\" -> \"%p\";\n", no, no->p[i]);
       geraDotAux(no->p[i],out);
    }
}

void geraArquivoDot(TipoApontador arvore,FILE *arqDot)/*Função que gera o código DOT através da ordem da arvore*/
{
    fprintf(arqDot,"ArvoreB {\n");
    geraDotAux(arvore,arqDot);
    fprintf(arqDot,"}\n");
}

void geraImagem(int index,TipoApontador arvore) /* Para cada passo da arvore é gerado uma imagem convertida em gif da linguagem DOT*/
{
    char tempstr[100];
    sprintf (tempstr, "temp%d.dot", index);
    arqDot = fopen(tempstr,"w");

    geraArquivoDot(arvore,arqDot);

    fclose(arqDot);

    sprintf(tempstr,"dot -Tgif temp%d.dot -o image%d.gif",index,index);
    system(tempstr);
}
