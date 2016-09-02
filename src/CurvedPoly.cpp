/*
 *  CurvedPoly.cpp
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
#include "CurvedPoly.h"

namespace nm
{
    //CurvedPoly::CurvedPoly(float curveAmount) : curveAmount(curveAmount)
    //{
    //}
    
    void CurvedPoly::push_back(const ofVec2f& point)
    {
        points.push_back(point);
        // just add a new bezier every time rather than clearing
        beziers.clear();
    }
    
    void CurvedPoly::push_back(float x, float y)
    {
        push_back(ofVec2f(x, y));
    }
    
    ofVec2f CurvedPoly::sampleAt(unsigned bezierIdx, float t)
    {
        if (points.size() > 2 && beziers.empty()) createBeziers();
        return beziers[bezierIdx].bezier3(t);
    }
    
    ofVec2f CurvedPoly::sampleAt(float t)
    {
        if (points.size() > 2 && beziers.empty()) createBeziers();
        float bezierIdx = floor(t / inverseNumBeziers);
        float bezierT = (t - bezierIdx * inverseNumBeziers) / inverseNumBeziers;
        return beziers[bezierIdx].bezier3(bezierT);
    }
    
    void CurvedPoly::createBeziers(float curveAmount)
    {
        if (points.size() > 2)
        {
            inverseNumBeziers = 1.f / points.size();
            for (unsigned i = 0; i < points.size(); ++i)
            {
                beziers.push_back(Bezier2d());
                beziers.back().push_back(curveAmount * points[i] + (1.f - curveAmount) * points[(i + 1) % points.size()]);
                beziers.back().push_back(points[(i + 1) % points.size()]);
                beziers.back().push_back(curveAmount * points[(i + 1) % points.size()] + (1.f - curveAmount) * points[(i + 2) % points.size()]);
            }
        }
    }
}
