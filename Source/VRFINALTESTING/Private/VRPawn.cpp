// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "GameFramework/Pawn.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRControllerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRControllerRoot"));
	RootComponent = VRControllerRoot;

	//////Initialize the Left Motion Controller and attach it to VRControllerRoot
	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	LeftMotionController->SetupAttachment(VRControllerRoot);
	LeftMotionController->SetTrackingSource(EControllerHand::Left);

	////Initialize the Left Hand Skeletal Mesh and attach it to LeftMotionController
	LeftHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(LeftMotionController);

	////Initialize the RIght Motion Controller and attach it to VRControllerRoot
	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	RightMotionController->SetupAttachment(VRControllerRoot);
	RightMotionController->SetTrackingSource(EControllerHand::Right);

	////Initialize the Right Hand Skeletal Mesh and attach it to RightMotionController
	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(RightMotionController);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

