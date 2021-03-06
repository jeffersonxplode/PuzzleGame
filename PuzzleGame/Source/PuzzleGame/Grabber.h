// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	
	float Reach = 100.f;
	
	class UPhysicsHandleComponent *PhysicsHandler = nullptr;

	class UInputComponent *InputComponent = nullptr;

	//Find Attached Physics Handler
	void FindPhysicsHandleComponent();
	//Ray Cast and Grab Whats in reach
	void Grab();
	//Caller When Grab is released
	void Release();
	//Setup (assumed) Input component
	void SetupInputComponent();
	//Return  current end of reach line
	FVector GetLineTraceEnd();
	//Return current start of reach line
	FVector GetLineTraceStart();

	const FHitResult GetFirstPhysicsBodyInReach();
};
