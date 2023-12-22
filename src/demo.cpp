#include "../sgg/include/graphics.h"

void update(float ms) {

}

void draw() {
    
}

int main()
{
    graphics::createWindow(1200, 600, "Tutorial");

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(1000, 500);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();

    return 0;
}
