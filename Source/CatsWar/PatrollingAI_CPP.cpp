// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrollingAI_CPP.h"

#include "DrawDebugHelpers.h"
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
	
	this->CallFunctionByNameWithArguments(TEXT("DamageAnim"), ar, NULL, true);
	
	if(Health <= 0)
	{
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
	bDeath = true;
}


// Called every frame
void APatrollingAI_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Distance = GetDistanceTo(Cat_Char);

	if(!bDeath)
	{
		if(Distance <= 160.f)
		{
			this->CallFunctionByNameWithArguments(TEXT("Attack"), ar, NULL, true);
		}
	}


}

// Called to bind functionality to input
void APatrollingAI_CPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APatrollingAI_CPP::MeleAttack(float Radius, int32 Segments, bool DrawDebug)
{
	FVector Start = GetMesh()->GetSocketLocation(TEXT("AttackSocket"));
	
	
	
	TArray<FHitResult> OutHits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
	
	bool bIsHit = GetWorld()->SweepMultiByChannel(OutHits, Start, Start, FQuat::Identity, ECC_Pawn, Sphere, Params);
	
	if (bIsHit)
	{
		// loop through TArray
		for (auto& Hit : OutHits)
		{
			if (GEngine) 
			{
				// screen log information on what was hit
				
				if(Hit.Actor->ActorHasTag("Player"))
				{
					Cat_Char->GetDamage(DuckDamage);
				}
			}						
		}
	}

	if(DrawDebug)
	{
		DrawDebugSphere(GetWorld(), Start, Radius, Segments, FColor(181,0,0), true, 2, 0, 2);
	}

	//GetWorld()->SweepSingleByChannel();
}
