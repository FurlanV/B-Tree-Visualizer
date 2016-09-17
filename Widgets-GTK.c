/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Widgets-GTK.c
 * Author: Vinicius Furlan
 *
 * Created on June 26, 2016, 4:56 AM
 */


#include <string.h>
#include "Widgets-GTK.h"
#include "arvoreB.h"

G_MODULE_EXPORT void on_btnAdd_clicked( GtkButton *button, Widgets *widget )
{        
    char *imagem = (char*)malloc(sizeof(char)*50);
    char *mensagem = (char*)malloc(sizeof(char)*50);
    char mensagem2[50] = "Inseriu: ";
    
    widget->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget->txtView)); /*Este bloco prepara o textView para receber uma string */;
    widget->mark = gtk_text_buffer_get_insert(widget->buffer);
    gtk_text_buffer_get_iter_at_mark(widget->buffer,&(widget->iter),widget->mark);    
    gtk_text_buffer_get_end_iter(widget->buffer,&(widget->iterEnd));
    g_snprintf(mensagem,sizeof(mensagem),"%d\n",atoi(gtk_entry_get_text(widget->txtNum)));
    strcat(mensagem2,mensagem);
    
 
    if(atoi(gtk_entry_get_text(widget->txtNum)) != NULL){ 
        widget->x.Chave = atoi(gtk_entry_get_text(widget->txtNum));
        Insere(widget->x.Chave,&(widget->arvore));
        geraImagem(widget->i,widget->arvore);
    }
        
    gtk_text_buffer_insert(widget->buffer,&(widget->iter),mensagem2,-1);
    gtk_entry_set_text(widget->txtNum,"");
    g_snprintf(imagem,sizeof(imagem),"image%d",widget->i);
    strcat(imagem,".gif");
    gtk_image_set_from_file(GTK_IMAGE(widget->gtkImg),imagem);
    widget->i++;
    
    free(imagem);
    free(mensagem);
}

G_MODULE_EXPORT void on_btnDel_clicked( GtkButton *button, Widgets *widget)
{  
    char *imagem = (char*)malloc(sizeof(char)*50);
    char *mensagem = (char*)malloc(sizeof(char)*50);
    char mensagem2[50] = "Removeu: ";
    
    widget->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget->txtView));
    widget->mark = gtk_text_buffer_get_insert(widget->buffer);
    gtk_text_buffer_get_iter_at_mark(widget->buffer,&(widget->iter),widget->mark);    
    gtk_text_buffer_get_end_iter(widget->buffer,&(widget->iterEnd));
    g_snprintf(mensagem,sizeof(mensagem),"%d\n",atoi(gtk_entry_get_text(widget->txtNum)));
    strcat(mensagem2,mensagem);
    gtk_text_buffer_insert(widget->buffer,&(widget->iter),mensagem2,-1);
    
    if(atoi(gtk_entry_get_text(widget->txtNum)) != NULL){ 
        widget->x.Chave = atoi(gtk_entry_get_text(widget->txtNum));
        Retira(widget->x.Chave,&(widget->arvore));
        geraImagem(widget->i,widget->arvore);
    }
    
    gtk_entry_set_text(widget->txtNum,"");
    g_snprintf(imagem,sizeof(imagem),"image%d",widget->i);
    strcat(imagem,".gif");
    gtk_image_set_from_file(GTK_IMAGE(widget->gtkImg),imagem);
    widget->i++;
    
    free(imagem);
    free(mensagem);
}

G_MODULE_EXPORT void on_btnPesq_clicked( GtkButton *button, Widgets *widget)
{
    char *mensagem = (char*)malloc(sizeof(char)*50);
    char encontrado[] = " - Encontrado!\n";
    char nExiste[] = " - Nao econtrado!\n";
    
    if(atoi(gtk_entry_get_text(widget->txtNum)) != NULL && widget->arvore){ 
        widget->x.Chave = atoi(gtk_entry_get_text(widget->txtNum));
       
        if(Pesquisa(&(widget->x.Chave),widget->arvore)){
           g_snprintf(mensagem,sizeof(mensagem),"'%d' ",widget->x.Chave);
           strcat(mensagem,encontrado);
        } 
        else{
            g_snprintf(mensagem,sizeof(mensagem),"'%d'",widget->x.Chave);
            strcat(mensagem,nExiste);
        }
        gtk_text_buffer_insert(widget->buffer,&(widget->iter),mensagem,-1);
    }
    
    gtk_entry_set_text(widget->txtNum,"");
    free(mensagem);
}

G_MODULE_EXPORT void on_window1_destroy()
{
    gtk_main_quit();
}