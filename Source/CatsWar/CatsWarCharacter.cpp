// Copyright Epic Games, Inc. All Rights Reserved.

#include "CatsWarCharacter.h"

#include "DrawDebugHelpers.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Misc/OutputDeviceNull.h"

//////////////////////////////////////////////////////////////////////////
// ACatsWarCharacter

ACatsWarCharacter::ACatsWarCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 450.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	//USkeletalMeshComponent* Mesh = GetMesh();
}

void ACatsWarCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACatsWarCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ACatsWarCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings 
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Debug", IE_Pressed, this, &ACatsWarCharacter::Debug);
	
	PlayerInputComponent->BindAction("Hand", IE_Pressed, this, &ACatsWarCharacter::Hand);
	PlayerInputComponent->BindAction("Bat", IE_Pressed, this, &ACatsWarCharacter::Bat);
	PlayerInputComponent->BindAction("Pistol", IE_Pressed, this, &ACatsWarCharacter::Pistol);
	
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACatsWarCharacter::Attack);

	PlayerInputComponent->BindAction<FMaxSpeedDelegate>("MaxSpeed", IE_Pressed, this, &ACatsWarCharacter::SetMaxWalkSpeed, 600.f);
	PlayerInputComponent->BindAction<FMaxSpeedDelegate>("MaxSpeed", IE_Released, this, &ACatsWarCharacter::SetMaxWalkSpeed, 150.f);
	
	PlayerInputComponent->BindAction<FShakeDelegate>("Shake", IE_Pressed, this, &ACatsWarCharacter::CameraSake, 1.0f);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACatsWarCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACatsWarCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACatsWarCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACatsWarCharacter::LookUpAtRate);


}



void ACatsWarCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACatsWarCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACatsWarCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACatsWarCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ACatsWarCharacter::PrintDebugMessage(FString Message, float TimeToDisplay, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Color, Message);
}

void ACatsWarCharacter::CameraSake(float Scale)
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CamShake, Scale);
}

void ACatsWarCharacter::SetMaxWalkSpeed(float Speed)
{
	if(bMaxSpeed)
	{
		return;
	}
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void ACatsWarCharacter::JumpBoost()
{
	Boost(EBoost::JUMP);
	
}

void ACatsWarCharacter::InvisibilityBoost()
{
	Boost(EBoost::INVISIBILITY);
}

void ACatsWarCharacter::SpeedBoost()
{
	Boost(EBoost::SPEED);
}


void ACatsWarCharacter::Boost(EBoost BOOST)
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ACatsWarCharacter::RepeatingFunction, 1.0f, true, 0.f);
	
	bBoost = true;
	//float RandomVelocity = FMath::RandRange(800.f, 1200.f);
	
	switch (BOOST)
	{
		case JUMP:
			GetCharacterMovement()->JumpZVelocity = 1200.f;   //RandomVelocity;
			//GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ACatsWarCharacter::RepeatingFunction, 1.0f, true, 0.f);
			break;
		case INVISIBILITY:
			this->CallFunctionByNameWithArguments(TEXT("SetInviseMaterial"), ar, NULL, true);
			bWasInvisible = true;
			break;
		case SPEED:
			SetMaxWalkSpeed(1200.f);
			bMaxSpeed = true;
			break;
			
	}

}

void ACatsWarCharacter::Hand()
{
	AttackType = HAND;

	if(IsValid(Weapon))
	{
		Weapon->Destroy();
	}
	
	bPistolMode = false;
	PrintDebugMessage("Hand");
	
	
	bUseControllerRotationYaw = false;
	Unzoom();


}

void ACatsWarCharacter::Bat()
{
	AttackType = BAT;
	
	if(IsValid(Weapon) && Weapon->ActorHasTag(TEXT("BAT")))
	{
		PrintDebugMessage("Bat no spawn");
		return;
	}
	
	SpawnWeapon("BatSocket", 0);

	
	bUseControllerRotationYaw = false;
	Unzoom();
}

void ACatsWarCharacter::Pistol()
{
	AttackType = PISTOL;
	
	if(IsValid(Weapon) && Weapon->ActorHasTag(TEXT("PISTOL")))
	{
		PrintDebugMessage("Pistol no spawn");
		return;
	}
	
	
	SpawnWeapon("PistolSocket", 1);
	
	Zoom();
	bPistolMode = true;
	bUseControllerRotationYaw = true;
}

void ACatsWarCharacter::SpawnWeapon(FString SocketName, int32 WeaponIndex)
{
	
	if(IsValid(Weapon))
	{
		Weapon->Destroy();
	}
	
	
	bPistolMode = false;
	
	FVector Location = GetMesh()->GetSocketLocation(*SocketName);
	FRotator Rotation = GetMesh()->GetSocketRotation(*SocketName);
	
	FActorSpawnParameters SpawnInfo;
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	
	Weapon = GetWorld()->SpawnActor<AActor>(Weapons[WeaponIndex],Location, Rotation, SpawnInfo);
	
	Weapon->AttachToComponent(GetMesh(), AttachRules, *SocketName);

	PrintDebugMessage("SpawnWeapon");
}




void ACatsWarCharacter::PistolAttack()
{
	Shoot.Broadcast();

	FVector Start = FollowCamera->GetComponentLocation();
	FVector FollowCameraForwardVector = FollowCamera->GetForwardVector();

	FHitResult OutHit;
	
	FVector End = ((FollowCameraForwardVector * 3000.f) + Start);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 3, 0, 2);

	bool bIsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_PhysicsBody, CollisionParams);
	
	if(bIsHit)
	{
		if(OutHit.GetActor()->GetClass()->IsChildOf(ACatsWarCharacter::StaticClass()))
		{
			if(OutHit.BoneName == "Head")
			{
				//HealthDelegate.Broadcast();
				
			}else
			{
				//HealthDelegate.Broadcast();
			}
			
			
		}

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Bone is: %s"), *OutHit.GetActor()->GetName()));

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("The Component Being Hit is: %s"), *OutHit.GetActor()->GetName()));
	}
}

void ACatsWarCharacter::MeleAttack(float Radius, int32 Segments)
{
	FVector Start = GetMesh()->GetSocketLocation(TEXT("BatAttack"));
	
	
	//DrawDebugSphere(GetWorld(), Start, Radius, Segments, FColor(181,0,0), true, 2, 0, 2);
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
				
				if(Hit.Actor->ActorHasTag("Enemy"))
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *Hit.Actor->GetName()));
					EnemyAttackDelegate.Broadcast(BatDamage);
				}
			}						
		}
	}

	//GetWorld()->SweepSingleByChannel();
}

void ACatsWarCharacter::GetDamage(float Damage)
{
	Health -= Damage;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health: %f"), Health));
	CameraSake(1);
	if(Health <= 0.f)
	{
		Death();
	}
}


void ACatsWarCharacter::Death()
{
	GetCharacterMovement()->DisableMovement();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetAllBodiesPhysicsBlendWeight(1.f, false);
}

void ACatsWarCharacter::Attack()
{
	
	switch (AttackType)
	{
	case HAND:
		CallFunctionByNameWithArguments(TEXT("HandAttackAnim"), ar, NULL, true);
		break;
	case BAT:
		CallFunctionByNameWithArguments(TEXT("BatAttackAnim"), ar, NULL, true);
		break;
	case PISTOL:
		CallFunctionByNameWithArguments(TEXT("PistolAttackAnim"), ar, NULL, true);
		PistolAttack();
		break;
	}
	
}


void ACatsWarCharacter::Zoom()
{
	CameraBoom->SetRelativeLocation(FVector(0.f, 100.f, 60.f));
	bZoom = true;
	this->CallFunctionByNameWithArguments(TEXT("ZoomCamera"), ar, NULL, true);
}

void ACatsWarCharacter::Unzoom()
{
	if(bZoom)
	{
		CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
		bZoom = false;
		this->CallFunctionByNameWithArguments(TEXT("UnzoomCamera"), ar, NULL, true);
		
	}
	
}



void ACatsWarCharacter::RepeatingFunction()
{
	
	if (CountTime == TimerEndTime)
	{
		RestToDefaultParameters();
		GetWorldTimerManager().ClearTimer(MemberTimerHandle);
	}
	CountTime++;
	FString CountTimeString = FString::FromInt(CountTime);
	PrintDebugMessage(CountTimeString, 2.f, FColor::Purple);
	
	
}

void ACatsWarCharacter::RestToDefaultParameters()
{
	bMaxSpeed = false;
	if(bWasInvisible)
	{
		this->CallFunctionByNameWithArguments(TEXT("SetRandomMaterial"), ar, NULL, true);
		bWasInvisible = false;
	}
	
	GetCharacterMovement()->JumpZVelocity = 600.f;
	SetMaxWalkSpeed(150.f);
	bBoost = false;
	CountTime = 0;
}

void ACatsWarCharacter::Debug()
{
	bPistolMode ? PrintDebugMessage("true") : PrintDebugMessage("false");
	
	/*
	if(IsValid(Weapon))
	{
		PrintDebugMessage("true", 2.f, FColor::White);
	}else
	{
		PrintDebugMessage("false", 2.f, FColor::White);
	}
	*/
}




