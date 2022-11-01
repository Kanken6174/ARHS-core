#include "zbar.hpp"

vector<decodedObject> zbarScanner::getFoundElements(){
    const std::lock_guard<std::mutex> lock(decodedObjectsAccessLock);
    return decodedObjects;
}

void zbarScanner::decode(cv::UMat im)
{

    cv::Mat imGray;
    cv::cvtColor(im, imGray, cv::COLOR_BGRA2GRAY);

    Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

    int n = scanner.scan(image);
    const std::lock_guard<std::mutex> lock(decodedObjectsAccessLock);
    decodedObjects.clear();
    for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        decodedObject obj;

        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();
        obj.originalHeight = im.rows;
        obj.originalWidth = im.cols;

        for (int i = 0; i < symbol->get_location_size(); i++)
        {
            obj.location.push_back(cv::Point(symbol->get_location_x(i), symbol->get_location_y(i)));
        }

        decodedObjects.push_back(obj);
    }
}

zbarScanner::zbarScanner()
{
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
}