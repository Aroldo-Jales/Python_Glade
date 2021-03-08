import gi
import cv2, os
import numpy as np

gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
builder = Gtk.Builder()

builder.add_from_file('gui.glade')

def new_img(filename, n, k):
    filename = filename
    img = cv2.imread(filename,0)
    amost_img = amostragem(img, n)
    quant_img = color_quantization(amost_img,k)
    name, extension = os.path.splitext(filename)
    new_filename = ('new-{name}{extension}'.format(name=name, extension=extension))
    cv2.imwrite(new_filename, quant_img)
    return new_filename

def amostragem(image, n):
    amostra = [lin[::n] for lin in image[::n]]
    return np.array(amostra)   

def color_quantization(image, K):
    data = np.float32(image).reshape((-1, 3))

    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 20, 1.0)

    ret, label, center = cv2.kmeans(data, K, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)
    center = np.uint8(center)
    result = center[label.flatten()]
    result = result.reshape(image.shape)
    return result

class Handler(object):
    def __init__(self, *args , **kwargs):
        super(Handler, self).__init__(*args ,**kwargs)
        
        self.img_frame = builder.get_object('img_frame')
        self.entry_n = builder.get_object('entry_n')
        self.entry_k = builder.get_object('entry_k')
        self.entry_source = builder.get_object('entry_source')
        self.bt_ok = builder.get_object('bt_ok')

    def on_bt_ok_clicked(self, *args):
        n = int(self.entry_n.get_text())
        k = int(self.entry_k.get_text())
        filename = self.entry_source.get_text()

        new_filename = new_img(filename,n,k)
        self.img_frame.set_from_file(new_filename)

    def on_main_window_destroy(self, *args):
        Gtk.main_quit()

builder.connect_signals(Handler())
window = builder.get_object('main_window')
window.show_all()

if __name__=='__main__':
    Gtk.main()
