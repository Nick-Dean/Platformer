#pragma once
#include "InputComponent.h"
class PlayerInputComponent :
	public InputComponent
{
public:
	PlayerInputComponent();
	~PlayerInputComponent();

	void Update(Input& input, Entity& entity) override;

};

