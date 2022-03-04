// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "OrthogonalCameraSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class A4_LINEARALGEBRA_API UOrthogonalCameraSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOrthogonalCameraSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category="Orthographic Camera")
	float near = 1000;
	UPROPERTY(EditAnywhere, Category = "Orthographic Camera")
	float far = -1000;
	UPROPERTY(EditAnywhere, Category = "Orthographic Camera")
	float top = 1000;
	UPROPERTY(EditAnywhere, Category = "Orthographic Camera")
	float bottom = -1000;
	UPROPERTY(EditAnywhere, Category = "Orthographic Camera")
	float left = 1000;
	UPROPERTY(EditAnywhere, Category = "Orthographic Camera")
	float right = -1000;
};
