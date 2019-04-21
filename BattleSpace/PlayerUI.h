#pragma once
#include "UI.h"

class Player;
class PlayerUI :
	public UI
{
public:
	PlayerUI(Player *player, STAGE_KIND stage);
	virtual ~PlayerUI();

private:
	Player *player = nullptr;
	Texture *heart = nullptr;
	Texture *exp = nullptr;
	Texture *expGage = nullptr;
	STAGE_KIND stage;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

