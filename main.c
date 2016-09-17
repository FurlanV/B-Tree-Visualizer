/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Vinicius Furlan
 *
 * Created on June 26, 2016, 4:21 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include "arvoreB.h"
#include "Widgets-GTK.h"

#define grau 2

int main( int argc, char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GError     *error = NULL;
    Widgets    widget;    

    /* Init GTK+ */
    gtk_init(&argc, &argv);

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    
    /* Load UI from file. If error occurs, report it and quit application. */    
    if(!gtk_builder_add_from_file( builder, "GUI.glade",&error ))
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    } 
    
    /* Carrega todos os itens da UI */
    window = GTK_WIDGET(gtk_builder_get_object( builder, "window1" ));  
    widget.txtNum = GTK_ENTRY(gtk_builder_get_object(builder,"txtNum"));
    widget.txtView = GTK_WIDGET(gtk_builder_get_object(builder,"txtView"));
    widget.gtkImg = GTK_WIDGET(gtk_builder_get_object(builder,"gtkImage"));
    widget.arvore = NULL;
    widget.i = 0;
    
    /* Conecta os sinais */
    gtk_builder_connect_signals(builder,&widget);

    /* Destroy builder, since we don't need it anymore */
    g_object_unref(G_OBJECT(builder));
    

    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show(window);

    /* Start main loop */
    gtk_main();

    return( 0 );
}