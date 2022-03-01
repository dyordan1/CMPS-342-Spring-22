// Fill out your copyright notice in the Description page of Project Settings.


#include "CoordinateFrameSceneComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values for this component's properties
UCoordinateFrameSceneComponent::UCoordinateFrameSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Ask Unreal to run the OnUpdateTransform callback when the editor position of an object changes.
	bWantsOnUpdateTransform = true;
}


// Called when the game starts
void UCoordinateFrameSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UCoordinateFrameSceneComponent::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport) {
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);

	UTextRenderComponent* textComponent;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);
	Children.FindItemByClass<UTextRenderComponent>(&textComponent);
	
	// Why inverse? Because reasons.
	auto owner = GetOwner();
	auto transform = owner->GetTransform().ToMatrixWithScale();
	auto origin = owner->GetActorLocation();

	// Yes, we're cheating a bit because graphics are complicated and Unreal is silly. Just take it at face value.
	textComponent->SetText(FText::Format(
		FText::FromString("| {0} {1} {2} {3} |\n| {4} {5} {6} {7} |\n| {8} {9} {10} {11} |\n| 0 0 0 1 |"),
		FText::AsNumber(transform.GetColumn(0).Component(0)),
		FText::AsNumber(transform.GetColumn(0).Component(1)),
		FText::AsNumber(transform.GetColumn(0).Component(2)),
		FText::AsNumber(origin.X),
		FText::AsNumber(transform.GetColumn(1).Component(0)),
		FText::AsNumber(transform.GetColumn(1).Component(1)),
		FText::AsNumber(transform.GetColumn(1).Component(2)),
		FText::AsNumber(origin.Y),
		FText::AsNumber(transform.GetColumn(2).Component(0)),
		FText::AsNumber(transform.GetColumn(2).Component(1)),
		FText::AsNumber(transform.GetColumn(2).Component(2)),
		FText::AsNumber(origin.Z)
	));

	//textComponent->SetText(FText::FromString(transform.ToString()));

	// Negate any parent rotation in the textComponent's transform. Basically, the parent can rotate anywhich way,
	// but the text will always read horizontally.
	textComponent->SetWorldRotation(FQuat::Identity);
}


// Called every frame
void UCoordinateFrameSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

