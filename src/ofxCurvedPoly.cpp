/*
 *  ofxCurvedPoly.cpp
 *
 *  Copyright (c) 2015, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of Neil Mendoza nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */
#include "ofxCurvedPoly.h"

namespace itg
{
    ofxCurvedPoly::ofxCurvedPoly(float curveAmount) : curveAmount(curveAmount)
    {
    }
    
    void ofxCurvedPoly::push_back(const ofVec2f& point)
    {
        points.push_back(point);
        // just add a new bezier every time rather than clearing
        beziers.clear();
    }
    
    unsigned ofxCurvedPoly::getNumBeziers()
    {
        if (points.size() > 2 && beziers.empty()) createBeziers();
        return beziers.size();
    }
    
    ofVec2f ofxCurvedPoly::sampleAt(unsigned bezierIdx, float t)
    {
        return beziers[bezierIdx].bezier3(t);
    }
    
    void ofxCurvedPoly::createBeziers()
    {
        if (points.size() > 2)
        {
            for (unsigned i = 0; i < points.size(); ++i)
            {
                beziers.push_back(Bezier2D());
                beziers.back().push_back(curveAmount * points[i] + (1.f - curveAmount) * points[(i + 1) % points.size()]);
                beziers.back().push_back(points[(i + 1) % points.size()]);
                beziers.back().push_back(curveAmount * points[(i + 1) % points.size()] + (1.f - curveAmount) * points[(i + 2) % points.size()]);
                
                //beziers.back().push_back(.5f * (points[i] + points[(i + 1) % points.size()]));
                //beziers.back().push_back(points[(i + 1) % points.size()]);
                //beziers.back().push_back(.5f * (points[(i + 1) % points.size()] + points[(i + 2) % points.size()]));
                
                
                /*for (unsigned j = 0; j < 100; ++j)
                {
                    curve.push_back(bezier.bezier3(j / 99.f));
                }*/
            }
        }
    }
}
