#include "WPistol.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AWPistol::AWPistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = SkeletalMeshComponent;


}

// Called when the game starts or when spawned
void AWPistol::BeginPlay()
{
	Super::BeginPlay();
	
	Cat_Char = Cast<ACatsWarCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Cat_Char->Shoot.AddDynamic(this, &AWPistol::Shoot);

}


void AWPistol::Shoot()
{
	
	FVector SocketLocation = SkeletalMeshComponent->GetSocketLocation("FireSocket");
	FRotator SocketRotation = SkeletalMeshComponent->GetSocketRotation("FireSocket");

	//this->CallFunctionByNameWithArguments(TEXT("SpawnEmitter"), ar, NULL, true);
	
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Fire, SocketLocation, SocketRotation, true);

	FActorSpawnParameters SpawnInfo;
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	auto Emitter = GetWorld()->SpawnActor<AActor>(EmitterActor,SocketLocation, SocketRotation, SpawnInfo);
	

	Emitter->AttachToComponent(SkeletalMeshComponent, AttachRules, TEXT("FireSocket"));
}