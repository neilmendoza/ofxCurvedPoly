/*
 *  Bezier.h
 *
 *  Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
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
 *  * Neither the name of 16b.it nor the names of its contributors may be used 
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
#pragma once

namespace nm
{
	template<class T>
    class Bezier
	{
	public:
		/*
		 Three control point quadratic Bezier interpolation
		 mu ranges from 0 to 1, start to end of curve
		 */
		T bezier3(double t) const
		{
			if (points.size() != 3) ofLog(OF_LOG_ERROR, "Three and only three control points need to be set.");
			double oneMinusT = 1 - t;
			T p;
			
			p = oneMinusT * oneMinusT * points[0] + 2 * oneMinusT * t * points[1] + t * t * points[2];
			
			return p;
		};
		
		/*
		 Four control point cubic Bezier interpolation
		 mu ranges from 0 to 1, start to end of curve
		 */
		T bezier4(double mu) const
		{
			if (points.size() != 4) ofLog(OF_LOG_ERROR, "Four and only four control points need to be set.");
			double mum1, mum13, mu3;
			T p;
			
			mum1 = 1 - mu;
			mum13 = mum1 * mum1 * mum1;
			mu3 = mu * mu * mu;
			
			p = mum13 * points[0] + 3 * mu * mum1 * mum1 * points[1] + 3 * mu * mu * mum1 * points[2] + mu3 * points[3];
			
			return p;
		};
		
		/*
		 General Bezier curve
		 Number of control points is n+1
		 0 <= mu < 1    IMPORTANT, the last point is not computed
		 */
		T bezier(double mu) const
		{
			int n = points.size() - 1;
			int k,kn,nn,nkn;
			double blend,muk,munk;
			T b;// = {0.0,0.0,0.0};
			
			muk = 1;
			munk = pow(1 - mu, (double)n);
			
			for (k=0;k<=n;k++)
			{
				nn = n;
				kn = k;
				nkn = n - k;
				blend = muk * munk;
				muk *= mu;
				munk /= (1-mu);
				while (nn >= 1)
				{
					blend *= nn;
					nn--;
					if (kn > 1)
					{
						blend /= (double)kn;
						kn--;
					}
					if (nkn > 1)
					{
						blend /= (double)nkn;
						nkn--;
					}
				}
				b += points[k] * blend;
			}
			return b;
		}
        
        unsigned size() const
        {
            return points.size();
        }
		
		void clear()
		{
			points.clear();
		}
		
		void push_back(const T& p)
		{
			points.push_back(p);
		}
		
		T& at(unsigned int i)
		{
			return points[i];
		}
		
		void set(unsigned int i, T value)
		{
			points[i] = value;
		}
		
	private:
		vector<T> points;
	
	};	
}