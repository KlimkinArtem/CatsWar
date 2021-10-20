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
	
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AActor>(SpawnActors[0], GetActorLocation(), GetActorRotation(), SpawnInfo);
}

void ASpawnTargetPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Distance = GetDistanceTo(Cat_Char);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Distance = %f"), Distance));

}
