// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	//for (int i = 10; i <= SpawnTargets.Num(), i++);

	for (auto& Target : SpawnTargets)
	{
		//SpawnTargetPoint = Cast<ASpawnTargetPoint>(Target);
		//FVector loc = SpawnTargetPoint->GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health: %s"), *loc.ToString()));

	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Vehicle"))
	{
		Death();
	}
}

float ANPC::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Health -= Damage;
	if(Health <= 0)
	{
		Death();
	}

	GetCharacterMovement()->MaxWalkSpeed = 800.f;
	
	return Damage;
}

void ANPC::Death()
{
	GetCharacterMovement()->DisableMovement();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetAllBodiesPhysicsBlendWeight(1.f, false);

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ANPC::DestroyActor, 1.0f, true, 0.f);
}

void ANPC::DestroyActor()
{
	
	if (CountTime == DestroyTime)
	{
		Destroy();
		GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	}
	CountTime++;
	FString CountTimeString = FString::FromInt(CountTime);
	
	
}

