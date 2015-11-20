#include <iostream>
#include <cstdlib>
#include <gtkmm-3.0/gtkmm.h>

using namespace std;

Gtk::ApplicationWindow* mainwindow;
Gtk::AboutDialog* aboutdialog;
Gtk::MenuItem* aboutitem;
Gtk::MenuItem* quititem;

void onAboutMenuItemClick() {
    aboutdialog->run();
    aboutdialog->close();
}

void closeMainWindow() {
    mainwindow->close();
}

void closeAboutDialog() {
    aboutdialog->close();
}

int main(int argc, char** argv) {
    Glib::setenv("LC_ALL", "C", true);
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "me.phitherek.oziexplorer_to_uiview_converter");
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("oziexplorer_uiview_converter.glade");
    builder->set_application(app);
    mainwindow = NULL;
    builder->get_widget("mainwindow", mainwindow);
    aboutdialog = NULL;
    builder->get_widget("aboutdialog", aboutdialog);
    aboutitem = NULL;
    builder->get_widget("aboutitem", aboutitem);
    aboutitem->signal_activate().connect(sigc::ptr_fun(&onAboutMenuItemClick));
    quititem = NULL;
    builder->get_widget("quititem", quititem);
    quititem->signal_activate().connect(sigc::ptr_fun(&closeMainWindow));
    return app->run(*mainwindow);
}