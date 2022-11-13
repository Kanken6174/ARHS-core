#include "../abstract/pipelineNode.hpp"

class VideoCaptureNode : public PipelineNode
{
public:
    VideoCaptureNode(PipelineNode* _previous){previous = _previous;}
    std::string getName() override {return "video capture node";}
    void beginVideoCapture();
    void stopVideoCapture();
    void snapPicture();
protected:
    cv::VideoWriter* writer;
    void processFrame() override;
    std::atomic_bool capturing = false;
    std::atomic_bool endCapture = false;
    std::string currentRecordingName = "";
};

class VideoCaptureStartCommand : public Command
{
protected:
    VideoCaptureNode *_back;
public:
    VideoCaptureStartCommand(VideoCaptureNode *back) : _back(back) {}
    void Execute() const override {_back->beginVideoCapture();}
};

class VideoCaptureStopCommand : public Command
{
protected:
    VideoCaptureNode *_back;
public:
    VideoCaptureStopCommand(VideoCaptureNode *back) : _back(back) {}
    void Execute() const override {_back->stopVideoCapture();}
};

class PictureSnapCommand : public Command
{
protected:
    VideoCaptureNode *_back;
public:
    PictureSnapCommand(VideoCaptureNode *back) : _back(back) {}
    void Execute() const override {_back->snapPicture();}
};