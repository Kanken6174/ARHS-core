#include <zbar.h>
#include <string>
#include <vector>
#include <mutex>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

using namespace zbar;

typedef struct
{
  string type;
  string data;
  vector <cv::Point> location;
  int originalWidth;
  int originalHeight;
} decodedObject;

class zbarScanner{
    private:
    ImageScanner scanner = ImageScanner();
    vector<decodedObject> decodedObjects;
    std::mutex decodedObjectsAccessLock;
    public:
    zbarScanner();
    void decode(cv::UMat im);
    vector<decodedObject> getFoundElements();
};