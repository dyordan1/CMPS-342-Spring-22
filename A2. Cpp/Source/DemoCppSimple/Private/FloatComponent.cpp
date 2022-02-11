// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatComponent.h"

// Sets default values for this component's properties
UFloatComponent::UFloatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UFloatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	auto owner = GetOwner();

	// https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPProgrammingQuickStart/
	FVector NewLocation = owner->GetActorLocation();
	FRotator NewRotation = owner->GetActorRotation();
	float RunningTime = owner->GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * RotationSpeed;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	owner->SetActorLocationAndRotation(NewLocation, NewRotation);
}

