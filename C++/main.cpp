#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <gtkmm.h>

using namespace Glib;
using namespace Gtk;
using namespace cv;
using namespace std;

class GtkmmExample : public Window {

public:
    GtkmmExample() {
    
    
    add(main_window);
    main_window.add(fixed);

    fixed.add(m_img);
    fixed.move(m_img, 10, 150);

    m_button1.set_label("Abrir");
    fixed.add(m_button1);
    fixed.move(m_button1, 10, 10);

    m_button2.set_label("Tons de Cinza");
    fixed.add(m_button2);
    fixed.move(m_button2, 80, 10);
    
    m_button1.signal_button_release_event().connect([&](GdkEventButton* event) {
        FileChooserDialog openFileDialog("", FILE_CHOOSER_ACTION_OPEN);
        openFileDialog.add_button("Abrir", RESPONSE_OK);
        openFileDialog.add_button("Cancelar", RESPONSE_CANCEL);
        
        if (openFileDialog.run() == RESPONSE_OK)
            path = openFileDialog.get_filename();
            m_img.set(path);

        return true;
    });

    m_button2.signal_button_release_event().connect([&](GdkEventButton* event) {
            img = imread(path, 0);
            imshow("", img);

        return true;
    });

    set_title("Gtkmm Example");
    resize(700, 700);
    show_all();
  }
  
private:
    ScrolledWindow main_window;
    Fixed fixed;

    Button m_button1, m_button2;
    Image m_img;

    
    string path;
    Mat img;
};

int main(int argc, char* argv[]) {
  RefPtr<Application> app = Application::create(argc, argv);
  GtkmmExample gtkmm_example;
  return app->run(gtkmm_example);
}
