/*
 *  Copyright 2000-2001: Sergio Rua <srua@debian.org>
 *  Copyright 2008 Joop Stakenborg <pg4i@amsat.org>
 *  Copyright 2008 Anibal Avelar <aavelar@cofradia.org>
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

extern GtkWidget *wprincipal;
GtkUIManager *ui_manager;

static const GtkActionEntry entries[] = {
  { "FileMenu", NULL, "_File" },
  { "New", GTK_STOCK_NEW, N_("_New"), NULL, "", G_CALLBACK(on_novo1_activate) },
  { "Wizard", NULL, N_("New _Wizard page"), NULL, "", G_CALLBACK(on_new_wizard_page1_activate) },
  { "Open", GTK_STOCK_OPEN, N_("_Open..."), NULL, "", G_CALLBACK(on_abrir1_activate) },
  { "Save", GTK_STOCK_SAVE, N_("_Save"), NULL, "", G_CALLBACK(on_gardar1_activate) },
  { "SaveAs", GTK_STOCK_SAVE_AS, N_("Save _As..."), NULL, "", G_CALLBACK(on_gardar_como1_activate) },
  { "Quit", GTK_STOCK_QUIT, N_("_Quit"), NULL, "", G_CALLBACK(on_sair4_activate) },
  { "EditMenu", NULL, "_Edit" },
  { "Cut", GTK_STOCK_CUT, N_("Cu_t"), NULL, "", G_CALLBACK(on_cortar1_activate) },
  { "Copy", GTK_STOCK_COPY, N_("_Copy"), NULL, "", G_CALLBACK(on_copiar1_activate) },
  { "Paste", GTK_STOCK_PASTE, N_("_Paste"), NULL, "", G_CALLBACK(on_pegar1_activate) },
  { "SelectAll", GTK_STOCK_SELECT_ALL, N_("_Select All"), NULL, "", G_CALLBACK(on_select_all1_activate) },
  { "InsertMenu", NULL, "_Insert" },
  { "BasicPage", NULL, N_("Basic Page"), NULL, "", G_CALLBACK(on_pagina_base1_activate) },
  { "Title", NULL, N_("Titel"), NULL, "", G_CALLBACK(on_titulo_activate) },
  { "Date", NULL, N_("Date"), NULL, "", G_CALLBACK(on_data1_activate) },
  { "SectionMenu", NULL, "Section" },
  { "Name", NULL, N_("Name"), NULL, "", G_CALLBACK(on_nome1_activate) },
  { "Synopsis", NULL, N_("Synopsis"), NULL, "", G_CALLBACK(on_sinopsis1_activate) },
  { "Description", NULL, N_("Description"), NULL, "", G_CALLBACK(on_descripcion1_activate) },
  { "Options", NULL, N_("Options"), NULL, "", G_CALLBACK(on_opcions1_activate) },
  { "ReturnValues", NULL, N_("Return values"), NULL, "", G_CALLBACK(on_valores_retornados1_activate) },
  { "ExitStatus", NULL, N_("Exit status"), NULL, "", G_CALLBACK(on_estados_de_saida1_activate) },
  { "Usage", NULL, N_("Usage"), NULL, "", G_CALLBACK(on_uso1_activate) },
  { "File", NULL, N_("File"), NULL, "", G_CALLBACK(on_ficheiro1_activate) },
  { "Environment", NULL, N_("Environment"), NULL, "", G_CALLBACK(on_entorno1_activate) },
  { "Diagnostics", NULL, N_("Diagnostics"), NULL, "", G_CALLBACK(on_diagnostico1_activate) },
  { "Security", NULL, N_("Security"), NULL, "", G_CALLBACK(on_seguridade1_activate) },
  { "Notes", NULL, N_("Notes"), NULL, "", G_CALLBACK(on_notas1_activate) },
  { "Bugs", NULL, N_("Bugs"), NULL, "", G_CALLBACK(on_bugs1_activate) },
  { "Author", NULL, N_("Author"), NULL, "", G_CALLBACK(on_autor1_activate) },
  { "Examples", NULL, N_("Examples"), NULL, "", G_CALLBACK(on_exemplos1_activate) },
  { "SeeAlso", NULL, N_("See also"), NULL, "", G_CALLBACK(on_ver_tamen1_activate) },
  { "ConformingTo", NULL, N_("Conforming to"), NULL, "", G_CALLBACK(on_conforme_a1_activate) },
  { "Other", NULL, N_("Other"), NULL, "", G_CALLBACK(on_otro1_activate) },
  { "JustifyMenu", NULL, "Justify" },
  { "Left", NULL, N_("Left"), NULL, "", G_CALLBACK(on_xustificacion_a_esquerda1_activate) },
  { "Both", NULL, N_("Both"), NULL, "", G_CALLBACK(on_ambas1_activate) },
  { "FillingMenu", NULL, "Filling" },
  { "Enable", NULL, N_("Enable"), NULL, "", G_CALLBACK(on_activar1_activate) },
  { "Disable", NULL, N_("Disable"), NULL, "", G_CALLBACK(on_desactivar1_activate) },
  { "LetterTypeMenu", NULL, "Lettertype" },
  { "Bold", NULL, N_("Bold"), NULL, "", G_CALLBACK(on_bold1_activate) },
  { "BoldRoman", NULL, N_("Bold - Roman"), NULL, "", G_CALLBACK(on_bold_roman1_activate) },
  { "Italic", NULL, N_("Italic"), NULL, "", G_CALLBACK(on_italica1_activate) },
  { "ItalicBold", NULL, N_("Italic - Bold"), NULL, "", G_CALLBACK(on_italica_bold1_activate) },
  { "ItalicRoman", NULL, N_("Italic - Roman"), NULL, "", G_CALLBACK(on_italica_roman1_activate) },
  { "RomanBold", NULL, N_("Roman - Bold"), NULL, "", G_CALLBACK(on_roman_bold1_activate) },
  { "RomanItalic", NULL, N_("Roman - Italic"), NULL, "", G_CALLBACK(on_roman_italic1_activate) },
  { "SmallBold", NULL, N_("Small - Bold"), NULL, "", G_CALLBACK(on_small_bold1_activate) },
  { "Small", NULL, N_("Small"), NULL, "", G_CALLBACK(on_small1_activate) },
  { "ParagraphsMenu", NULL, "Paragraphs" },
  { "NewParagraph", NULL, N_("New Paragraph"), NULL, "", G_CALLBACK(on_novo_parrafo1_activate) },
  { "ParagraphStart", NULL, N_("Paragraph Start"), NULL, "", G_CALLBACK(on_comezo_parrafo1_activate) },
  { "MarginMenu", NULL, "MarginSection" },
  { "MarginStart", NULL, N_("Margin start"), NULL, "", G_CALLBACK(on_comezo_marxen1_activate) },
  { "MarginEnd", NULL, N_("Margin end"), NULL, "", G_CALLBACK(on_finaliza_marxen1_activate) },
  { "HypertextMenu", NULL, "Hypertext" },
  { "AHREF", NULL, N_("A HREF"), NULL, "", G_CALLBACK(on_a_href1_activate) },
  { "ANAME", NULL, N_("A NAME"), NULL, "", G_CALLBACK(on_a_name1_activate) },
  { "OthersMenu", NULL, "Others" },
  { "DefaultTabs", NULL, N_("Default tabs"), NULL, "", G_CALLBACK(on_tabulador_por_defecto1_activate) },
  { "Subheader", NULL, N_("Subheader"), NULL, "", G_CALLBACK(on_subcabeceira1_activate) },
  { "EmptyLines", NULL, N_("Empty lines"), NULL, "", G_CALLBACK(on_lineas_en_branco1_activate) },
  { "Comments", NULL, N_("Comments"), NULL, "", G_CALLBACK(on_comments1_activate) },
  { "ViewMenu", NULL, "_View" },
  { "ViewCreatedPage", NULL, N_("View created page"), NULL, "", G_CALLBACK(on_paxina_creada1_activate) },
  { "Preferences", GTK_STOCK_PREFERENCES, N_("_Preferences"), NULL, "", G_CALLBACK(on_opcions_programa1_activate) },
  { "HelpMenu", NULL, "_Help" },
  { "Help", GTK_STOCK_HELP, N_("H_elp"), NULL, "", G_CALLBACK(on_help1_activate) },
  { "Homepage", NULL, N_("_Home page"), NULL, "", G_CALLBACK(on_home_page1_activate) },
  { "About", GTK_STOCK_ABOUT, N_("_About"), NULL, "", G_CALLBACK(on_about2_activate) },
};

static const char *ui_description =
"<ui>"
"  <menubar name='MainMenu'>"
"        <menu action='FileMenu'>"
"               <menuitem action='New'/>"
"               <menuitem action='Wizard'/>"
"               <menuitem action='Open'/>"
"               <menuitem action='Save'/>"
"               <menuitem action='SaveAs'/>"
"               <separator name='sep1'/>"
"               <menuitem action='Quit'/>"
"        </menu>"
"        <menu action='EditMenu'>"
"               <menuitem action='Cut'/>"
"               <menuitem action='Copy'/>"
"               <menuitem action='Paste'/>"
"               <menuitem action='SelectAll'/>"
"        </menu>"
"        <menu action='InsertMenu'>"
"               <menuitem action='BasicPage'/>"
"               <menuitem action='Title'/>"
"               <menuitem action='Date'/>"
"                     <menu action='SectionMenu'>"
"                           <menuitem action='Name'/>"
"                           <menuitem action='Synopsis'/>"
"                           <menuitem action='Description'/>"
"                           <menuitem action='Options'/>"
"                           <menuitem action='ReturnValues'/>"
"                           <menuitem action='ExitStatus'/>"
"                           <menuitem action='Usage'/>"
"                           <menuitem action='File'/>"
"                           <menuitem action='Environment'/>"
"                           <menuitem action='Diagnostics'/>"
"                           <menuitem action='Security'/>"
"                           <menuitem action='Notes'/>"
"                           <menuitem action='Bugs'/>"
"                           <menuitem action='Author'/>"
"                           <menuitem action='Examples'/>"
"                           <menuitem action='SeeAlso'/>"
"                           <menuitem action='ConformingTo'/>"
"                           <menuitem action='Other'/>"
"                     </menu>"
"                     <menu action='JustifyMenu'>"
"                           <menuitem action='Left'/>"
"                           <menuitem action='Both'/>"
"                     </menu>"
"                     <menu action='FillingMenu'>"
"                           <menuitem action='Enable'/>"
"                           <menuitem action='Disable'/>"
"                     </menu>"
"                     <menu action='LetterTypeMenu'>"
"                           <menuitem action='Bold'/>"
"                           <menuitem action='BoldRoman'/>"
"                           <menuitem action='Italic'/>"
"                           <menuitem action='ItalicBold'/>"
"                           <menuitem action='ItalicRoman'/>"
"                           <menuitem action='RomanBold'/>"
"                           <menuitem action='RomanItalic'/>"
"                           <menuitem action='SmallBold'/>"
"                           <menuitem action='Small'/>"
"                     </menu>"
"                     <menu action='ParagraphsMenu'>"
"                           <menuitem action='NewParagraph'/>"
"                           <menuitem action='ParagraphStart'/>"
"                     </menu>"
"                     <menu action='MarginMenu'>"
"                           <menuitem action='MarginStart'/>"
"                           <menuitem action='MarginEnd'/>"
"                     </menu>"
"                     <menu action='HypertextMenu'>"
"                           <menuitem action='AHREF'/>"
"                           <menuitem action='ANAME'/>"
"                     </menu>"
"                     <menu action='OthersMenu'>"
"                           <menuitem action='DefaultTabs'/>"
"                           <menuitem action='Subheader'/>"
"                           <menuitem action='EmptyLines'/>"
"                           <menuitem action='Comments'/>"
"                     </menu>"
"        </menu>"
"        <menu action='ViewMenu'>"
"               <menuitem action='ViewCreatedPage'/>"
"               <menuitem action='Preferences'/>"
"        </menu>"
"        <menu action='HelpMenu'>"
"               <menuitem action='Help'/>"
"               <menuitem action='Homepage'/>"
"               <menuitem action='About'/>"
"        </menu>"
"  </menubar>"
"  <toolbar name='ToolBar'>"
"        <toolitem action='New'/>"
"        <toolitem action='Open'/>"
"        <toolitem action='Save'/>"
"        <separator name='septool1'/>"
"        <toolitem action='Cut'/>"
"        <toolitem action='Copy'/>"
"        <toolitem action='Paste'/>"
"        <separator name='septool2'/>"
"        <toolitem action='Quit'/>"
"  </toolbar>"
"</ui>";


GtkWidget*
create_wprincipal (void)
{
  GtkWidget *wprincipal;
  GtkWidget *vbox1;
  GtkWidget *scrolledwindow1;
  GtkWidget *text;
  GtkWidget *statusbar1;

  wprincipal = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_object_set_data (G_OBJECT (wprincipal), "wprincipal", wprincipal);
  gtk_widget_set_size_request (wprincipal, 640, 500);
  gtk_window_set_title (GTK_WINDOW (wprincipal), _("Gmanedit - Gnome manpages editor"));
  GdkPixbuf *icon_pixbuf = create_image ("gmanedit_icon.png");
  gtk_window_set_icon (GTK_WINDOW (wprincipal), icon_pixbuf);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (wprincipal), vbox1);
  
  GtkActionGroup *action_group = gtk_action_group_new ("MenuActions");
  gtk_action_group_set_translation_domain (action_group, PACKAGE);
  gtk_action_group_add_actions (action_group, entries,
                G_N_ELEMENTS (entries), wprincipal);
  ui_manager = gtk_ui_manager_new ();
  gtk_ui_manager_insert_action_group (ui_manager, action_group, 0);
  GtkAccelGroup *accel_group = gtk_ui_manager_get_accel_group (ui_manager);
  gtk_window_add_accel_group (GTK_WINDOW (wprincipal), accel_group);
  
  gtk_ui_manager_add_ui_from_string (ui_manager, ui_description, -1, NULL);
  GtkWidget *menubar = gtk_ui_manager_get_widget (ui_manager, "/MainMenu");
  gtk_box_pack_start (GTK_BOX (vbox1), menubar, FALSE, FALSE, 0);
  
  GtkWidget *handlebox = gtk_handle_box_new ();
  gtk_box_pack_start (GTK_BOX (vbox1), handlebox, FALSE, FALSE, 0);
  GtkWidget *toolbar = gtk_ui_manager_get_widget (ui_manager, "/ToolBar");
  gtk_container_add (GTK_CONTAINER (handlebox), toolbar);
  gtk_widget_show_all (handlebox);
  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

  text = GTK_WIDGET(gtk_text_view_new());
  HOOKUP_OBJECT (wprincipal, text, "text");
  gtk_widget_show (text);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), text);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(text), TRUE);

  statusbar1 = gtk_statusbar_new ();
  HOOKUP_OBJECT (wprincipal, statusbar1, "statusbar1");
  gtk_widget_show (statusbar1);
  gtk_box_pack_start (GTK_BOX (vbox1), statusbar1, FALSE, FALSE, 0);

  g_signal_connect (G_OBJECT (wprincipal), "delete_event",
                      G_CALLBACK (on_wprincipal_delete),
                      NULL);
  g_signal_connect (G_OBJECT (text), "drag_data_received",
                      G_CALLBACK (on_text_drag_data_received),
                      NULL);

  gtk_widget_grab_focus (text);
  return wprincipal;
}

GtkWidget*
create_fileselection (GtkWidget *parent)
{
  GtkWidget *fileselection;

  fileselection = gtk_file_chooser_dialog_new (_("Gmanedit - Select file"),
				      GTK_WINDOW (parent),
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
  GdkPixbuf *icon_pixbuf = create_image ("gmanedit_icon.png");
  gtk_window_set_icon (GTK_WINDOW (fileselection), icon_pixbuf);

  return fileselection;
}

GtkWidget*
create_save_file (GtkWidget *parent)
{
  GtkWidget *save_file;

  save_file = gtk_file_chooser_dialog_new (_("Gmanedit - Saving file"),
				      GTK_WINDOW (parent),
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
  GdkPixbuf *icon_pixbuf = create_image ("gmanedit_icon.png");
  gtk_window_set_icon (GTK_WINDOW (save_file), icon_pixbuf);

  return save_file;
}

GtkWidget*
create_wbuscar (void)
{
  GtkWidget *wbuscar;
  GtkWidget *vbox2;
  GtkWidget *hbox1;
  GtkWidget *label1;
  GtkWidget *buscar;
  GtkWidget *hbox2;
  GtkWidget *label2;
  GtkWidget *reemprazar;
  GtkWidget *hbuttonbox1;
  GtkWidget *bbuscar;
  GtkWidget *breemprazar;
  GtkWidget *bpechar;

  wbuscar = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_object_set_data (G_OBJECT (wbuscar), "wbuscar", wbuscar);
  gtk_window_set_title (GTK_WINDOW (wbuscar), _("Gmanedit - Search and replace"));
  gtk_window_set_position (GTK_WINDOW (wbuscar), GTK_WIN_POS_CENTER);
  GdkPixbuf *icon_pixbuf = create_image ("gmanedit_icon.png");
  gtk_window_set_icon (GTK_WINDOW (wbuscar), icon_pixbuf);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (wbuscar), vbox2);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox1, FALSE, FALSE, 0);

  label1 = gtk_label_new (_("Search:         "));
  gtk_widget_show (label1);
  gtk_box_pack_start (GTK_BOX (hbox1), label1, FALSE, FALSE, 0);

  buscar = gtk_entry_new ();
  HOOKUP_OBJECT (wbuscar, buscar, "buscar");
  gtk_widget_show (buscar);
  gtk_box_pack_start (GTK_BOX (hbox1), buscar, TRUE, TRUE, 0);
  gtk_entry_set_text (GTK_ENTRY (buscar), _("Option not yet available"));

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

  label2 = gtk_label_new (_("Replace with: "));
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (hbox2), label2, FALSE, FALSE, 0);

  reemprazar = gtk_entry_new ();
  HOOKUP_OBJECT (wbuscar, reemprazar, "reemprazar");
  gtk_widget_show (reemprazar);
  gtk_box_pack_start (GTK_BOX (hbox2), reemprazar, TRUE, TRUE, 0);
  gtk_entry_set_text (GTK_ENTRY (reemprazar), _("Option not yet available"));

  hbuttonbox1 = gtk_hbutton_box_new ();
  gtk_widget_show (hbuttonbox1);
  gtk_box_pack_start (GTK_BOX (vbox2), hbuttonbox1, TRUE, TRUE, 0);

  bbuscar = gtk_button_new_with_mnemonic ("_Search");
  HOOKUP_OBJECT (wbuscar, bbuscar, "bbuscar");
  gtk_widget_show (bbuscar);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), bbuscar);

  breemprazar = gtk_button_new_with_label ("_Replace");
  HOOKUP_OBJECT (wbuscar, breemprazar, "breemprazar");
  gtk_widget_show (breemprazar);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), breemprazar);

  bpechar = gtk_button_new_with_label ("_Close");
  HOOKUP_OBJECT (wbuscar, bpechar, "bpechar");
  gtk_widget_show (bpechar);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), bpechar);

  g_signal_connect (G_OBJECT (bbuscar), "clicked",
                      G_CALLBACK (on_bbuscar_clicked),
                      NULL);
  g_signal_connect (G_OBJECT (breemprazar), "clicked",
                      G_CALLBACK (on_breemprazar_clicked),
                      NULL);
  g_signal_connect (G_OBJECT (bpechar), "clicked",
                      G_CALLBACK (on_bpechar_clicked),
                      NULL);
  return wbuscar;
}

void create_about (void)
{
  const gchar *authors[] = {
    "Sergio Rua <email unknown>",
    "Joop Stakenborg <pg4i@amsat.org>",
    "Anibal Avelar <aavelar@cofradia.org>",
    NULL
  };
  const gchar *translators = "Sergio Rua <email unknown>\n"
	"Jordi Mallach <jordi@sindominio.net>\n"
	"Takeshi Aihana <aihana@muc.biglobe.ne.jp>";

  const gchar *license =
    "Copyright 2000, 2001 Sergio Rua <email unknown>\n"
    "Copyright 2008 Joop Stakenborg <pg4i@amsat.org>\n"
    "Copyright 2008 Anibal Avelar <aavelar@cofradia.org>\n"
    "\n"
    "This program is free software; you can redistribute it and/or modify\n"
    "it under the terms of the GNU General Public License as published by\n"
    "the Free Software Foundation; either version 2 of the License, or\n"
    "(at your option) any later version.\n"
    "\n"
    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "GNU Library General Public License for more details.\n"
    "\n"
    "You should have received a copy of the GNU Library General Public License\n"
    "along with this program; if not, write to the Free Software Foundation,\n"
    "Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.";

  GdkPixbuf *icon_pixbuf = create_image ("gmanedit.png");

  gtk_show_about_dialog (GTK_WINDOW(wprincipal),
  	"authors", authors,
  	"comments", _("Man Pages Editor"),
  	"license", license,
  	"website", "http://sourceforge.net/projects/gmanedit2",
  	"logo", icon_pixbuf,
  	"translator-credits", translators,
  	"version", VERSION,
  	NULL);
}

GtkWidget*
create_exit_dialog (void)
{
  GtkWidget *exit_dialog;
  GtkWidget *label3;
  GtkWidget *ok_button;
  GtkWidget *cancel_button;

  exit_dialog = gtk_dialog_new_with_buttons (_("Gmanedit - Exit"),
  	GTK_WINDOW(wprincipal), GTK_DIALOG_DESTROY_WITH_PARENT, NULL);

  label3 = gtk_label_new (_("Exit from gmanedit?"));
  gtk_widget_show (label3);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG (exit_dialog)->vbox), label3);
  gtk_misc_set_padding (GTK_MISC (label3), 10, 10);
  
  ok_button = gtk_dialog_add_button (GTK_DIALOG (exit_dialog),
                GTK_STOCK_OK, GTK_RESPONSE_OK);
  cancel_button = gtk_dialog_add_button (GTK_DIALOG (exit_dialog),
                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);

  g_signal_connect (G_OBJECT (ok_button), "clicked",
                      G_CALLBACK (on_bdialog_yes_clicked),
                      NULL);
  g_signal_connect (G_OBJECT (cancel_button), "clicked",
                      G_CALLBACK (on_bdialog_no_clicked),
                      NULL);

  return exit_dialog;
}

GtkWidget*
create_wpreferences (void)
{
  GtkWidget *wpreferences;
  GtkWidget *vbox3;
  GtkWidget *vbox4;
  GtkWidget *hbox3;
  GtkWidget *label4;
  GtkWidget *entry_command;
  GtkWidget *hbox4;
  GtkWidget *label17;
  GtkWidget *combo2;
//  GtkWidget *cbinet;
  GtkWidget *chgnome_help;
  GtkWidget *bpok;
  GtkWidget *bpcancel;
//  GtkTooltips *tooltips;

//  tooltips = gtk_tooltips_new ();

  wpreferences = gtk_dialog_new_with_buttons (_("Gmanedit - Preferences"),
  	GTK_WINDOW(wprincipal), GTK_DIALOG_DESTROY_WITH_PARENT, NULL);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox3);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG (wpreferences)->vbox), vbox3);

  vbox4 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox4);
  gtk_box_pack_start (GTK_BOX (vbox3), vbox4, TRUE, TRUE, 0);
  hbox3 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox3);
  gtk_box_pack_start (GTK_BOX (vbox4), hbox3, TRUE, TRUE, 0);
  label4 = gtk_label_new (_("Command to test created man pages: "));
  gtk_widget_show (label4);
  gtk_box_pack_start (GTK_BOX (hbox3), label4, FALSE, FALSE, 0);

  entry_command = gtk_entry_new ();
  gtk_widget_show (entry_command);
  HOOKUP_OBJECT (wpreferences, entry_command, "entry_command");

  gtk_box_pack_start (GTK_BOX (hbox3), entry_command, FALSE, TRUE, 0);
  gtk_entry_set_text (GTK_ENTRY (entry_command), _("xterm -e man "));
  hbox4 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox4);
  gtk_box_pack_start (GTK_BOX (vbox4), hbox4, TRUE, TRUE, 0);
  label17 = gtk_label_new (_("Internet browser"));
  gtk_widget_show (label17);
  gtk_box_pack_start (GTK_BOX (hbox4), label17, FALSE, FALSE, 0);
  combo2 = gtk_combo_box_entry_new_text ();
  gtk_widget_show (combo2);
  gtk_box_pack_start (GTK_BOX (hbox4), combo2, TRUE, TRUE, 0);
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo2), "netscape");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo2), "mozilla");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo2), "firefox");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo2), "galeon");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo2), "yelp");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo2), "konqueror");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo2), "nautilus");
  HOOKUP_OBJECT (wpreferences, combo2, "combo2");

//  gtk_tooltips_set_tip (tooltips, cbinet, _("Select your internet browser from this list"), NULL);

  chgnome_help = gtk_check_button_new_with_label (_("Use yelp"));
  gtk_widget_show (chgnome_help);
  HOOKUP_OBJECT (wpreferences, chgnome_help, "chgnome_help");
  gtk_box_pack_start (GTK_BOX (vbox3), chgnome_help, FALSE, FALSE, 0);

  bpok = gtk_dialog_add_button (GTK_DIALOG (wpreferences),
                GTK_STOCK_OK, GTK_RESPONSE_OK);
  bpcancel = gtk_dialog_add_button (GTK_DIALOG (wpreferences),
                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL);

  g_signal_connect (G_OBJECT (chgnome_help), "toggled",
                      G_CALLBACK (on_chgnome_help_toggled),
                      NULL);
  g_signal_connect (G_OBJECT (bpok), "clicked",
                      G_CALLBACK (on_bpok_clicked),
                      NULL);
  g_signal_connect (G_OBJECT (bpcancel), "clicked",
                      G_CALLBACK (on_bpcancel_clicked),
                      NULL);

  return wpreferences;
}

GtkWidget*
create_wizard (void)
{

  GtkWidget *wizard;
  GtkWidget *druid_vbox2;
  GtkWidget *fixed1;
  GtkWidget *mname;
  GtkWidget *mdate;
  GtkWidget *mtitle;
  GtkWidget *mauthor;
  GtkWidget *label14;
  GtkWidget *label15;
  GtkWidget *label16;
  GtkWidget *label1;
  GtkWidget *druid_vbox3;
  GtkWidget *fixed2;
  GtkWidget *label8;
  GtkWidget *label2;
  GtkWidget *label9;
  GtkWidget *label10;
  GtkWidget *label11;
  GtkWidget *label7;
  GtkWidget *label6;
  GtkWidget *label5;
  GtkWidget *label4;
  GtkWidget *label3;
  GtkWidget *combo1;
//  GtkWidget *snumber;
  GtkWidget *druid_vbox1;
  GtkWidget *fixed3;
  GtkWidget *label13;
  GtkWidget *cherrorh;
  GtkWidget *chenvironment;
  GtkWidget *chfiles;
  GtkWidget *chusage;
  GtkWidget *cherrors;
  GtkWidget *chsynopsis;
  GtkWidget *chdescription;
  GtkWidget *choptions;
  GtkWidget *chname;
  GtkWidget *chseealso;
  GtkWidget *chauthor;
  GtkWidget *chreturnvalues;
  GtkWidget *chdiagnostics;
  GtkWidget *chsecurity;
  GtkWidget *chconformingto;
  GtkWidget *chnotes;
  GtkWidget *chbugs;
//  GtkTooltips *tooltips;
  GdkPixbuf *icon_pixbuf;
  time_t fech;
  struct tm *fecha;
	gchar cad[30];
	gchar *meses[]={_("January"),_("February"),_("March"),_("April"),
        		_("May"),_("June"),_("July"),_("August"),
        		_("September"),_("October"),_("November"),_("December")};

//  tooltips = gtk_tooltips_new ();

  wizard = gtk_assistant_new ();
  gtk_window_set_title (GTK_WINDOW (wizard), _("Gmanedit - Wizard"));
  icon_pixbuf = create_image ("gmanedit_icon.png");
  gtk_window_set_icon (GTK_WINDOW (wizard), icon_pixbuf);

  GtkWidget *labelbegin = gtk_label_new (_("Welcome to the Gmanedit Man Pages Wizard. Follow the next steps to build a Basic Man Page"));
  gtk_label_set_line_wrap (GTK_LABEL(labelbegin), TRUE);
  gtk_widget_show (labelbegin);
  gtk_assistant_append_page (GTK_ASSISTANT (wizard), labelbegin);
  gtk_assistant_set_page_title (GTK_ASSISTANT (wizard), labelbegin, _("Welcome"));
  gtk_assistant_set_page_type (GTK_ASSISTANT (wizard), labelbegin, GTK_ASSISTANT_PAGE_INTRO);
  gtk_assistant_set_page_complete (GTK_ASSISTANT (wizard), labelbegin, TRUE);

  druid_vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (druid_vbox2);

  fixed1 = gtk_fixed_new ();
  gtk_widget_show (fixed1);
  gtk_box_pack_start (GTK_BOX (druid_vbox2), fixed1, TRUE, TRUE, 0);

  mname = gtk_entry_new ();
  HOOKUP_OBJECT (wizard, mname, "mname");
  gtk_widget_show (mname);
  gtk_fixed_put (GTK_FIXED (fixed1), mname, 248, 24);
  gtk_widget_set_size_request (mname, 158, 26);
//  gtk_tooltips_set_tip (tooltips, mname, _("Short name to the man page (example: gmanedit)"), NULL);
  
  mdate = gtk_entry_new ();
  HOOKUP_OBJECT (wizard, mdate, "mdate");
  gtk_widget_show (mdate);
  gtk_fixed_put (GTK_FIXED (fixed1), mdate, 248, 80);
  gtk_widget_set_size_request (mdate, 158, 26);
//  gtk_tooltips_set_tip (tooltips, mdate, _("Creation date (default today)"), NULL);
  time(&fech);
  fecha=localtime(&fech);
	
	if (fecha!=NULL)
	{
		sprintf(cad,"%s %d, %d",meses[fecha->tm_mon],fecha->tm_mday,fecha->tm_year+1900);			
		gtk_entry_set_text(GTK_ENTRY(mdate),cad);
	}

  mtitle = gtk_entry_new ();
  HOOKUP_OBJECT (wizard, mtitle, "mtitle");
  gtk_widget_show (mtitle);
  gtk_fixed_put (GTK_FIXED (fixed1), mtitle, 248, 136);
  gtk_widget_set_size_request (mtitle, 158, 26);
//  gtk_tooltips_set_tip (tooltips, mtitle, _("Long man page name or title"), NULL);

  mauthor = gtk_entry_new ();
  HOOKUP_OBJECT (wizard, mauthor, "mauthor");
  gtk_widget_show (mauthor);
  gtk_fixed_put (GTK_FIXED (fixed1), mauthor, 248, 192);
  gtk_widget_set_size_request (mauthor, 158, 26);
//  gtk_tooltips_set_tip (tooltips, mauthor, _("First_Name Last_Name <my@email.com>"), NULL);

  label14 = gtk_label_new (_("Creation Date:"));
  gtk_widget_show (label14);
  gtk_fixed_put (GTK_FIXED (fixed1), label14, 64, 80);
  gtk_widget_set_size_request (label14, 176, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label14), TRUE);

  label15 = gtk_label_new (_("Man page Title:"));
  gtk_widget_show (label15);
  gtk_fixed_put (GTK_FIXED (fixed1), label15, 64, 136);
  gtk_widget_set_size_request (label15, 176, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label15), TRUE);

  label16 = gtk_label_new (_("Author:"));
  gtk_widget_show (label16);
  gtk_fixed_put (GTK_FIXED (fixed1), label16, 64, 192);
  gtk_widget_set_size_request (label16, 120, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label16), TRUE);

  label1 = gtk_label_new (_("Man page Name:"));
  gtk_widget_show (label1);
  gtk_fixed_put (GTK_FIXED (fixed1), label1, 64, 24);
  gtk_widget_set_size_request (label1, 184, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label1), TRUE);

  gtk_assistant_append_page (GTK_ASSISTANT (wizard), druid_vbox2);
  gtk_assistant_set_page_title (GTK_ASSISTANT (wizard), druid_vbox2, _("Step 1: Basic Information"));
  gtk_assistant_set_page_type (GTK_ASSISTANT (wizard), druid_vbox2, GTK_ASSISTANT_PAGE_CONTENT);
  gtk_assistant_set_page_complete (GTK_ASSISTANT (wizard), druid_vbox2, TRUE);

  druid_vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (druid_vbox3);

  fixed2 = gtk_fixed_new ();
  gtk_widget_show (fixed2);
  gtk_box_pack_start (GTK_BOX (druid_vbox3), fixed2, TRUE, TRUE, 0);

  label8 = gtk_label_new (_("Section 5: File formats and conventions"));
  gtk_widget_show (label8);
  gtk_fixed_put (GTK_FIXED (fixed2), label8, 32, 136);
  gtk_widget_set_size_request (label8, 224, 40);
  gtk_label_set_line_wrap (GTK_LABEL (label8), TRUE);

  label2 = gtk_label_new (_("Section number"));
  gtk_widget_show (label2);
  gtk_fixed_put (GTK_FIXED (fixed2), label2, 56, 208);
  gtk_widget_set_size_request (label2, 144, 24);

  label9 = gtk_label_new (_("Section 6: Games"));
  gtk_widget_show (label9);
  gtk_fixed_put (GTK_FIXED (fixed2), label9, 264, 40);
  gtk_widget_set_size_request (label9, 184, 24);
  gtk_label_set_line_wrap (GTK_LABEL (label9), TRUE);

  label10 = gtk_label_new (_("Section 7: Conventions and miscellaneous"));
  gtk_widget_show (label10);
  gtk_fixed_put (GTK_FIXED (fixed2), label10, 264, 64);
  gtk_widget_set_size_request (label10, 240, 40);
  gtk_label_set_line_wrap (GTK_LABEL (label10), TRUE);

  label11 = gtk_label_new (_("Section 8: System management commands"));
  gtk_widget_show (label11);
  gtk_fixed_put (GTK_FIXED (fixed2), label11, 264, 104);
  gtk_widget_set_size_request (label11, 240, 40);
  gtk_label_set_line_wrap (GTK_LABEL (label11), TRUE);

  label7 = gtk_label_new (_("Section 4: Special files (devices)"));
  gtk_widget_show (label7);
  gtk_fixed_put (GTK_FIXED (fixed2), label7, 0, 112);
  gtk_widget_set_size_request (label7, 232, 24);

  label6 = gtk_label_new (_("Section 3: Library calls"));
  gtk_widget_show (label6);
  gtk_fixed_put (GTK_FIXED (fixed2), label6, 0, 88);
  gtk_widget_set_size_request (label6, 232, 24);

  label5 = gtk_label_new (_("Section 2: System calls"));
  gtk_widget_show (label5);
  gtk_fixed_put (GTK_FIXED (fixed2), label5, 0, 64);
  gtk_widget_set_size_request (label5, 240, 24);

  label4 = gtk_label_new (_("Section 1: Commands"));
  gtk_widget_show (label4);
  gtk_fixed_put (GTK_FIXED (fixed2), label4, 0, 40);
  gtk_widget_set_size_request (label4, 232, 24);

  label3 = gtk_label_new (_("There are 8 sections for man pages. Select one:"));
  gtk_widget_show (label3);
  gtk_fixed_put (GTK_FIXED (fixed2), label3, 0, 16);
  gtk_widget_set_size_request (label3, 504, 16);

  combo1 = gtk_combo_box_new_text ();
  gtk_widget_show (combo1);
  gtk_fixed_put (GTK_FIXED (fixed2), combo1, 240, 208);
  gtk_widget_set_size_request (combo1, 175, 26);
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "1");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "2");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "3");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "4");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "5");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "6");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "7");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "8");
  gtk_combo_box_append_text (GTK_COMBO_BOX(combo1), "9");
  gtk_combo_box_set_active (GTK_COMBO_BOX(combo1), 0);
  HOOKUP_OBJECT (wizard, combo1, "combo1");

//  gtk_tooltips_set_tip (tooltips, snumber, _("Select section number"), NULL);

  gtk_assistant_append_page (GTK_ASSISTANT (wizard), druid_vbox3);
  gtk_assistant_set_page_title (GTK_ASSISTANT (wizard), druid_vbox3, _("Step 2: Section number"));
  gtk_assistant_set_page_type (GTK_ASSISTANT (wizard), druid_vbox3, GTK_ASSISTANT_PAGE_CONTENT);
  gtk_assistant_set_page_complete (GTK_ASSISTANT (wizard), druid_vbox3, TRUE);

  druid_vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (druid_vbox1);

  fixed3 = gtk_fixed_new ();
  gtk_widget_show (fixed3);
  gtk_box_pack_start (GTK_BOX (druid_vbox1), fixed3, TRUE, TRUE, 0);

  label13 = gtk_label_new (_("What sections would you like include?"));
  gtk_widget_show (label13);
  gtk_fixed_put (GTK_FIXED (fixed3), label13, 64, 16);
  gtk_widget_set_size_request (label13, 344, 24);

  cherrorh = gtk_check_button_new_with_label (_("ERROR HANDLING"));
  gtk_widget_show (cherrorh);
  gtk_fixed_put (GTK_FIXED (fixed3), cherrorh, 16, 184);
  gtk_widget_set_size_request (cherrorh, 176, 24);

  chenvironment = gtk_check_button_new_with_label (_("ENVIRONMENT"));
  gtk_widget_show (chenvironment);
  gtk_fixed_put (GTK_FIXED (fixed3), chenvironment, 192, 184);
  gtk_widget_set_size_request (chenvironment, 152, 24);
  HOOKUP_OBJECT (wizard, chenvironment, "chenvironment");

  chfiles = gtk_check_button_new_with_label (_("FILES"));
  gtk_widget_show (chfiles);
  gtk_fixed_put (GTK_FIXED (fixed3), chfiles, 192, 152);
  gtk_widget_set_size_request (chfiles, 121, 28);
  HOOKUP_OBJECT (wizard, chfiles, "chfiles");

  chusage = gtk_check_button_new_with_label (_("USAGE"));
  gtk_widget_show (chusage);
  gtk_fixed_put (GTK_FIXED (fixed3), chusage, 192, 120);
  gtk_widget_set_size_request (chusage, 121, 28);
  HOOKUP_OBJECT (wizard, chusage, "chusage");

  cherrors = gtk_check_button_new_with_label (_("ERRORS"));
  gtk_widget_show (cherrors);
  gtk_fixed_put (GTK_FIXED (fixed3), cherrors, 192, 56);
  gtk_widget_set_size_request (cherrors, 121, 28);
  HOOKUP_OBJECT (wizard, cherrors, "cherrors");

  chsynopsis = gtk_check_button_new_with_label (_("SYNOPSIS"));
  gtk_widget_show (chsynopsis);
  gtk_fixed_put (GTK_FIXED (fixed3), chsynopsis, 16, 88);
  gtk_widget_set_size_request (chsynopsis, 121, 28);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (chsynopsis), TRUE);
  HOOKUP_OBJECT (wizard, chsynopsis, "chsynopsis");

  chdescription = gtk_check_button_new_with_label (_("DESCRIPTION"));
  gtk_widget_show (chdescription);
  gtk_fixed_put (GTK_FIXED (fixed3), chdescription, 16, 120);
  gtk_widget_set_size_request (chdescription, 136, 24);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (chdescription), TRUE);
  HOOKUP_OBJECT (wizard, chdescription, "chdescription");

  choptions = gtk_check_button_new_with_label (_("OPTIONS"));
  gtk_widget_show (choptions);
  gtk_fixed_put (GTK_FIXED (fixed3), choptions, 192, 88);
  gtk_widget_set_size_request (choptions, 121, 28);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (choptions), TRUE);
  HOOKUP_OBJECT (wizard, choptions, "choptions");

  chname = gtk_check_button_new_with_label (_("NAME"));
  gtk_widget_show (chname);
  gtk_fixed_put (GTK_FIXED (fixed3), chname, 16, 56);
  gtk_widget_set_size_request (chname, 121, 28);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (chname), TRUE);
  HOOKUP_OBJECT (wizard, chname, "chname");

  chseealso = gtk_check_button_new_with_label (_("SEE ALSO"));
  gtk_widget_show (chseealso);
  gtk_fixed_put (GTK_FIXED (fixed3), chseealso, 112, 208);
  gtk_widget_set_size_request (chseealso, 121, 28);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (chseealso), TRUE);
  HOOKUP_OBJECT (wizard, chseealso, "chseealso");

  chauthor = gtk_check_button_new_with_label (_("AUTHOR"));
  gtk_widget_show (chauthor);
  gtk_fixed_put (GTK_FIXED (fixed3), chauthor, 272, 208);
  gtk_widget_set_size_request (chauthor, 121, 28);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (chauthor), TRUE);
  HOOKUP_OBJECT (wizard, chauthor, "chauthor");

  chreturnvalues = gtk_check_button_new_with_label (_("RETURN VALUES"));
  gtk_widget_show (chreturnvalues);
  gtk_fixed_put (GTK_FIXED (fixed3), chreturnvalues, 16, 152);
  gtk_widget_set_size_request (chreturnvalues, 160, 32);
  HOOKUP_OBJECT (wizard, chreturnvalues, "chreturnvalues");

  chdiagnostics = gtk_check_button_new_with_label (_("DIAGNOSTICS"));
  gtk_widget_show (chdiagnostics);
  gtk_fixed_put (GTK_FIXED (fixed3), chdiagnostics, 336, 56);
  gtk_widget_set_size_request (chdiagnostics, 144, 24);
  HOOKUP_OBJECT (wizard, chdiagnostics, "chdiagnostics");

  chsecurity = gtk_check_button_new_with_label (_("SECURITY"));
  gtk_widget_show (chsecurity);
  gtk_fixed_put (GTK_FIXED (fixed3), chsecurity, 336, 88);
  gtk_widget_set_size_request (chsecurity, 121, 28);
  HOOKUP_OBJECT (wizard, chsecurity, "chsecurity");

  chconformingto = gtk_check_button_new_with_label (_("CONFORMING TO"));
  gtk_widget_show (chconformingto);
  gtk_fixed_put (GTK_FIXED (fixed3), chconformingto, 336, 120);
  gtk_widget_set_size_request (chconformingto, 168, 32);
  HOOKUP_OBJECT (wizard, chconformingto, "chconformingto");

  chnotes = gtk_check_button_new_with_label (_("NOTES"));
  gtk_widget_show (chnotes);
  gtk_fixed_put (GTK_FIXED (fixed3), chnotes, 336, 152);
  gtk_widget_set_size_request (chnotes, 121, 28);
  HOOKUP_OBJECT (wizard, chnotes, "chnotes");

  chbugs = gtk_check_button_new_with_label (_("BUGS"));
  gtk_widget_show (chbugs);
  gtk_fixed_put (GTK_FIXED (fixed3), chbugs, 336, 184);
  gtk_widget_set_size_request (chbugs, 121, 28);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (chbugs), TRUE);
  HOOKUP_OBJECT (wizard, chbugs, "chbugs");

  gtk_assistant_append_page (GTK_ASSISTANT (wizard), druid_vbox1);
  gtk_assistant_set_page_title (GTK_ASSISTANT (wizard), druid_vbox1, _("Step 3: Man Sections"));
  gtk_assistant_set_page_type (GTK_ASSISTANT (wizard), druid_vbox1, GTK_ASSISTANT_PAGE_CONTENT);
  gtk_assistant_set_page_complete (GTK_ASSISTANT (wizard), druid_vbox1, TRUE);


  GtkWidget *labelend = gtk_label_new (_("Thank you for using me! You can now edit the man page with gmanedit to change and complete the text"));
  gtk_label_set_line_wrap (GTK_LABEL(labelend), TRUE);
  gtk_widget_show (labelend);
  gtk_assistant_append_page (GTK_ASSISTANT (wizard), labelend);
  gtk_assistant_set_page_title (GTK_ASSISTANT (wizard), labelend, _("The End"));
  gtk_assistant_set_page_type (GTK_ASSISTANT (wizard), labelend, GTK_ASSISTANT_PAGE_CONFIRM);
  gtk_assistant_set_page_complete (GTK_ASSISTANT (wizard), labelend, TRUE);

  g_signal_connect (G_OBJECT (wizard), "close",
                    G_CALLBACK (on_dthe_end_finish), NULL);
  
  g_signal_connect (G_OBJECT (wizard), "cancel",
                    G_CALLBACK (on_assistant_cancel), NULL);
  return wizard;
}

