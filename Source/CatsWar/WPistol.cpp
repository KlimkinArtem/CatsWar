// Fill out your copyright notice in the Description page of Project Settings.


#include "WPistol.h"

// Sets default values
AWPistol::AWPistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = SkeletalMeshComponent;
}

// Called when the game starts or when spawned
void AWPistol::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWPistol::PrintDebugMessage(FString Message, float TimeToDisplay, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, Message);
}

// Called every frame
void AWPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

