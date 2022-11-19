#pragma once
#include <iostream>
#include "Coordinates.h"
#include "Player.h"

//Класс игрового поля, которое имееет различные состояния, добавляя новые состояния можно расширять
//игровые механики. По крайней мере в моей голове это работало так.

class StateGameObject;
class GameObject;
class InvisibleState;
class VoidFieldState;
class WallState;
class PlayerState;

class StateGameObject //базовое состояние ничего не умеет.
{
private:
	std::string name;
public:
	StateGameObject(const std::string& name) : name(name) {}
	std::string GetName()
	{
		return name;
	}
	virtual bool PlayerTransfer(GameObject* GO, Player* pl)
	{
		return false;
	}
	virtual bool ClearPlayer(GameObject* GO)
	{
		return false;
	}
	virtual bool BuildWall(GameObject* GO)
	{
		return false;
	}
	virtual int GetInfo(GameObject* GO) = 0;

};

class GameObject
{
private:

	StateGameObject* state;

public:

	GameObject();

	GameObject(StateGameObject* st)
	{
		state = st;
	}

	~GameObject()
	{
		delete state;
	}
	void SetState(StateGameObject* st)
	{
		state = st;
	}
	std::string GetState()
	{
		return state->GetName();
	}
	int GetInfo()
	{
		return state->GetInfo(this);
	}
	void Hide();

	bool PlayerTransfer(Player* pl)  //перемещение игрока на поле, взвращает False если это невозможно.
	{
		return state->PlayerTransfer(this, pl);
	}
	bool ClearPlayer()    //удаляет игрока с поля
	{
		return state->ClearPlayer(this);
	}
	bool BuildWall()   //строит на поле стену
	{
		return state->BuildWall(this);
	}
};

class InvisibleState : public StateGameObject  //нивидимое состояние. обозначается 0.
{
public:
	InvisibleState() : StateGameObject("Invisible") {}
	virtual int GetInfo(GameObject* GO)
	{
		return 0;
	}
};

class VoidFieldState : public StateGameObject  //состояние пустого поля, может стать стеной, может получить игрока. обозначается 1.
{
public:
	VoidFieldState() : StateGameObject("VoidField") {}
	virtual bool BuildWall(GameObject* GO);
	virtual bool PlayerTransfer(GameObject* GO, Player* pl);
	virtual int GetInfo(GameObject* GO)
	{
		return 1;
	}

};

class WallState : public StateGameObject  //состояние стены не может ничего, игрока не принимает, обозначается 2.
{
public:
	WallState() : StateGameObject("Wall") {}
	virtual int GetInfo(GameObject* GO)
	{
		return 2;
	}
};

class PlayerState : public StateGameObject  //поле занимаемое игроком, может быть им покинуто, обозначается 3.
{
public:
	Player* player;

	PlayerState(Player* pl) : StateGameObject("Player")
	{
		player = pl;
	}
	virtual bool ClearPlayer(GameObject* GO);
	virtual int GetInfo(GameObject* GO)
	{
		return 3;
	}
};

void GameObject ::Hide()
{
	SetState(new InvisibleState());
}

bool VoidFieldState::BuildWall(GameObject* GO)
{
	GO->SetState(new WallState());
	return true;
}
bool VoidFieldState::PlayerTransfer(GameObject* GO, Player* pl)
{
	GO->SetState(new PlayerState(pl));
	return true;
}
bool PlayerState::ClearPlayer(GameObject* GO)
{
	GO->SetState(new VoidFieldState());
	return true;
}

GameObject::GameObject() 
{
	state = new VoidFieldState();
}
