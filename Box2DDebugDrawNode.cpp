#include "Box2DDebugDrawNode.h"

USING_NS_CC;

Box2DDebugDrawNode *Box2DDebugDrawNode::create(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass)
{
    Box2DDebugDrawNode *node = new (std::nothrow) Box2DDebugDrawNode();
    if (node && node->init(world, ratio, shape, joint, aabb, centerOfMass))
    {
        node->autorelease();
        return node;
    }
    
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool Box2DDebugDrawNode::init(b2World *world, const float &ratio, const bool &shape, const bool &joint, const bool &aabb, const bool &centerOfMass)
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

void Box2DDebugDrawNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Node::draw(renderer, transform, flags);
    
    m_customCmd.init(_globalZOrder, transform, flags);
    m_customCmd.func = CC_CALLBACK_0(Box2DDebugDrawNode::onDraw, this, transform, flags);
    renderer->addCommand(&m_customCmd);
}

void Box2DDebugDrawNode::onDraw(const Mat4 &transform, const uint32_t &flags)
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
