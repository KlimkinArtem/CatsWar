// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ADamageActor::ADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADamageActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ADamageActor::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ADamageActor::BeginPlay()
{
	Super::BeginPlay();

	Cat_Char = Cast<ACatsWarCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cat_Char == OtherActor)
	{
		Cat_Char->PrintDebugMessage("Begin Overlap", 1.f, FColor::Emerald);

		float RandomScale = FMath::RandRange(0.f, 1.8f);
		Cat_Char->CameraSake(RandomScale);
	}
}

void ADamageActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Cat_Char->PrintDebugMessage("End overlap", 1.f, FColor::Red);
}

