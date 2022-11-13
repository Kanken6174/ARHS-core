#include "videoCaptureNode.hpp"

void VideoCaptureNode::processFrame()
{
    if (!capturing || writer == nullptr)
        return;

    if (endCapture)
    {
        writer = nullptr;
        endCapture = false;
        capturing = false;
        return;
    }

    cv::UMat currentFrame = previous->getOutput();

    if (currentFrame.empty())
        return;

    writer->write(currentFrame);
}

void VideoCaptureNode::beginVideoCapture()
{
    if(capturing) return;
    time_t now = time(0);
    currentRecordingName = ctime(&now);
    currentRecordingName += ".avi";
    writer = new VideoWriter(currentRecordingName, CV_FOURCC('M', 'J', 'P', 'G'), fpsLimit, Size(640, 480));
    capturing = true;
}

void VideoCaptureNode::stopVideoCapture()
{
    endCapture = true;
}

void VideoCaptureNode::snapPicture()
{
    time_t now = time(0);
    std::string snapName = ctime(&now);
    snapName += ".png";
    cv::UMat currentFrame = previous->getOutput();
    if (!currentFrame.empty())
        imwrite(snapName, currentFrame);
}