// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPC.h"
#include "CatsWarCharacter.h"
#include "Engine/TargetPoint.h"
#include "SpawnTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class CATSWAR_API ASpawnTargetPoint : public ATargetPoint
{
	GENERATED_BODY()


public:

	ASpawnTargetPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, Category="Spawn")
	TArray<TSubclassOf<AActor>> SpawnActors;

	UPROPERTY(EditAnywhere, Category="Spawn parametrs")
	float SpawnTime = 5;

	UPROPERTY(EditAnywhere, Category="Spawn parametrs")
	float Distance = 1000;


private:
	
	ANPC* NPC;
	ACatsWarCharacter* Cat_Char;
	
	void SpawnTimer();

	float CountTime = 0;
	

	FTimerHandle MemberTimerHandle;

	void Spawn();
};
