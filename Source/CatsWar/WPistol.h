// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "CatsWarCharacter.h"
#include "GameFramework/Actor.h"
#include "Misc/OutputDeviceNull.h"
#include "WPistol.generated.h"


UCLASS()
class CATSWAR_API AWPistol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWPistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void Shoot();

	void PrintDebugMessage(FString Message = "Hello", float TimeToDisplay = 1.f, FColor Color = FColor::Red);

	FVector GetSocketLocation();
	FRotator GetSocketRotation();
	void SetSocketTransform();


	void DelegateExample();

	static void DoSomething();
private:
	FOutputDeviceNull ar;


	ACatsWarCharacter* Cat_Char;
};
