#include <iostream>
#include <cstdlib>
#include <gtkmm-3.0/gtkmm.h>

using namespace std;

Gtk::ApplicationWindow* mainwindow = NULL;
Gtk::AboutDialog* aboutdialog = NULL;
Gtk::FileChooserDialog* inchooserdialog = NULL;
Gtk::FileChooserDialog* outchooserdialog = NULL;
Gtk::MenuItem* aboutitem = NULL;
Gtk::MenuItem* quititem = NULL;
Gtk::Button* inchooserbutton = NULL;
Gtk::Button* outchooserbutton = NULL;
Gtk::Entry* inchooserentry = NULL;
Gtk::Entry* outchooserentry = NULL;

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

void openInChooserDialog() {
    if(inchooserentry->get_text() != "") {
        inchooserdialog->set_current_folder(inchooserentry->get_text());
    }
    inchooserdialog->run();
}

void openOutChooserDialog() {
    if(outchooserentry->get_text() != "") {
        outchooserdialog->set_current_folder(outchooserentry->get_text());
    }
    outchooserdialog->run();
}

void inChooserDialogResponse(int response_id) {
    if(response_id == Gtk::RESPONSE_CANCEL) {
        inchooserdialog->close();
    } else if(response_id == Gtk::RESPONSE_OK) {
        inchooserentry->set_text(inchooserdialog->get_current_folder());
        inchooserdialog->close();
    }
}

void outChooserDialogResponse(int response_id) {
    if(response_id == Gtk::RESPONSE_CANCEL) {
        outchooserdialog->close();
    } else if(response_id == Gtk::RESPONSE_OK) {
        outchooserentry->set_text(outchooserdialog->get_current_folder());
        outchooserdialog->close();
    }
}

int main(int argc, char** argv) {
    Glib::setenv("LC_ALL", "C", true);
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "me.phitherek.oziexplorer_to_uiview_converter");
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("oziexplorer_uiview_converter.glade");
    builder->set_application(app);
    builder->get_widget("mainwindow", mainwindow);
    builder->get_widget("aboutdialog", aboutdialog);
    builder->get_widget("aboutitem", aboutitem);
    aboutitem->signal_activate().connect(sigc::ptr_fun(&onAboutMenuItemClick));
    builder->get_widget("quititem", quititem);
    quititem->signal_activate().connect(sigc::ptr_fun(&closeMainWindow));
    builder->get_widget("inchooserdialog", inchooserdialog);
    builder->get_widget("outchooserdialog", outchooserdialog);
    builder->get_widget("inchooserbutton", inchooserbutton);
    builder->get_widget("outchooserbutton", outchooserbutton);
    inchooserdialog->add_button("Select", Gtk::RESPONSE_OK);
    inchooserdialog->add_button("Cancel", Gtk::RESPONSE_CANCEL);
    outchooserdialog->add_button("Select", Gtk::RESPONSE_OK);
    outchooserdialog->add_button("Cancel", Gtk::RESPONSE_CANCEL);
    inchooserbutton->signal_clicked().connect(sigc::ptr_fun(&openInChooserDialog));
    outchooserbutton->signal_clicked().connect(sigc::ptr_fun(&openOutChooserDialog));
    inchooserdialog->signal_response().connect(sigc::ptr_fun(&inChooserDialogResponse));
    outchooserdialog->signal_response().connect(sigc::ptr_fun(&outChooserDialogResponse));
    builder->get_widget("inchooserentry", inchooserentry);
    builder->get_widget("outchooserentry", outchooserentry);
    return app->run(*mainwindow);
}