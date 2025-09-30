//
// Created by olaus on 2025-09-28.
//

#include "MainWindow.h"

MainWindow::MainWindow()
: myButton("Hello World")   // creates a new button with label "Hello World".
{
    // Sets the margin around the button.
    myButton.set_margin(10);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    myButton.signal_clicked().connect(sigc::mem_fun(*this,
                &TestWindow::OnButtonClicked));

    // This packs the button into the Window (a container).
    set_child(myButton);
}

void MainWindow::OnButtonClicked() {
    std::cout << "Hello World" << std::endl;
}
