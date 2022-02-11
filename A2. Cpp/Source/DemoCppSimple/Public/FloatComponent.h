// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatComponent.generated.h"


UCLASS( ClassGroup=(Potato), meta=(BlueprintSpawnableComponent) )
class DEMOCPPSIMPLE_API UFloatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFloatComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "FloatingActor")
	float FloatSpeed = 20.0f;

	UPROPERTY(EditAnywhere, Category = "FloatingActor")
	float RotationSpeed = 20.0f;
};
