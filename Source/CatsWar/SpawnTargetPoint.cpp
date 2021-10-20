// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTargetPoint.h"

#include "Kismet/GameplayStatics.h"

ASpawnTargetPoint::ASpawnTargetPoint()
{
	
}

void ASpawnTargetPoint::BeginPlay()
{
	Super::BeginPlay();
	
	Cat_Char = Cast<ACatsWarCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	

	Spawn();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ASpawnTargetPoint::SpawnTimer, 1.0f, true, 0.f);
}

void ASpawnTargetPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}


void ASpawnTargetPoint::SpawnTimer()
{
	
	if (CountTime == SpawnTime)
	{
		CountTime = 0;
		Spawn();
	}
	CountTime++;
	FString CountTimeString = FString::FromInt(CountTime);
	
	
}

void ASpawnTargetPoint::Spawn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Distance = %f"), GetDistanceTo(Cat_Char)));
	if(GetDistanceTo(Cat_Char) <= Distance) return;
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AActor>(SpawnActors[0], GetActorLocation(), GetActorRotation(), SpawnInfo);



	
}

