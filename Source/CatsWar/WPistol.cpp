#include "WPistol.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AWPistol::AWPistol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AWPistol::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Cat_Char = Cast<ACatsWarCharacter>(OtherActor);

	//Cat_Char->Shoot.AddDynamic(this, &AWPistol::Shoot);
}

void AWPistol::Shoot()
{
	PrintDebugMessage("YA LOH BLYAT");
}

void AWPistol::PrintDebugMessage(FString Message, float TimeToDisplay, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, Message);
}

FVector AWPistol::GetSocketLocation()
{
	
	return  SocketLocation;
}

FRotator AWPistol::GetSocketRotation()
{
	return  SocketRotation;
}

void AWPistol::SetSocketTransform()
{

	if(SkeletalMeshComponent->DoesSocketExist("FireSocket"))
	{
		PrintDebugMessage("YES");
	}
	else
	{
		PrintDebugMessage("No");
	}
	//CallFunctionByNameWithArguments(TEXT("SetSocketValue"), ar, NULL, true);
	//PrintDebugMessage("SetSocketTransform finish");
}

void AWPistol::DelegateExample()
{
	PrintDebugMessage("RFEKDNMKMF");
}

void AWPistol::DoSomething()
{
	
}


// Called every frame
void AWPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

