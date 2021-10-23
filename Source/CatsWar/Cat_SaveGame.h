// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Cat_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CATSWAR_API UCat_SaveGame : public USaveGame
{
	GENERATED_BODY()


public:
	
	UCat_SaveGame();

	UPROPERTY(EditAnywhere)
	FVector PlayerLocation;
};
