// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorSceneComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values for this component's properties
UVectorSceneComponent::UVectorSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Ask Unreal to run the OnUpdateTransform callback when the editor position of an object changes.
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

	// Fetch the text component that is a child of this SceneComponent
	UTextRenderComponent* textComponent;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);
	Children.FindItemByClass<UTextRenderComponent>(&textComponent);

	// Get the (global) location of the component in 3D Space
	TArray<FVector> locations;
	auto location = GetComponentLocation();
	locations.Add(location);

	// Get the "parent" of this scene component. If the scene component is actor root - the "parent"
	// is the attached parent actor.
	auto* parent = GetOwner();
	if (parent->GetRootComponent() == this) {
		parent = parent->GetAttachParentActor();
	}

	// If there is a parent (i.e. the scene component is not root for owner OR the owner actor has a parent actor)
	if (parent != nullptr) {
		// Do the same check for grandparent - in this case, it's always the parent's attached parent actor
		auto* grandparent = parent->GetAttachParentActor();
		if (grandparent != nullptr) {
			auto intermediateLocation = grandparent->GetActorTransform().Inverse().TransformPosition(location);
			locations.Add(intermediateLocation);
		}

		// Do magic to transform location from global to local.
		auto localLocation = parent->GetActorTransform().Inverse().TransformPosition(location);
		locations.Add(localLocation);

		// Negate any parent rotation in the textComponent's transform. Basically, the parent can rotate anywhich way,
		// but the text will always read horizontally.
		textComponent->SetWorldRotation(FQuat::Identity);
	}

	// Output the results, based on how many relevant "locations" there are for the vector.
	if (locations.Num() == 3) {
		textComponent->SetText(FText::Format(
			FText::FromString("Parent: ({0}, {1}, {2})\nGrandparent: ({3}, {4}, {5})\nGlobal: ({6}, {7}, {8})"),
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
			FText::FromString("Parent: ({0}, {1}, {2})\nGlobal: ({3}, {4}, {5})"),
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
			FText::FromString("Global: ({0}, {1}, {2})"),
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

