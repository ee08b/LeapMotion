#include <iostream>
#include "Leap.h"
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "draw.hpp"
#include <pthread.h>

class LeapListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
};