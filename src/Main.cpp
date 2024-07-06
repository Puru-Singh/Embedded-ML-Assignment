#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void stepOne(Mat image, Size size)
{
    //Creating three images for all three of the interpolation techniques
    Mat nearest, linear, cubic;

    //Resizing the image
    resize(image, nearest, size, INTER_NEAREST);
    resize(image, linear, size, INTER_LINEAR);
    resize(image, cubic, size, INTER_CUBIC);
    
    //Saving the resized image
    imwrite("Nearest.png",nearest);
    imwrite("Linear.png",linear);
    imwrite("Cubic.png",cubic);

}

void stepTwo(Mat image, Size size)
{
    //TickMeter object to calculate time for iterations
    TickMeter t1,t2,t3;
    Mat testImg;
    
    //Calculating time for 1000 iterations of Nearest Neighbour Interpolation
    int i=0;
    t1.start();
    for(; i<1000; i++)
    {
        resize(image, testImg, size, INTER_NEAREST);
    }
    t1.stop();

    cout<<"Time taken by Nearest Neighbour = "<<t1.getTimeMilli()<<"ms \n";

    //Calculating time for 1000 iterations of Linear Interpolation
    i=0;
    t2.start();
    for(; i<1000; i++)
    {
        resize(image, testImg, size, INTER_LINEAR);
    }
    t2.stop();

    cout<<"Time taken by Linear Interpolation = "<<t2.getTimeMilli()<<"ms \n";

    //Calculating time for 1000 iterations of Cubic Interpolation
    i=0;
    t3.start();
    for(; i<1000; i++)
    {
        resize(image, testImg, size, INTER_CUBIC);
    }
    t3.stop();

    cout<<"Time taken by Cubic Interpolation = "<<t3.getTimeMilli()<<"ms \n";

}

void customNearest(Mat image, Size size)
{
    Mat res(size, image.type());
    int r,c;

    for(int i=0; i<size.height ; i++)
    {
        for(int j=0; j<size.width ; j++)
        {
            r = static_cast<int>(floor(i/0.5));
            c = static_cast<int>(floor(j/0.5));

            r = min(r, image.rows -1);
            c = min(c, image.cols -1);

            res.at<Vec3b>(i,j) = image.at<Vec3b>(r, c);
        }
    }

    imwrite("CustomNearestResult.png",res);
}

void customLinear(Mat image, Size size)
{
    int r =  static_cast<int>(size.height);
    int c = static_cast<int>(size.width);

    const float y_ratio = static_cast<float>(image.rows)/r;
    const float x_ratio = static_cast<float>(image.cols)/c;

    Mat newImage(r, c, image.type());

    for(int i=0; i<r ; i++)
    {
        int y_s = static_cast<int>(i * y_ratio);

        const float b = (i * y_ratio) - y_s;
        const float b1 = (1 - b);
        Vec3b q;

        for(int j=0; j<c; j++)
        {
            int x_s = static_cast<int>(j * x_ratio);

            const float a = (j * x_ratio) - x_s;
            const float a1 = (1 - a);

            const float a1_cross_b1 = a1 * b1; //weights
            const float a1_cross_b = a1 * b;
            const float a_cross_b1 = a * b1;
            const float a_cross_b = a * b;

            q = (a1_cross_b1 * image.at<Vec3b>(y_s, x_s)) 
                + (a1_cross_b * image.at<Vec3b>(y_s+1, x_s)) 
                + (a_cross_b1 * image.at<Vec3b>(y_s, x_s+1))
                + (a_cross_b * image.at<Vec3b>(y_s+1, x_s+1));

            newImage.at<Vec3b>(i, j) = q;
        }
    }

    imwrite("CustomLinearResult.png",newImage);

}

void stepThree(Mat image, Size size)
{
    //Custom Nearest Neighbour implementation
    customNearest(image, size);

    //Custom Linear implementation
    customLinear(image, size);

    //Custom Cubic implementation


}

int main()
{
    //Importing the input image 
    string inputImg = "input.BMP";
    Mat image = imread(inputImg);

    //Creating a Size object for the new size of the resultant image -> half of original size so /2
    Size size(image.cols/2,image.rows/2);

    //Performing the step one: to resize image using nearest neighbour, linear and cubic interpolation
    stepOne(image, size);
    
    //Measuring performance for 1000 iterations for each of the interpolation methods
    stepTwo(image, size);

    //Re-implementing interpolation functions
    stepThree(image, size);

    return 0;
}
