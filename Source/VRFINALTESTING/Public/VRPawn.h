// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SceneComponent.h"
#include "VRPawn.generated.h"

UCLASS()
class VRFINALTESTING_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//// Root Scene Component for VR controllers
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* VRControllerRoot;

	////// Left and Right Motion Controllers
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* LeftMotionController;

	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* RightMotionController;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* LeftHand;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* RightHand;

};
