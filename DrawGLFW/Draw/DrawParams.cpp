#include <DrawParams.hpp>
#include <stddef.h>  // defines NULL
        
DrawParams *DrawParams::instance = NULL;

DrawParams::DrawParams() {
    instance = NULL;

    rotate_y = 0; 
    rotate_x = 0;
    rotate_z = 0;

    translate_y = 0;
    translate_x = 0;
    translate_z = 0;

    scale = 1;
};

DrawParams* DrawParams::getInstance()
{
    if (instance == NULL) {
        instance = new DrawParams();
    }

    return instance;
}
