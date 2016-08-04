//
//  Breath.cpp
//  breathPattern
//
//  Created by Matthew Visco on 7/30/16.
//
//

#include "Breath.h"

void Breath::reset() {
    animating = true;
    blur.begin();
    ofClear(0);
    blur.end();
    containers.clear();
    breathing = false;
    shrinking = false;
    curRadius = STARTRADIUS;
    curBrightness = STARTBRIGHT;
}
void Breath::setup(int width, int height) {
    blur.setup(width, height,10, .2, 4);
    reset();
}

void Breath::setBreathe(ofPoint origin, float rateGrow, float rateShrink, float density, int maxRadius) {
    reset(); // To be safe!
    
    Breath::origin = origin;
    Breath::density = density;
    Breath::maxRadius = maxRadius;
    
    // Clamp grow & shrink
    rateGrow = MIN(1,MAX(0,rateGrow));
    rateShrink = MIN(1,MAX(0,rateShrink));
    Breath::rateGrow = rateGrow;
    Breath::rateShrink = rateShrink;
    
    // Convert rate into brightness, particles, & radius grow/shrink
    radiusGrow = rateGrow * (maxRadius - curRadius);
    brightGrow = rateGrow * (255.0 - curBrightness); // TODO: consider growth to be specific to container
    
    // Enable breathing and growing
    breathing = true;
    growing = true;
}

void Breath::update() {
    if(animating) {
        if(breathing) {
            if(!shrinking) grow();
            else shrink();
        }
    }
}

void makeParticle(ofPoint origin, float radius, float maxRadius, float bright, Container& container) {
    int x = ofRandom(origin.x - radius, origin.x + radius);
    int y = ofRandom(origin.y - radius, origin.y + radius);
    ofPoint pt(x,y);
    Particle particle;
    particle.pt = pt;
    float dist = particle.pt.distance(origin);
    if(dist <= radius) {
        particle.color = MIN(bright,ofMap(dist,0,maxRadius,255,100, true));
        container.particles.push_back(particle);
    }
}

void Breath::grow() {
    if(growing) {
        Container container{curRadius};
        if(containers.size()) container.curBrightness = containers[containers.size()-1].curBrightness;
        else container.curBrightness = STARTBRIGHT;
        container.maxBrightness = ofMap(curRadius,STARTRADIUS,maxRadius,255,100, true);
        container.curBrightness = container.maxBrightness - 50;
        container.particles.clear();
        containers.push_back(container);
    }
    blur.begin();
    ofBackground(0);
    for (auto& container : containers) {
        ofSetColor(container.curBrightness);
        int particleGrow = floor(rateGrow * density * container.radius ); //(container.radius - (container.radius-radiusGrow))
        particleGrow = MAX(1, particleGrow);
        int totalParticles = container.particles.size();
        int particlesToMake = MIN(particleGrow, density*container.radius - totalParticles);
        if(particlesToMake > 0) {
            for(int i = 0; i < particlesToMake; i++) {
                makeParticle(origin, container.radius, maxRadius, curBrightness, container); //MAX(0,container.radius - radiusGrow)
            }
        }
        for(auto& particle : container.particles) {
            ofSetColor(particle.color);
            ofDrawCircle(particle.pt, 1);
            particle.color += brightGrow;
            particle.color = MIN(255, particle.color);
        }
    }
    blur.end();
    curBrightness += brightGrow;
    curBrightness = MIN(255, curBrightness);
    curRadius += radiusGrow;
    curRadius = MIN(maxRadius,curRadius);

    if(growing && curRadius >= maxRadius) {
        growing = false;
        startOfShrinkWait = ofGetElapsedTimef();
    } else if(!growing && ofGetElapsedTimef() - startOfShrinkWait > WAITTIME) {
        shrinking = true;
    }
}

void cleanUp(vector<Container>& containers) {
    vector<Container> newContainers;
    for(auto& container : containers) {
        if(container.particles.size()) newContainers.push_back(container);
    }
    containers = newContainers;
}
                             
void Breath::shrink() {
    blur.begin();
    ofBackground(0);
    for (auto& container : containers) {
        int totalParticles = container.particles.size();
        int particleShrink = floor(rateShrink * density * container.radius);
        particleShrink = MAX(2, particleShrink);
        if(totalParticles > 0) {
            int particlesToRemove = MIN(particleShrink, totalParticles);
            container.particles.erase(container.particles.begin(), container.particles.begin() + particlesToRemove);
            for(auto& particle : container.particles) {
                ofSetColor(particle.color);
                ofDrawCircle(particle.pt, 1);
            }
        }
    }
    cleanUp(containers);
    blur.end();
    
    if(!containers.size()) {
        reset();
        float time = ofGetElapsedTimef();
        ofNotifyEvent(breathEnded, time, this);
    }
}