// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	//Finds the HandleComponet
	FindPhysicsHandleComponent();
	SetupInputComponent();


}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If the actor finds something to grab
	if (PhysicsHandler->GrabbedComponent)
	{

		PhysicsHandler->SetTargetLocation(GetLineTraceEnd());

	};

}
//Finding the PhysicsHandleComponent
void UGrabber::FindPhysicsHandleComponent(){
	

	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandler == nullptr) {

		UE_LOG(LogTemp, Error, TEXT("%s Missing Physics Component"), *GetOwner()->GetName());
	
	}
}
//Method that release the component
void UGrabber::Release() {

	PhysicsHandler->ReleaseComponent();
}
//Setting the inputs
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {

		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Component"), *GetOwner()->GetName());
	}
}
//Getting the End of the Line of the Player View
FVector UGrabber::GetLineTraceEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
//Getting the Begin of the Line of the Player View
FVector UGrabber::GetLineTraceStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}
//Getting the first thing that the player hits
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParamenters(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(OUT HitResult,
		GetLineTraceStart(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParamenters
	);

	return HitResult;
}
//Grabbing the components that the player hits.
void UGrabber::Grab() {

	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	

	if (ActorHit) {
				PhysicsHandler->GrabComponentAtLocationWithRotation(
					ComponentToGrab,
					NAME_None,
					ComponentToGrab->GetOwner()->GetActorLocation(),
					FRotator().ZeroRotator
				);
	}

}

