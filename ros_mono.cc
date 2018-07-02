/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<string>
#include<thread>

#include<ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// using namespace std;
using namespace cv;
// #include<opencv2/core/core.hpp>

using namespace std;

class ImageGrabber
{
public:
    ImageGrabber(){}

    // void GrabImage(const sensor_msgs::ImageConstPtr& msg);
    void GrabImage(const sensor_msgs::CompressedImageConstPtr& msg);

    // ORB_SLAM2::System* mpSLAM;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Mono");
    ros::start();

    
    ImageGrabber igb;

    ros::NodeHandle nodeHandler;
    std::cout << "start:  " << std::endl;
    ros::Subscriber sub = nodeHandler.subscribe("/camera1/image_color/compressed", 1, &ImageGrabber::GrabImage, &igb);

    ros::spin();

  
    ros::shutdown();

    return 0;
}

// void ImageGrabber::GrabImage(const sensor_msgs::ImageConstPtr& msg)
void ImageGrabber::GrabImage(const sensor_msgs::CompressedImageConstPtr& msg)
{
    //////////////*****************////////////
    std::cout << "inside 1:  " << std::endl;
    cv::Mat image = cv::imdecode(cv::Mat(msg->data),1);//convert compressed image data to cv::Mat
    cv::imwrite("test.bmp", image);
    std::cout << "inside 2:  " << std::endl;
    //cv::waitKey(10);
    //////////////*****************////////////
#if 0
    // Copy the ros image message to cv::Mat.
    cv_bridge::CvImageConstPtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat image = cv_ptr->image;
    std::cout << "ok " << std::endl;
    cv::imwrite("test.jpg", image);
    // mpSLAM->TrackMonocular(cv_ptr->image,cv_ptr->header.stamp.toSec());
#endif
}


