// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Cat_SaveGame.h"
#include "GameFramework/Character.h"
#include "Misc/OutputDeviceNull.h"
#include "Sound/SoundCue.h"
#include "CatsWarCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FShakeDelegate, float)
DECLARE_DELEGATE_OneParam(FMaxSpeedDelegate, float)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShootDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyAttackDelegate, float, Damage);

enum EBoost
{
	JUMP,
	INVISIBILITY,
	SPEED,
	HEALTH,
	ARMOR,
	DAMAGE,
};

enum EAttackType
{
	HAND,
	BAT,
	PISTOL,
};


UCLASS(config=Game)
class ACatsWarCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ACatsWarCharacter();
	
	virtual  void BeginPlay() override;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(BlueprintAssignable)
	FShootDelegate Shoot;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundCue*> OtherSoundCue;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundCue*> ShootCue;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundCue*> PunchCue;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundCue*> TakeDamageCue;
	
	UPROPERTY(BlueprintAssignable)
	FEnemyAttackDelegate EnemyAttackDelegate;

	
	void Drug();

	void GetAmmo();

	UPROPERTY(BlueprintReadOnly)
	float DrugCount = 0;

	UPROPERTY(BlueprintReadOnly)
	float PistolClip = 5.f;
	
protected:
	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void PrintDebugMessage(FString Message = "Hello", float TimeToDisplay = 1.f, FColor Color = FColor::Red);

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> CamShake;

	
	UPROPERTY(VisibleAnywhere)
	bool bBoost = false;

	UPROPERTY(EditAnywhere)
	float TimerEndTime = 15;

	UPROPERTY(EditAnywhere, Category= "Weapons")
	float ReloadTime = 2.f;


	UPROPERTY(EditAnywhere, Category = "Health and damage")
	float PistolDamage = 20;
	
	UPROPERTY(EditAnywhere, Category = "Health and damage")
	float Health = 100.f;
	
	UPROPERTY(BlueprintReadOnly, Category="Animation mode")
	bool bPistolMode = false;
	
	
	UFUNCTION()
	void CameraSake(float Scale);

	UFUNCTION()
	void SetMaxWalkSpeed(float Speed);

	UFUNCTION()
	void JumpBoost();

	UFUNCTION()
	void InvisibilityBoost();

	UFUNCTION()
	void SpeedBoost();

	UFUNCTION(BlueprintCallable)
	void MeleAttack(float Radius, int32 Segments);

	UFUNCTION()
	void GetDamage(float Damage);
	
	UPROPERTY(EditDefaultsOnly, Category= "Weapons")
	TArray<TSubclassOf<AActor>> Weapons;

	UPROPERTY(EditDefaultsOnly, Category= "Destruction")
	TSubclassOf<AActor> RadialForce;

	UFUNCTION()
	void DisablePlayerInput(float Time);

private:

	void RepeatingFunction();
	FTimerHandle MemberTimerHandle;
	float CountTime = 0;
	
	void RestToDefaultParameters();

	bool bWasInvisible = false;
	bool bMaxSpeedBoost = false;
	
	void Debug();

	void Boost(EBoost BOOST);

	bool bMaxSpeed = false;
	FOutputDeviceNull ar;


	void SpawnWeapon(FString SocketName, int32 WeaponIndex);
	void Hand();
	void Bat();
	void Pistol();
	AActor* Weapon;
	bool bZoom = false;
	
	void Zoom();
	void Unzoom();


	
	void PistolAttack();
	
	
	
	void Death();
	
	void Attack();
	bool Ammo();
	void ReloadingPistol();

	float Bullets = 15.f;

	

	FTimerHandle ReloadTimerHandle;
	bool bReloading = true;	

	
	EAttackType AttackType = EAttackType::HAND;

	float HandsAndBatDamage = 5;

	void SaveGame();
	void LoadGame();




	
	/*void SpawnWeapon(FVector Location, FRotator Rotation, FName SocketName);
	
	AActor* Weapon;*/
	
};

