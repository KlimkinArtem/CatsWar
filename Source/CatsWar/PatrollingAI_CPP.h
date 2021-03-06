// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIPatrollingController.h"
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


	UPROPERTY(EditAnywhere, Category = "Health and damage")
	float DuckDamage = 10;
	
	UPROPERTY(EditAnywhere, Category = "Health and damage")
	float Health = 100;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MeleAttack(float Radius, int32 Segments,bool DrawDebug = false);

	UPROPERTY(BlueprintReadOnly)
	bool bDeath = false;

	UFUNCTION()
	void GetDamage(float Damage);

	UPROPERTY(EditAnywhere)
	float DestroyTime = 30.f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

private:

	
	//FOutputDeviceNull ar;

	void Death();
	
	FOutputDeviceNull ar;
	ACatsWarCharacter* Cat_Char;


	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void DestroyActor();
	float CountTime = 0.f;

	FTimerHandle MemberTimerHandle;

	AAIPatrollingController* Controller;
};

