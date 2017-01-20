#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
         "Usage:\n"
         "./houghcircles <image_name>, Default is ../data/board.jpg\n" << endl;
}

void detect_circle(Mat& img,
                   vector<Vec3f>& circles,
                   const unsigned int min_radius,
                   const unsigned int max_radius) {
    Mat cimg;
    medianBlur(img, img, 5);
    cvtColor(img, cimg, COLOR_GRAY2BGR);

    HoughCircles(img, circles, HOUGH_GRADIENT, 1, 10,
                 100, 30, min_radius, max_radius
                );

    std::cout << "I've got " << circles.size() << " circles" << std::endl;
    img = cimg;
}

int main(int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv,
                                 "{help h ||}{@image|../data/board.jpg|}"
                                );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    string filename = parser.get<string>("@image");
    if (filename.empty())
    {
        help();
        cout << "no image_name provided" << endl;
        return -1;
    }
    Mat img = imread(filename, 0);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    const unsigned int min_radius = atoi(argv[2]);
    const unsigned int max_radius = atoi(argv[3]);
    vector<Vec3f> circles;

    detect_circle(img, circles, min_radius, max_radius);

    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( img, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( img, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }

    imshow("detected circles", img);
    waitKey();
    return 0;
}
