#ifndef __BOX2D_DEBUG_DRAW_NODE_H__
#define __BOX2D_DEBUG_DRAW_NODE_H__

#include "GLES-Render.h"

// Draws Box2D debug data onto a cocos2d node
// Implementation taken from cocos2d-x Box2DTestBed sample
class Box2DDebugDrawNode : public cocos2d::Node
{
public:
    static Box2DDebugDrawNode *create(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass);
    virtual bool init(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass);
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
private:
    virtual void onDraw(const cocos2d::Mat4 &transform, const uint32_t &flags);
    
    b2World *m_world;
    GLESDebugDraw m_debugDraw;
    cocos2d::CustomCommand m_customCmd;
};

#endif // __BOX2D_DEBUG_DRAW_NODE_H__
