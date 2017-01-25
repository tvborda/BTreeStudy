// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BTreeStudy.h"
#include "BTreeStudyGameMode.h"
#include "BTreeStudyCharacter.h"

ABTreeStudyGameMode::ABTreeStudyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Blueprints/BP_BTreeStudyCharacter.BP_BTreeStudyCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
