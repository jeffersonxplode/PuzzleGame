// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUZZLEGAME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OpenDoor();
	virtual void CloseDoor();

private:

	AActor *ActorThatOpens;
	AActor *Owner;

	UPROPERTY(EditAnywhere)
		ATriggerVolume *PressurePlate;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

		float LastDoorOpenTime;

};
