#include "GameUtils.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

extern int MOVE_FORWARD;
extern int MOVE_LEFT;
extern int MOVE_RIGHT;
extern int MOVE_BACK;
extern int QUIT;
extern int DEBUG_RENDERING_TOGGLE;

namespace Utils
{
	bool enableDebugRendering = true;

	bool getUserInput(ALLEGRO_EVENT_QUEUE* events, shared_ptr<::Ship> player)
	{
		static bool forMovementKeyHeld;
		static bool backMovementKeyHeld;
		static bool leftMovementKeyHeld;
		static bool rightMovementKeyHeld;

		static Point mouseCurPos;
		static ALLEGRO_EVENT event;
		static ALLEGRO_MOUSE_EVENT mouseEvent;
		static ALLEGRO_KEYBOARD_EVENT keyboardEvent;

		while (!al_is_event_queue_empty(events))
		{
			al_get_next_event(events, &event);
			ALLEGRO_EVENT_TYPE ty = event.type;
			if (ty == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				mouseEvent = event.mouse;
				if (mouseEvent.button & 1)
				{
					//printf("mouse click at x: %d y: %d\n", mouseEvent.x, mouseEvent.y);
					shared_ptr<::Projectile> proj = player->fireProj();
					addGameObject(proj);
				}
			}
			//mouse was moved
			if (ty == ALLEGRO_EVENT_MOUSE_AXES)
			{
				mouseEvent = event.mouse;
				mouseCurPos.getCurMousePos(mouseEvent);
				player->setRotationTarget(mouseCurPos);
				//printf("mouse at x: %d y: %d\n", mouseEvent.x, mouseEvent.y);
			}
			//key was pressed
			if (ty == ALLEGRO_EVENT_KEY_DOWN)
			{
				keyboardEvent = event.keyboard;
				if (keyboardEvent.keycode == QUIT)
				{
					return true;
				}
				else if (keyboardEvent.keycode == MOVE_FORWARD)
				{
					forMovementKeyHeld = true;
				}
				else if (keyboardEvent.keycode == MOVE_BACK)
				{
					backMovementKeyHeld = true;
				}
				else if (keyboardEvent.keycode == MOVE_LEFT)
				{
					leftMovementKeyHeld = true;
				}
				else if (keyboardEvent.keycode == MOVE_RIGHT)
				{
					rightMovementKeyHeld = true;
				}
				else if (keyboardEvent.keycode == DEBUG_RENDERING_TOGGLE)
				{
					enableDebugRendering = !enableDebugRendering;
				}
			}
			//player ship movement
			if (forMovementKeyHeld)
			{
				player->moveForward();
			}
			if (backMovementKeyHeld)
			{
				player->moveBack();
			}
			if (leftMovementKeyHeld)
			{
				player->moveLeft();
			}
			if (rightMovementKeyHeld)
			{
				player->moveRight();
			}

			//key was released
			if (ty == ALLEGRO_EVENT_KEY_UP)
			{
				keyboardEvent = event.keyboard;
				if (keyboardEvent.keycode == MOVE_FORWARD)
				{
					forMovementKeyHeld = false;
				}
				else if (keyboardEvent.keycode == MOVE_BACK)
				{
					backMovementKeyHeld = false;
				}
				else if (keyboardEvent.keycode == MOVE_LEFT)
				{
					leftMovementKeyHeld = false;
				}
				else if (keyboardEvent.keycode == MOVE_RIGHT)
				{
					rightMovementKeyHeld = false;
				}
			}
		}
		return false;
	}

	void updateGameState()
	{
		vector<int> objectsToRemove;
		int i = 0;
		//while updating check objects if they should be destroyed
		for (auto GameObjsToUpdate : GameObjects)
		{
			if (GameObjsToUpdate->destroyCondition())
			{
				objectsToRemove.push_back(i);
			}
			else
			{
				GameObjsToUpdate->update();
			}
			i++;
		}

		//reverse iterator since erase invalidates things after the deleted element
		for (auto beg = objectsToRemove.rbegin(), end = objectsToRemove.rend();beg != end;++beg)
		{
			//std::cout << *beg << std::endl;
			GameObjects.erase(GameObjects.begin() + *beg);
		}
		objectsToRemove.clear();
	}

	void renderGameState(Ui& ui)
	{
		//clear existing frame
		al_clear_to_color(BLACK);
		//render new frame
		for (auto GameObjsToRender : GameObjects)
		{
			GameObjsToRender->render();
			if (enableDebugRendering)
			{
				GameObjsToRender->debugRender();
			}
		}
		ui.render();
		al_flip_display();
	}

	void addGameObject(shared_ptr<GameObject> obj)
	{
		GameObjectsToAdd.push_back(obj);
	}
}

