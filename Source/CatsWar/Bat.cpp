// Fill out your copyright notice in the Description page of Project Settings.


#include "Bat.h"

// Sets default values
ABat::ABat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ABat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

