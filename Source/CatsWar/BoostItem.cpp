// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostItem.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABoostItem::ABoostItem()
{
	PrimaryActorTick.bCanEverTick = true;


	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CollisionBox);
	

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABoostItem::OnOverlapBegin);

	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;
}

// Called when the game starts or when spawned
void ABoostItem::BeginPlay()
{
	Super::BeginPlay();

	Cat_Char = Cast<ACatsWarCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ABoostItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);
	FQuat QuatRotation = FQuat(NewRotation);
	StaticMesh->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ABoostItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cat_Char == OtherActor)
	{
		if(Cat_Char->bBoost)
		{
			return;
		}
		Cat_Char->PrintDebugMessage("Picup boost object", 1.f, FColor::Emerald);

		
		
		switch (BoostType)
		{
			case JUMP_B:
				Cat_Char->JumpBoost();
				break;
			case INVISIBILITY_B:
				Cat_Char->InvisibilityBoost();
				break;
			case SPEED_B:
				Cat_Char->SpeedBoost();
				break;
		}

		Destroy();
		
	}
}

