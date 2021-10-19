// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthEnemySystem.h"

#include <Actor.h>

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthEnemySystem::UHealthEnemySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UHealthEnemySystem::BeginPlay()
{
	Super::BeginPlay();

	Cat_Char = Cast<ACatsWarCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Cat_Char->EnemyAttackDelegate.AddDynamic(this, &UHealthEnemySystem::GetDamage);
	
}

void UHealthEnemySystem::GetDamage(float Damage)
{
	Health -= Damage;
	
	if(Health <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString::Printf(TEXT("Actor is death: %s"), *GetName()));
		
	}
}



// Called every frame
void UHealthEnemySystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

