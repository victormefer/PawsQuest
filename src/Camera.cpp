#include "Camera.h"

Point Camera::pos;
Point Camera::speed;
Entity* Camera::focus;
int Camera::maxWidth, Camera::maxHeight;

/* ************************************************************
 *
 * Novo foco para a camera
 *
 *************************************************************/
void Camera::Follow(Entity* newFocus)
{
	focus = newFocus;
	//pos = focus->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center() + Point(-512, -288/*+64*/);
	pos = Point(0,0);
}

/* ************************************************************
 *
 * Retira foco da camera
 *
 *************************************************************/
void Camera::Unfollow()
{
	focus = NULL;
}

/* ************************************************************
 *
 * Atualiza tela a partir do foco ou do deltatime
 *
 *************************************************************/
void Camera::Update(float dt)
{
	if (focus != NULL)
	{
		//pos = focus->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center() + Point(-512, -300);
		float focusX = focus->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center().x - 512;
		float focusY = focus->GetComponent<TransformComponent>("TransformComponent")->GetPosition().Center().y - 288;

		if (focusX > pos.x + CAMERA_WINDOW_WIDTH_HALF && pos.x < maxWidth - 1034)
			pos.x = focusX - CAMERA_WINDOW_WIDTH_HALF;
		else if (focusX < pos.x - CAMERA_WINDOW_WIDTH_HALF && pos.x > 10)
			pos.x = focusX + CAMERA_WINDOW_WIDTH_HALF;

		if (focusY > pos.y + CAMERA_WINDOW_HEIGHT_HALF && pos.y < maxHeight - 586)
			pos.y = focusY - CAMERA_WINDOW_HEIGHT_HALF;
		else if (focusY < pos.y - CAMERA_WINDOW_HEIGHT_HALF && pos.y > 10)
			pos.y = focusY + CAMERA_WINDOW_HEIGHT_HALF;
	}
	else
	{
		//std::cout << dt << std::endl;
		if (InputManager::GetInstance().IsKeyDown('a'))
		{
			speed = Point(-CAMERA_SPEED * dt, 0);
			pos = pos + speed;
		}
		if (InputManager::GetInstance().IsKeyDown('d'))
		{
			speed = Point(CAMERA_SPEED * dt, 0);
			pos = pos + speed;
		}
		if (InputManager::GetInstance().IsKeyDown('w'))
		{
			speed = Point(0, -CAMERA_SPEED * dt);
			pos = pos + speed;
		}
		if (InputManager::GetInstance().IsKeyDown('s'))
		{
			speed = Point(0, CAMERA_SPEED * dt);
			pos = pos + speed;
		}
	}

//	 std::cout << "CAMERA: " << pos.x << ", " << pos.y << std::endl;
}


/* ************************************************************
 *
 * Setar altura e largura maximas para limitar camera
 *
 *************************************************************/
void Camera::SetMaxWidth(int width)
{
	maxWidth = width;
}

void Camera::SetMaxHeight(int height)
{
	maxHeight = height;
}
