#include <iostream>
#include <cstdlib>
#include <gtkmm-3.0/gtkmm.h>

using namespace std;

int main(int argc, char** argv) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "me.phitherek.oziexplorer_to_uiview_converter");
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("oziexplorer_uiview_converter.glade");
    builder->set_application(app);
    Gtk::Window* mainwindow = NULL;
    builder->get_widget("mainwindow", mainwindow);
    return app->run(*mainwindow);
}