#include "../_ui.hpp"

namespace ui{

    UMat UiSupport::makeMatStereo(UMat toStereo){
        UMat toreturn;
        vector<UMat> mats{toStereo,toStereo};
        cv::hconcat(mats,toreturn);
        return toreturn;
    }

    UMat UiSupport::prepareUiMat(){
        return UMat(cv::Size(960, 1080), CV_8UC3,Scalar(0,0,0));
    }

    UMat UiSupport::resizeIn(UMat input){
        UMat output;
        resize(input, output, Size(960, 1080), InterpolationFlags::INTER_NEAREST);
        return output;
    }

    ///if a non transparent picture is supplied (3 channels), it will be made transparent by using black as a mask
    UMat UiSupport::OverlayBlackMask(UMat input, UMat toOverlay, int x, int y){
        //return input;
        if(input.cols < toOverlay.cols || input.rows < toOverlay.rows){
            cerr << "Wrong size for inout file!!! overlay was bigger" << endl;
        return input;
        }

        UMat toOverlayGRAY, mask;
        vector<UMat> Bands;

        if(toOverlay.channels() == 3){           //non transparent image, use black as mask
            cvtColor(toOverlay,toOverlayGRAY, COLOR_BGR2GRAY);          //picture to greyscale
            threshold(toOverlayGRAY, mask, 0, 255, THRESH_BINARY);      //greyscale to alpha (black or not)
        } else if (toOverlay.channels() == 4){   //transparent, use alpha layer as mask
            split(toOverlay,Bands);                                   // seperate channels
            vector<UMat> channels{ Bands[0],Bands[1],Bands[2] };
            merge(channels,toOverlay);                                       // glue together again
            mask = Bands[3];                                         // png's alpha channel used as mask
        }
        toOverlay.copyTo(input(cv::Rect(x,y,toOverlay.cols, toOverlay.rows)),mask);
        return input;
    }
}