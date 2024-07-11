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

    Mat res(r, c, image.type());

    for(int i=0; i<r ; i++)
    {
        int y_s = static_cast<int>((i) * y_ratio);

        const float b = ((i) * y_ratio) - y_s;
        const float b1 = (1 - b);
        Vec3b q;

        for(int j=0; j<c; j++)
        {
            int x_s = static_cast<int>((j) * x_ratio);

            const float a = ((j) * x_ratio) - x_s;
            const float a1 = (1 - a);

            const float a1_cross_b1 = a1 * b1; //weights
            const float a1_cross_b = a1 * b;
            const float a_cross_b1 = a * b1;
            const float a_cross_b = a * b;
            
            q = Vec3b(saturate_cast<uchar>(a1_cross_b1 * image.at<Vec3b>(y_s, x_s)[0]), saturate_cast<uchar>(a1_cross_b1 * image.at<Vec3b>(y_s, x_s)[1]), saturate_cast<uchar>(a1_cross_b1 * image.at<Vec3b>(y_s, x_s)[2])) 
                + Vec3b(saturate_cast<uchar>(a1_cross_b * image.at<Vec3b>(y_s+1, x_s)[0]), saturate_cast<uchar>(a1_cross_b * image.at<Vec3b>(y_s+1, x_s)[1]), saturate_cast<uchar>(a1_cross_b * image.at<Vec3b>(y_s+1, x_s)[2])) 
                + Vec3b(saturate_cast<uchar>(a_cross_b1 * image.at<Vec3b>(y_s, x_s+1)[0]), saturate_cast<uchar>(a_cross_b1 * image.at<Vec3b>(y_s, x_s+1)[1]), saturate_cast<uchar>(a_cross_b1 * image.at<Vec3b>(y_s, x_s+1)[2]))
                + Vec3b(saturate_cast<uchar>(a_cross_b * image.at<Vec3b>(y_s+1, x_s+1)[0]), saturate_cast<uchar>(a_cross_b * image.at<Vec3b>(y_s+1, x_s+1)[1]), saturate_cast<uchar>(a_cross_b * image.at<Vec3b>(y_s+1, x_s+1)[2]));
            
            res.at<Vec3b>(i, j) = q;
        }
    }

    imwrite("CustomLinearResult.png",res);

}

double W(double t) {
    const double a = -0.5; // You can change this to other values like -0.75 or -1 for different results
    if (std::abs(t) <= 1) {
        return (a + 2) * std::pow(std::abs(t), 3) - (a + 3) * std::pow(std::abs(t), 2) + 1;
    } else if (std::abs(t) <= 2) {
        return a * std::pow(std::abs(t), 3) - 5 * a * std::pow(std::abs(t), 2) + 8 * a * std::abs(t) - 4 * a;
    } else {
        return 0;
    }
}

void customCubic(Mat image, Size size)
{
    int r = size.height;
    int c = size.width;

    Mat res(r, c, image.type());

    for(int k=0; k<image.channels(); k++)
    {
        for(int i=0; i<r; i++)
        {
            for(int j=0; j<c; j++)
            {
                double xm = (i+0.5)*(image.rows/static_cast<double>(r))-0.5;
                double ym = (j+0.5)*(image.cols/static_cast<double>(c))-0.5;

                int xi = static_cast<int>(floor(xm));
                int yi = static_cast<int>(floor(ym));

                double u = xm - xi;
                double v = ym - yi;
            
                
                Vec3d out(0, 0, 0);
                //double out[3];
                for (int n = -1; n <= 2; n++) {
                    for (int m = -1; m <= 2; m++) {
                        int x = xi + n;
                        int y = yi + m;

                        // Boundary check
                        if (x < 0) x = 0;
                        if (x >= image.rows) x = image.rows - 1;
                        if (y < 0) y = 0;
                        if (y >= image.cols) y = image.cols - 1;
                        Vec3b pixel = image.at<Vec3b>(x, y);
                        double weight = W(u - n) * W(v - m);
                        out[0] += pixel[0] * weight;
                        out[1] += pixel[1] * weight;
                        out[2] += pixel[2] * weight;
                    }
                }
                res.at<Vec3b>(i, j) = Vec3b(
                    static_cast<uchar>(out[0]),
                    static_cast<uchar>(out[1]),
                    static_cast<uchar>(out[2])
                );
                
            }
        }
    }
    imwrite("CustomCubicResult.png",res);
}

void stepThree(Mat image, Size size)
{
    //Custom Nearest Neighbour implementation
    customNearest(image, size);

    //Custom Linear implementation
    customLinear(image, size);

    //Custom Cubic implementation
    customCubic(image, size);

}

int main()
{
    //Importing the input image 
    string inputImg = "input.BMP";
    Mat image = imread(inputImg);

    //Creating a Size object for the new size of the resultant image -> half of original size so /2
    Size size(image.cols/2,image.rows/2);

    int opt = 0;
    while(true)
    {
        cout<<"Select the step to run -> \n1. Step one\n2. Step two\n3. Step three\n4. Exit";
        cin>>opt;
        switch(opt)
        {
            case 1: stepOne(image,size);
                    break;
            case 2: stepTwo(image,size);
                    break;
            case 3: stepThree(image,size);
                    break;
            case 4: return 0;
            default: return 0;
        }
    }

}
