#include "subNodes.hpp"
#include "../../../ui/support/UiSupport.hpp"

ZbarOverlayer::ZbarOverlayer(zbarScanner *backend) : localScanner(backend)
{
}

void ZbarOverlayer::processFrame(cv::UMat &input, cv::Point2d &cursorPos)
{
    vector<decodedObject> objects = localScanner->getFoundElements();

    if(objects.size() > 0){
        float ogH = objects.at(0).originalHeight;
        float ogW = objects.at(0).originalWidth;
        cv::UMat toWriteOn = cv::UMat(cv::Size(ogW,ogH), CV_8UC3, cv::Scalar(0, 0, 0));

    // Loop over all decoded objects
    for (decodedObject deo : objects)
    {
        vector<cv::Point> points = deo.location;
        vector<cv::Point> hull;

        // If the points do not form a quad, find convex hull
        if (points.size() > 4)
            cv::convexHull(points, hull);
        else
            hull = points;

        // Number of points in the convex hull
        int n = hull.size();

        for (int j = 0; j < n; j++)
        {
            cv::line(toWriteOn, hull[j], hull[(j + 1) % n], cv::Scalar(255, 0, 0), 3);
        }
            cv::Point pos = cv::Point(deo.location.at(0).x*(960/ogH),deo.location.at(0).y*(1080/ogW));
            cv::putText(input, cv::format("%s", deo.data.c_str()), pos, cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255), 1, 8, false);
    }
    cv::UMat toOverlay = UiSupport::resizeIn(toWriteOn);
    input = UiSupport::OverlayBlackMask(toOverlay, input);
    }
}