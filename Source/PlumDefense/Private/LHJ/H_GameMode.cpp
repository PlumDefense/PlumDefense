// Fill out your copyright notice in the Description page of Project Settings.


#include "LHJ/H_GameMode.h"

AH_GameMode::AH_GameMode()
{
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/LHJ/BP_User.BP_User_C'"));
	if (PlayerPawnClass.Succeeded())
		DefaultPawnClass = PlayerPawnClass.Class; 
}
