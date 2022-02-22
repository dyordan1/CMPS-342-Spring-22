// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionVectorSceneComponent.h"


void UDirectionVectorSceneComponent::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) {
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);

	auto* owner = GetOwner();
	auto* arrow = Cast<UStaticMeshComponent>(owner->GetComponentByClass(UStaticMeshComponent::StaticClass()));

	auto location = owner->GetActorLocation();
	auto* parent = owner->GetAttachParentActor();
	if (parent != nullptr) {
		auto parentLocation = parent->GetActorLocation();
		location -= parentLocation;
		arrow->SetWorldLocation(parentLocation);
	}
	else {
		arrow->SetWorldLocation(FVector::ZeroVector);
	}
	arrow->SetWorldScale3D(FVector(location.Size() / 50, 5, 5));
	arrow->SetWorldRotation(location.ToOrientationQuat());
}