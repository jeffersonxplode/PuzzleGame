// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();

}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (GetTotalMassOfActorOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();		
	}

	else 
	{
		OnClose.Broadcast();
	}

}



float UOpenDoor::GetTotalMassOfActorOnPlate() 
{
	
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors) 
	{	//Finding the Actors that pressed the plate and adding their masses on TotalMass
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		
	}

	return TotalMass;

}