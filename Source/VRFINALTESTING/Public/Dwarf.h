// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Http.h"
#include "Dwarf.generated.h"

UCLASS()
class VRFINALTESTING_API ADwarf : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADwarf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Resposne, bool bConnectedSuccessfully);

};
