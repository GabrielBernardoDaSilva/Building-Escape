


#include "OpenDoor.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include <GameFramework/PlayerController.h>

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

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;


	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("The PressurePlate is nullptr, the name of the actor is %s !"), *GetOwner()->GetName());

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	auto CurrentTime = GetWorld()->GetTimeSeconds();
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor(DeltaTime);
		DoorLastOpen = CurrentTime;
	}
	else {
		if (CurrentTime- DoorLastOpen > DoorCloseDelay)
			CloseDoor(DeltaTime);

	}

	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, OpenAngle, DeltaTime, 45);
	AActor* Object = GetOwner();
	FRotator DoorRotation = Object->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	Object->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, InitialYaw, DeltaTime, 90);
	AActor* Object = GetOwner();
	FRotator DoorRotation = Object->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	Object->SetActorRotation(DoorRotation);
}

