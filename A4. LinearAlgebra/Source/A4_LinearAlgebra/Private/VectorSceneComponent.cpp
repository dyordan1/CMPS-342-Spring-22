// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorSceneComponent.h"

// Sets default values for this component's properties
UVectorSceneComponent::UVectorSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsOnUpdateTransform = true;
}


// Called when the game starts
void UVectorSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UVectorSceneComponent::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) {
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);

	auto* owner = GetOwner();
	auto* textComponent = Cast<UTextRenderComponent>(owner->GetComponentByClass(UTextRenderComponent::StaticClass()));

	TArray<FVector> locations;
	auto location = owner->GetActorLocation();
	locations.Add(location);

	auto* parent = owner->GetAttachParentActor();
	if (parent != nullptr) {
		auto* grandparent = parent->GetAttachParentActor();
		if (grandparent != nullptr) {
			auto intermediateLocation = grandparent->GetActorTransform().Inverse().TransformPosition(location);
			locations.Add(intermediateLocation);
		}

		auto localLocation = parent->GetActorTransform().Inverse().TransformPosition(location);
		locations.Add(localLocation);

		textComponent->SetWorldRotation(FQuat::Identity);
	}

	if (locations.Num() == 3) {
		textComponent->SetText(FText::Format(
			FText::FromString("({0}, {1}, {2})\n({3}, {4}, {5})\n({6}, {7}, {8})"),
			FText::AsNumber(locations[2].X),
			FText::AsNumber(locations[2].Y),
			FText::AsNumber(locations[2].Z),
			FText::AsNumber(locations[1].X),
			FText::AsNumber(locations[1].Y),
			FText::AsNumber(locations[1].Z),
			FText::AsNumber(locations[0].X),
			FText::AsNumber(locations[0].Y),
			FText::AsNumber(locations[0].Z)
		));
	} else if (locations.Num() == 2) {
		textComponent->SetText(FText::Format(
			FText::FromString("({0}, {1}, {2})\n({3}, {4}, {5})"),
			FText::AsNumber(locations[1].X),
			FText::AsNumber(locations[1].Y),
			FText::AsNumber(locations[1].Z),
			FText::AsNumber(locations[0].X),
			FText::AsNumber(locations[0].Y),
			FText::AsNumber(locations[0].Z)
		));
	}
	else {
		textComponent->SetText(FText::Format(
			FText::FromString("({0}, {1}, {2})"),
			FText::AsNumber(locations[0].X),
			FText::AsNumber(locations[0].Y),
			FText::AsNumber(locations[0].Z)
		));
	}
}


// Called every frame
void UVectorSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

