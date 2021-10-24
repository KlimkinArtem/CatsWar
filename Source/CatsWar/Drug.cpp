// Fill out your copyright notice in the Description page of Project Settings.


#include "Drug.h"

#include "Components/BoxComponent.h"

// Sets default values
ADrug::ADrug()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CollisionBox);
	

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADrug::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ADrug::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADrug::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACatsWarCharacter* Cat_Char = Cast<ACatsWarCharacter>(OtherActor);

	if(Cat_Char)
	{
		Cat_Char->Drug();
		Destroy();
	}
}

