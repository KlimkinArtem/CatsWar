// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingAI_CPP.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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


	Cat_Char = Cast<ACatsWarCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Cat_Char->EnemyAttackDelegate.AddDynamic(this, &APatrollingAI_CPP::GetDamage);
}

void APatrollingAI_CPP::GetDamage(float Damage)
{
	Health -= Damage;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString::Printf(TEXT("Actor is death: %s"), *GetName()));
	if(Health <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, FString::Printf(TEXT("Actor is death: %s"), *GetName()));
		//GetOwner()->CallFunctionByNameWithArguments(TEXT("Physics"), ar, NULL, true);
		//GetOwner()->Destroy();
		Death();
	}
}

void APatrollingAI_CPP::Death()
{
	GetCharacterMovement()->DisableMovement();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetAllBodiesPhysicsBlendWeight(1.f, false);
}


// Called every frame
void APatrollingAI_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Distance = GetDistanceTo(Cat_Char);


	if(Distance <= 160.f)
	{
		this->CallFunctionByNameWithArguments(TEXT("Attack"), ar, NULL, true);
	}

}

// Called to bind functionality to input
void APatrollingAI_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

