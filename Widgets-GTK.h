/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Widgets-GTK.h
 * Author: Vinicius Furlan
 *
 * Created on June 26, 2016, 4:53 AM
 */


#ifndef WIDGETS_GTK_H
#define WIDGETS_GTK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gtk-3.0/gtk/gtk.h>
#include "arvoreB.h"
    
typedef struct{
    TipoPagina *arvore;
    TipoRegistro x;
    
    int i;
    GtkEntry *txtNum;
    GtkWidget *txtView;
    GtkWidget *gtkImg;
    GtkTextBuffer *buffer;
    GtkTextIter iter,iterEnd;
    GtkTextMark *mark;    
}Widgets;

G_MODULE_EXPORT void on_btnAdd_clicked(GtkButton *button,Widgets *widg);
G_MODULE_EXPORT void on_btnDel_clicked(GtkButton *button,Widgets *widg);
void on_window1_destroy();



#ifdef __cplusplus
}
#endif

#endif /* WIDGETS_GTK_H */

