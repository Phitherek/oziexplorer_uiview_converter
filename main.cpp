#include <iostream>
#include <cstdlib>
#include <gtkmm-3.0/gtkmm.h>
#include <string>
#include <vector>
#include "ConversionWorker.h"

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
Gtk::Button* startconversionbutton = NULL;
Gtk::Button* cancelconversionbutton = NULL;
ConversionWorker* worker;
Glib::RefPtr<Gtk::Builder> builder;
Glib::RefPtr<Gtk::TextView> conversionlogtextview;
Glib::RefPtr<Gtk::TextBuffer> conversionlogtextbuffer;

void onAboutMenuItemClick() {
    aboutdialog->run();
    aboutdialog->close();
}

void closeMainWindow() {
    mainwindow->close();
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

void afterConversion() {
    delete worker;
    worker = NULL;
    inchooserentry->set_sensitive(true);
    outchooserentry->set_sensitive(true);
    inchooserbutton->set_sensitive(true);
    outchooserbutton->set_sensitive(true);
    cancelconversionbutton->set_sensitive(false);
    startconversionbutton->set_sensitive(true);
}

void startConversion() {
    inchooserentry->set_sensitive(false);
    outchooserentry->set_sensitive(false);
    inchooserbutton->set_sensitive(false);
    outchooserbutton->set_sensitive(false);
    startconversionbutton->set_sensitive(false);
    cancelconversionbutton->set_sensitive(true);
    if(outchooserentry->get_text() == "") {
        outchooserentry->set_text(inchooserentry->get_text());
    }
    worker = new ConversionWorker();
    worker->sig_done.connect(sigc::ptr_fun(&afterConversion));
    worker->setIndir(inchooserentry->get_text());
    worker->setOutdir(outchooserentry->get_text());
    worker->start(builder);
}

void cancelConversion() {
    worker->cancel();
}

int main(int argc, char** argv) {
    if(!Glib::thread_supported()) Glib::thread_init();
    Glib::setenv("LC_ALL", "C", true);
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "me.phitherek.oziexplorer_to_uiview_converter");
    builder = Gtk::Builder::create_from_file("oziexplorer_uiview_converter.glade");
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
    builder->get_widget("startconversionbutton", startconversionbutton);
    builder->get_widget("cancelconversionbutton", cancelconversionbutton);
    cancelconversionbutton->set_sensitive(false);
    startconversionbutton->signal_clicked().connect(sigc::ptr_fun(&startConversion));
    cancelconversionbutton->signal_clicked().connect(sigc::ptr_fun(&cancelConversion));
    return app->run(*mainwindow);
}