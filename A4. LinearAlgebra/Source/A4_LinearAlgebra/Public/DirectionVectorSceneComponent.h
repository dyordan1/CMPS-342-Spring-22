// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VectorSceneComponent.h"
#include "DirectionVectorSceneComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class A4_LINEARALGEBRA_API UDirectionVectorSceneComponent : public UVectorSceneComponent
{
	GENERATED_BODY()

protected:
	/** Native callback when this component is moved */
	virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport = ETeleportType::None);
};
