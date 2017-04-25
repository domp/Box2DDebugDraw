# Box2DDebugDraw

**Tested with cocos2d-x v3.14.1 and v3.15rc0**

Simply add the files to your project and include the header:

```
#include "Box2DDebugDrawNode.h"
```

After that, add the node:

```
const float pixelToMeterRatio = 32.0f;
Box2DDebugDrawNode *debugDraw = Box2DDebugDrawNode::create(world, pixelToMeterRatio, true, true, true, true);
this->addChild(debugDraw);
```

Do not forget to remove the node **before** deleting the world:

```
this->removeChild(debugDraw);
```
