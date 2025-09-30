//
// Created by olaus on 2025-09-28.
//

#ifndef HOMEWORKHELPER_MAINWINDOW_H
#define HOMEWORKHELPER_MAINWINDOW_H

#include <gtkmm-4.0/gtkmm/window.h>
#include <gtkmm-4.0/gtkmm/button.h>

class MainWindow : public Gtk::Window{
public:
    MainWindow();
    ~MainWindow() override = default;

protected:
    //Signal handlers:
    void OnButtonClicked();

    //Member widgets:
    Gtk::Button myButton;
};


#endif //HOMEWORKHELPER_MAINWINDOW_H