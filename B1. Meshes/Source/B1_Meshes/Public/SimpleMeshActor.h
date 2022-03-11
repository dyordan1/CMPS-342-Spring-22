// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "SimpleMeshActor.generated.h"

// An enum for the shape to draw in the procedural mesh actor
UENUM()
enum Shape
{
	Triangle      UMETA(DisplayName = "Triangle"),
	Square        UMETA(DisplayName = "Square"),
	Tetrahedron   UMETA(DisplayName = "Tetrahedron"),
	SmoothTetra   UMETA(DisplayName = "Smooth Tetrahedron"),
	UVSquare      UMETA(DisplayName = "UV Mapped Square"),
};

// Simple mesh data - vertices & triangles with optional normals. Used for procedural mesh generation.
struct SimpleMesh
{
public:
	// A list of all vertices in the mesh.
	TArray<FVector> Vertices;

	// A list of vertex UVs. If empty, will replace with fake values.
	TArray<FVector2D> UV;

	// A list of vertex normals. If empty, will calculate face normals instead.
	TArray<FVector> Normals;

	// A list of triangle "members" - should be divisible by 3.
	TArray<int32> Triangles;
};

// A very simple procedural mesh generator actor that demonstractes meshes and hulls from vertex data
UCLASS()
class B1_MESHES_API ASimpleMeshActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASimpleMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when property is changed
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	// A property to select what shape to procedurally generate
	UPROPERTY(EditAnywhere, Category = SimpleMesh)
	TEnumAsByte<Shape> shape;

private:
	// Private helpers
	void CreateShape();
	SimpleMesh CreateTriangle();
	SimpleMesh CreateSquare();
	SimpleMesh CreateIcosahedron();
	SimpleMesh CreateSmoothIcosahedron();
	SimpleMesh CreateUVSquare();

	void CreateMesh(SimpleMesh drawMesh);

	// The UProceduralMeshComponent being VisibleAnywhere allows us to see properties in editor
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* mesh;
};
