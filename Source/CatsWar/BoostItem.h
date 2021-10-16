// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CatsWarCharacter.h"
#include "GameFramework/Actor.h"
#include "BoostItem.generated.h"

UENUM()
enum EBoostType
{
	NONE_B,
	JUMP_B,
	INVISIBILITY_B,
	SPEED_B
};

UCLASS()
class CATSWAR_API ABoostItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoostItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EBoostType> BoostType = EBoostType::NONE_B;
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

	UPROPERTY(EditAnywhere, Category = Movement)
	float PitchValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float YawValue;

	UPROPERTY(EditAnywhere, Category = Movement)
	float RollValue;

private:

	ACatsWarCharacter* Cat_Char;


};
