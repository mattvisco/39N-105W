//
//  breathe.h
//  breathPattern
//
//  Created by Matthew Visco on 7/30/16.
//
//

#ifndef Breath_h
#define Breath_h

#include "ofMain.h"
#include "ofxBlur.h"

struct Particle {
    ofPoint pt;
    float color;
};

struct Container {
    float radius;
//    vector<ofPoint> particles;
    vector<Particle> particles;
    float curBrightness;
    float maxBrightness;
};

class Breath {
    
private:
    // CONST
    float STARTRADIUS = 10;
    float STARTBRIGHT = 0;
    float WAITTIME = 5;
    
    ofPoint origin;
    int starterParticles;
    float shrinkStart;
    float curRadius;
    float curBrightness; // TODO: consider removing this var
    float radiusGrow;
    float radiusShrink;
    float brightGrow;
//    float brightShrink;
    float rateGrow;
    float rateShrink;
    float density;
    int maxRadius;
    bool growing;
    bool shrinking;
    float startOfShrinkWait;
    vector<Container> containers;
    
    void reset();
    void grow();
    void shrink();
    
    
    
public:
    ofxBlur blur;
    bool animating;
    bool breathing;
    
    void setup(int width, int height);
    void setBreathe(ofPoint origin, float rateGrow, float rateShrink, float density, int maxRadius);
    void update();
    
    ofEvent<float> breathEnded;
};

#endif /* Breath_h */
