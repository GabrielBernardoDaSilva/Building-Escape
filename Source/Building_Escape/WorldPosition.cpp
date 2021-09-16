// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	AActor* Object= GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Object->GetName());
	FString ObjectPosition = Object->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s postion World is :%s"),*Object->GetName(), *ObjectPosition);


}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

