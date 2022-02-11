// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatSceneComponent.h"

// Sets default values for this component's properties
UFloatSceneComponent::UFloatSceneComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UFloatSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPProgrammingQuickStart/
	FVector NewLocation = GetComponentLocation();
	FRotator NewRotation = GetComponentRotation();
	float RunningTime = GetOwner()->GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;       //Scale our height by a factor of 20
	float DeltaRotation = DeltaTime * RotationSpeed;    //Rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;
	SetRelativeLocationAndRotation(NewLocation, NewRotation);
}

