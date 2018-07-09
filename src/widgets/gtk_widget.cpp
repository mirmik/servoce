#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <servoce/widgets/gtk_widget.h>
#include <gxx/print.h>


void servoce::gtk_widget_show(const servoce::scene& scn) {
    gtk_init(NULL, NULL);

    int win_width = 800;
    int win_height = 600;

    GtkWidget *window;
    GtkToolItem *exitIcon;
    GtkWidget *toolbar;
    GtkWidget *menubar;
    GtkWidget* fileMenu;
    GtkWidget* fileMi;
    GtkWidget* stlMi;
    GtkWidget* quitMi;
	GtkWidget* vbox;
//	GtkWidget *gl_area = gtk_gl_area_new ();

	GtkWidget *socket = gtk_socket_new ();
//	gtk_widget_show (socket);
	//gtk_container_add (GTK_CONTAINER (parent), socket);

	// The following call is only necessary if one of
	// the ancestors of the socket is not yet visible.
//	gtk_widget_realize (socket);
//	g_print ("The ID of the sockets window is %#x\n",
  //  	gtk_socket_get_id (GTK_SOCKET(socket)));

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	menubar = gtk_menu_bar_new();
  	fileMenu = gtk_menu_new();

	fileMi = gtk_menu_item_new_with_label("File");
	stlMi = gtk_menu_item_new_with_label("Make Stl...");
  	quitMi = gtk_menu_item_new_with_label("Quit");

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  	gtk_container_add(GTK_CONTAINER(window), vbox);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), stlMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), socket, FALSE, FALSE, 0);
	//gtk_box_pack_start(GTK_BOX(vbox), gl_area, FALSE, FALSE, 0);

	//g_signal_connect (gl_area, "render", G_CALLBACK (render), NULL);
	//g_signal_connect (gl_area, "realize", G_CALLBACK (realize), NULL);
	//g_signal_connect (gl_area, "unrealize", G_CALLBACK (unrealize), NULL);
	
  	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);

    //item = make_menu_item ("Top", G_CALLBACK (print_stuff), NULL);
    //gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);

    //toolbar = gtk_toolbar_new();
    //gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);


//    exitIcon = gtk_tool_button_new(gtk_image_new_from_icon_name(_("_Quit")));
  //  gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exitIcon, -1);


    gtk_window_set_default_size(GTK_WINDOW(window), win_width, win_height);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);

    gxx::println(gtk_socket_get_id(GTK_SOCKET(socket)));

    gxx::println("premain");
    gtk_main();
    gxx::println("postmain");

}