// Fill out your copyright notice in the Description page of Project Settings.


#include "OrthogonalCameraSceneComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include <cmath>

// Sets default values for this component's properties
UOrthogonalCameraSceneComponent::UOrthogonalCameraSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOrthogonalCameraSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called when the game starts
void UOrthogonalCameraSceneComponent::OnRegister()
{
	Super::OnRegister();
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	// Fetch bounding box component...
	UStaticMeshComponent* previewMesh = nullptr;
	Children.FindItemByClass<UStaticMeshComponent>(&previewMesh);

	// Calculate scale for bounding box
	auto depth = std::abs(near - far);
	auto width = std::abs(left - right);
	auto height = std::abs(top - bottom);
	auto scale = FVector(depth / 100, width / 100, height / 100);

	// Apply scale to StaticMeshComponent
	if (previewMesh != nullptr) {
		previewMesh->SetRelativeScale3D(scale);
		previewMesh->SetRelativeLocation(FVector(far + depth / 2, right + width / 2, bottom + height / 2));
	}

	// Put capture component in the right location for default clipping plane to (mostly) match the "near" plane.
	USceneCaptureComponent2D* camera = nullptr;
	Children.FindItemByClass<USceneCaptureComponent2D>(&camera);
	if (camera != nullptr) {
		camera->SetRelativeLocation(FVector(near - 1, 0, 0));
	}
}


// Called every frame
void UOrthogonalCameraSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}