#pragma once
#include "Module.h"
#include "Globals.h"
#include"p2List_Extended.h"
#include "Box2D/Box2D/Box2D.h"

class b2World;
class b2Body;
struct b2Vec2;
typedef float float32;
typedef int int32;

class BodyClass
{
public:
	BodyClass();
	~BodyClass();

	b2Body* body;
	int spriteSheet;
	SDL_Rect section;
	bool needs_Center = true;
	int pivotX = 0, pivotY = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


	int GetPositionPixels_X();
	int GetPositionPixels_Y();

	float GetRotation();

	b2Vec2 GetPositionMeters();
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	BodyClass Create_Circle(int _x, int _y, float meter_radius, b2BodyType type, float density, int sheet = -1, SDL_Rect sec = {0, 0, 0, 0}, SDL_RendererFlip flip = SDL_FLIP_NONE);
	BodyClass Create_Rectangle(SDL_Rect size, int type, float density, int sheet = -1, SDL_Rect sec = {0, 0, 0, 0}, SDL_RendererFlip flip = SDL_FLIP_NONE);
	BodyClass Create_Chain(float, float, int[], int, b2Vec2[], int sheet = -1, SDL_Rect sec = { 0, 0, 0, 0 }, int isDynamic = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	BodyClass Create_Poly(float, float, int[], int, b2Vec2[], int sheet = -1, SDL_Rect sec = { 0, 0, 0, 0 }, int type = 1, SDL_RendererFlip flip = SDL_FLIP_NONE, float density = 1.0f);

	b2RevoluteJoint* Create_Revolute_Joint(b2Fixture*, b2Fixture*, float);

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	float32 timeStep = 1.0f / 60.f;
	int32 velocityIterations = 12;
	int32 positionIterations = 10;

public:
	p2List_Extended<BodyClass> world_body_list;
	void DestroyBody(b2Body*);
	bool MoveObjectSmooth(b2Vec2* position, b2Vec2 target_point,float32 speed);
	b2World *world = nullptr;

private:
	b2MouseJoint* mouse_joint;
	b2Body* jointBody;
	b2Body* ground;
};


