// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CatsWarCharacter.h"
#include "GameFramework/Character.h"
#include "PatrollingAI_CPP.generated.h"


UCLASS()
class CATSWAR_API APatrollingAI_CPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APatrollingAI_CPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
	float DuckDamage = 10;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MeleAttack(float Radius, int32 Segments,bool DrawDebug = false);

	UPROPERTY(BlueprintReadOnly)
	bool bDeath = false;

	UFUNCTION()
	void GetDamage(float Damage);

private:

	float Health = 30;
	//FOutputDeviceNull ar;

	void Death();
	
	FOutputDeviceNull ar;
	ACatsWarCharacter* Cat_Char;
	
};
