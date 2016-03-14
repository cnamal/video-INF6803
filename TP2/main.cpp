//
// Created by namalgac on 3/12/16.
//

#include "FollowVisibleFace.h"
#include "GrayFrameTransformation.h"
#include "HSVFrameTransformation.h"
#include "MeanShift.h"
#include "ParticleFilter.h"
#include "PFMS.h"
#include "JPSequence.h"
#include <string>

#define VIDEO 0
#define HSV 1
#define PART 3

int main() {


#if VIDEO
    FollowVisibleFace video;
#else
    JPSequence video;
#endif

#if HSV
    HSVFrameTransformation trans;
#else
    GrayFrameTransformation trans;
#endif

    switch (PART) {
        case 1: {
            ParticleFilter filter(video, trans);
            filter.track();
        }
            break;
        case 2: {
            MeanShift meanShift(video, trans);
            meanShift.track();
        }
            break;
        default: {
            PFMS pfms(video, trans);
            pfms.track();
        }
    }
    return 0;
}
