#include <iostream>
#include <gtkmm-4.0/gtkmm/application.h>

int main() {
    auto app = Gtk::Application::create("org.gtkmm.example");

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<TestWindow>(NULL, NULL);
}