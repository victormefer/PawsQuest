#include "Save.h"
#include "physics/Rect.h"
#include "components/TransformComponent.h"

Point Save::CheckPoint(500,0);
int Save::fase = 0;

/*************************************************************
 *
 * Atualiza a posicao do novo checkpoint
 *
 *************************************************************/
void Save::SetCheckPoint(Entity* entity)
{
	Rect position = entity->GetComponent<TransformComponent>("TransformComponent")->GetPosition();
	CheckPoint.x = position.x;
	CheckPoint.y = position.y;
	fase = Game::GetInstance().GetCurrentState().number;
}
