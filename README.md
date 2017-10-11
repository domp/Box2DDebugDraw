# Box2DDebugDraw

**Tested with cocos2d-x v3.14.1, v3.15 & v3.16**

Simply add the files to your project and include the header:

```
#include "B2DebugDrawNode.h"
```

After that, add the node:

```
const float pixelToMeterRatio = 32.0f;
B2DebugDrawNode *debugDraw = B2DebugDrawNode::create(world, pixelToMeterRatio, 
                                                     true, // Draw shape
                                                     true, // Draw joint
                                                     true, // Draw aabb
                                                     true); // Draw center of mass
this->addChild(debugDraw);
```

Do not forget to remove the node **before** deleting the world:

```
this->removeChild(debugDraw);
```
