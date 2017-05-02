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

#include "B2DebugDrawNode.h"

USING_NS_CC;

B2DebugDrawNode *B2DebugDrawNode::create(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass)
{
    B2DebugDrawNode *node = new (std::nothrow) B2DebugDrawNode();
    if (node && node->init(world, ratio, shape, joint, aabb, centerOfMass))
    {
        node->autorelease();
        return node;
    }
    
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool B2DebugDrawNode::init(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass)
{
    // Super init
    if (!Node::init())
    {
        return false;
    }
    
    m_world = world;
    m_debugDraw = GLESDebugDraw(ratio);
    
    uint32 flags = 0;
    if (shape) flags += b2Draw::e_shapeBit;
    if (joint) flags += b2Draw::e_jointBit;
    if (aabb) flags += b2Draw::e_aabbBit;
    if (centerOfMass) flags += b2Draw::e_centerOfMassBit;
    m_debugDraw.SetFlags(flags);
    
    m_world->SetDebugDraw(&m_debugDraw);
    
    return true;
}

void B2DebugDrawNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Node::draw(renderer, transform, flags);
    
    m_customCmd.init(_globalZOrder, transform, flags);
    m_customCmd.func = CC_CALLBACK_0(B2DebugDrawNode::onDraw, this, transform, flags);
    renderer->addCommand(&m_customCmd);
}

void B2DebugDrawNode::onDraw(const Mat4 &transform, const uint32_t &flags)
{
    Director *director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
    
    m_world->DrawDebugData();
    
    CHECK_GL_ERROR_DEBUG();
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
