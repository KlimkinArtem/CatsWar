// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = SkeletalMeshComponent;
	//CollisionBox->SetupAttachment(RootComponent);
	


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(RootComponent);
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AQuestNPC::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACatsWarCharacter* Cat = Cast<ACatsWarCharacter>(OtherActor);
	
	if(Cat)
	{
		//UAudioComponent* AudioComponent = UGameplayStatics::SpawnSound2D(this, Dialogue[0], 1);
		UAudioComponent* AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, Dialogue[0], GetActorLocation(),
			FRotator::ZeroRotator, 1.f, 1.f, 0.0f, AttenuationSettings, nullptr, true);

		Cat->DisablePlayerInput(5.f);

	}
}
