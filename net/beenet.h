#pragma once

#define PERSON_CLASS 0

#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

namespace beebit {

struct Configuration;

// The BeeBit neural network module. Currently powered by Darknet
class BeeNet {
public:
    
    // Initialize the BeeBit neural network with a config file
    BeeNet(const Configuration *config);
    ~BeeNet();

    // Makes detections given an image frame. Outputs normalized rect coordinates.
    std::vector<cv::Rect> getDetections(const cv::UMat &frame, const cv::Size &screenSize);

    cv::dnn::Net *getNetwork();
private:
    std::vector<cv::Rect> blobToRects(const cv::UMat &frame, const std::vector<cv::Mat> &blob, const cv::Size &finalSize);

    std::unique_ptr<cv::dnn::Net> m_network;
    std::vector<std::string> m_outputLayerNames;

    const cv::Size m_netSize;

    const Configuration *m_config;
};

}