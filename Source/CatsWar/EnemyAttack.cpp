// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttack.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyAttack::UEnemyAttack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UEnemyAttack::BeginPlay()
{
	Super::BeginPlay();


	Cat_Char = Cast<ACatsWarCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}


// Called every frame
void UEnemyAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float Distance = GetOwner()->GetDistanceTo(Cat_Char);


	if(Distance <= 160.f)
	{
		GetOwner()->CallFunctionByNameWithArguments(TEXT("Attack"), ar, NULL, true);
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString::Printf(TEXT("Distance: %f"), Distance));

	}
}

