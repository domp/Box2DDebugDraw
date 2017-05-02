/****************************************************************************
Copyright (c) 2017 domp http://github.com/domp
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/

#ifndef __B2_DEBUG_DRAW_NODE_H__
#define __B2_DEBUG_DRAW_NODE_H__

#include "GLES-Render.h"

// Draws Box2D debug data onto a cocos2d node
// Implementation taken from cocos2d-x Box2DTestBed sample
class B2DebugDrawNode : public cocos2d::Node
{
public:
    static B2DebugDrawNode *create(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass);
    virtual bool init(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass);
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
private:
    virtual void onDraw(const cocos2d::Mat4 &transform, const uint32_t &flags);
    
    b2World *m_world;
    GLESDebugDraw m_debugDraw;
    cocos2d::CustomCommand m_customCmd;
};

#endif // __B2_DEBUG_DRAW_NODE_H__
