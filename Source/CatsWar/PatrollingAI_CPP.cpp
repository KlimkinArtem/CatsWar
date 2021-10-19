// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingAI_CPP.h"

// Sets default values
APatrollingAI_CPP::APatrollingAI_CPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatrollingAI_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrollingAI_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APatrollingAI_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

