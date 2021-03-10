#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <gtkmm.h>

using namespace Glib;
using namespace Gtk;
using namespace cv;
using namespace std;

string path_to_filename(string path);
//Mat K_means(Mat input, int k);

class FormExample : public Window {
public:
    FormExample() {
    add(scrolledWindow);
    scrolledWindow.add(fixed);
    

    button1.signal_button_release_event().connect([&](GdkEventButton* event) {
        FileChooserDialog openFileDialog("", FILE_CHOOSER_ACTION_OPEN);
        openFileDialog.add_button("Cancel", RESPONSE_CANCEL);
        openFileDialog.add_button("Open", RESPONSE_OK);
        
        if (openFileDialog.run() == RESPONSE_OK)
            path1 = openFileDialog.get_filename();
            filename = path_to_filename(path1);
            cout << path1 << endl;
            cout << filename << endl;
            Mat img;
            img = imread(path1);
            img1.set(path1);

        return true;
    });

    button2.signal_button_release_event().connect([&](GdkEventButton* event) {
            //string new_filename = "new"+filename;
            //Mat clustered_image = K_means(input_image, clusters);
        return true;
    });

    fixed.add(img1);
    fixed.move(img1, 10, 150);

    fixed.add(img2);
    fixed.move(img2, 700, 150);

    m_label1.set_label("K :");
    fixed.add(m_label1);
    fixed.move(m_label1, 10, 10);

    button1.set_label("Abrir");
    fixed.add(button1);
    fixed.move(button1, 10, 40);

    button2.set_label("Alterar");
    fixed.add(button2);
    fixed.move(button2, 85, 40);

    set_title("Gtkmm Example");
    resize(800, 500);
    show_all();
  }
  
private:
    ScrolledWindow scrolledWindow;
    Fixed fixed;
    Button button1, button2;
    Image img1, img2;
    Entry m_entry1, m_entry2;
    Label m_label1, m_label2;
    string path1, filename;
};
/*
Mat K_means(Mat input, int k)
{
	Mat samples(input.rows* input.cols, input.channels(), CV_32F); // Muda pra float
	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++) {
			for (int z = 0; z < input.channels(); z++) {
				if (input.channels() == 3) {
					samples.at<float>(y + x * input.rows, z) = input.at<Vec3b>(y, x)[z]; // para imagens coloridas
				}
				else {
					samples.at<float>(y + x * input.rows) = input.at<uchar>(y, x); // para imagens em escala de cinza
				}
			}
		}
	}

	Mat labels;
	int attempts = 5;
	Mat centeres;
	kmeans(samples, k, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10, 1.0), attempts, KMEANS_PP_CENTERS, centeres);
	
	Mat new_image(input.size(), input.type());
	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++) {
			int cluster_idx = labels.at<int>(y + x * input.rows, 0);
			if (input.channels() == 3) {
				for (int z = 0; z < input.channels(); z++) {
					new_image.at<Vec3b>(y, x)[z] = centeres.at<float>(cluster_idx, z);
				}
			}
			else {
				new_image.at<uchar>(y, x) = centeres.at<float>(cluster_idx, 0);
			}
		}
	}

	return new_image;
}
*/
string path_to_filename(string path) {
    const size_t last_slash_idx = path.find_last_of("/");
    if (std::string::npos != last_slash_idx)
    {
        path.erase(0, last_slash_idx + 1);
    }

    return path;
}
int main(int argc, char* argv[]) {
  RefPtr<Application> app = Application::create(argc, argv);
  FormExample FormExample;
  return app->run(FormExample);
}
