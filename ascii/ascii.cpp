#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

string char_scale = "@#&$B896PO1l!uzvatbaioc;:+-,._        ";

class Pixel {
private:
    int x, y;
    char element;
public:
    Pixel* next;
    Pixel* prev;

    Pixel(int _x, int _y, char _element) {
        this->x = _x;
        this->y = _y;
        this->element = _element;
    }

    void PrintChar() {
        cout << element;
    }
};

int init_font_x = 8;
int init_font_y = 14;
int scaled_font = 8;

Pixel* ConvertImage(int scaled_width, int scaled_height, Mat img) {
    //typedef Vec<unsigned char, 3> Vec3b - cv2 vector of unsigned chars (из документации)
    //но мое изображение конвертируется в черно-белое => вектор из 3-мерного превращается в 1-мерный (вроде как) => img.at<UCHAR>!!!!
    //cout << img.at<Vec3b>(0, 0);
    double depth = 0;
    double k = 0;
    int index = 0;
    int x = 0, y = 0;
    Pixel* next = NULL, * head = NULL;

    for (int i = 0; i < scaled_height * scaled_width; ++i) {
        y = scaled_height - (i / scaled_width) - 1;
        x = scaled_width - (i % scaled_width) - 1;

        depth = 0.299 * img.at<Vec3b>(y, x)[0] + 0.587 * img.at<Vec3b>(y, x)[1] + 0.114 * img.at<Vec3b>(y, x)[2];
        k = depth / 255;
        index = (char_scale.size() - k * char_scale.size());

        head = new Pixel(x, y, char_scale[index]);
        head->next = next;
        next = head;
    }

    return head;
}

void SetFullscrn() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void SetFontSize(int x, int y) {
    CONSOLE_FONT_INFOEX info = {0};
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = y;
    info.dwFontSize.X = x;
    info.FontWeight = FW_NORMAL;
    wcscpy_s(info.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

void PrintImage(Pixel* head, int scaled_width) {
    int cntr = 1;

    while (head != NULL) {
        if (cntr % scaled_width == 0) {
            cout << endl;
        }
        head->PrintChar();
        head = head->next;
        ++cntr;
    }
}

int main(int argc, char* argv[]) {
    SetFullscrn();
    SetFontSize(scaled_font, scaled_font);

    string img_path = argv[1];

    //loading an image
    Mat img = imread(img_path); 
    Mat init_img = imread(img_path);

    double img_height = img.size().height;
    double img_width = img.size().width;

    if (!img.data) {
        cout << "NO SHOT" << endl;
        return 0;
    }

    int scaled_height = 0.1 * img_height;
    int scaled_width = 0.1 * img_width;
    double area = scaled_width * scaled_height;

    resize(img, img, Size(scaled_width, scaled_height), INTER_LINEAR);
    
    Pixel* ascii_head = ConvertImage(scaled_width, scaled_height, img);
   
    PrintImage(ascii_head, (int)scaled_width);
    resize(img, img, Size(img_width, img_height), INTER_LINEAR);
    imshow("Ваше изображение", init_img);
    
    cv::waitKey(0);
    return 0;
}
