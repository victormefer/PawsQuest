#ifndef CAMERA_H
#define CAMERA_H

#include "entities/Entity.h"
#include "components/TransformComponent.h"
#include "managers/InputManager.h"

#define CAMERA_SPEED 800 // pixels per second
#define CAMERA_WINDOW_WIDTH_HALF 40 // PIXELS
#define CAMERA_WINDOW_HEIGHT_HALF 80 // PIXELS

class Camera
{
public:
	static void Follow(Entity* newFocus);
	static void Unfollow();
	static void Update(float dt);
	static void SetMaxWidth(int width);
	static void SetMaxHeight(int height);

	static Point pos;
	static Point speed;

private:
	static Entity* focus;
	static int maxWidth, maxHeight;

};

#endif
