// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleMeshActor.h"

// Sets default values
ASimpleMeshActor::ASimpleMeshActor()
{
	// Set actor as ticking.
	PrimaryActorTick.bCanEverTick = true;

	// Create a UProceduralMeshComponent (requires ProceduralMeshComponent in uproject and .Build.cs).
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;

	// Create the appropriate shape when the object is constructed (this may not be the default in play mode).
	CreateShape();
}

// Called when a property is changed.
void ASimpleMeshActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Just re-draw (the new property value will be picked up in CreateShape).
	CreateShape();
}

// Creates whatever shape the shape property carries.
void ASimpleMeshActor::CreateShape()
{
	// Get the shape enum property and log it.
	auto selectedValue = shape.GetValue();
	UE_LOG(LogTemp, Log, TEXT("Creating %s"), *UEnum::GetValueAsString(selectedValue));

	// Clear all procedural geometry.
	mesh->ClearAllMeshSections();

	// Draw the "right" geometry for the enum value selected.
	switch (selectedValue) {
	case Triangle:
		CreateMesh(CreateTriangle());
		break;
	case Square:
		CreateMesh(CreateSquare());
		break;
	case Tetrahedron:
		CreateMesh(CreateIcosahedron());
		break;
	case SmoothTetra:
		CreateMesh(CreateSmoothIcosahedron());
		break;
	case UVSquare:
		CreateMesh(CreateUVSquare());
		break;
	}
}

// Creates a simple triangle.
SimpleMesh ASimpleMeshActor::CreateTriangle()
{
	auto m = SimpleMesh();

	// Add vertices
	m.Vertices.Add(FVector(0, 0, 100));
	m.Vertices.Add(FVector(0, 100, 0));
	m.Vertices.Add(FVector(100, 0, 0));

	// Add triangle
	m.Triangles.Add(0);
	m.Triangles.Add(1);
	m.Triangles.Add(2);

	return m;
}

// Creates a simple square (by drawing two triangles).
SimpleMesh ASimpleMeshActor::CreateSquare()
{
	auto m = SimpleMesh();

	// Add vertices
	m.Vertices.Add(FVector(100, 100, 0));
	m.Vertices.Add(FVector(100, -100, 0));
	m.Vertices.Add(FVector(-100, -100, 0));
	m.Vertices.Add(FVector(-100, 100, 0));

	// Add triangles
	m.Triangles.Add(0);
	m.Triangles.Add(1);
	m.Triangles.Add(2);

	m.Triangles.Add(0);
	m.Triangles.Add(2);
	m.Triangles.Add(3);

	return m;
}

// Creates an icosahedron hull (by drawing four triangles).
SimpleMesh ASimpleMeshActor::CreateIcosahedron()
{
	auto m = SimpleMesh();

	// Add vertices
	m.Vertices.Add(FVector(100, 100, 100));
	m.Vertices.Add(FVector(100, -100, -100));
	m.Vertices.Add(FVector(-100, 100, -100));
	m.Vertices.Add(FVector(-100, -100, 100));

	// Add triangles
	m.Triangles.Add(0);
	m.Triangles.Add(2);
	m.Triangles.Add(1);

	m.Triangles.Add(3);
	m.Triangles.Add(0);
	m.Triangles.Add(1);

	m.Triangles.Add(1);
	m.Triangles.Add(2);
	m.Triangles.Add(3);

	m.Triangles.Add(2);
	m.Triangles.Add(0);
	m.Triangles.Add(3);

	return m;
}

// Creates a "smooth" icosahedron by controlling the normals.
SimpleMesh ASimpleMeshActor::CreateSmoothIcosahedron()
{
	// Use the same geometry...
	auto m = CreateIcosahedron();

	// Set a normalized copy of each vertex as the vertex normal.
	m.Normals.Add(m.Vertices[0].GetUnsafeNormal());
	m.Normals.Add(m.Vertices[1].GetUnsafeNormal());
	m.Normals.Add(m.Vertices[2].GetUnsafeNormal());
	m.Normals.Add(m.Vertices[3].GetUnsafeNormal());

	return m;
}

// Creates a simple square (by drawing two triangles).
SimpleMesh ASimpleMeshActor::CreateUVSquare()
{
	auto m = SimpleMesh();

	// Add vertices
	m.Vertices.Add(FVector(100, 100, 0));
	m.Vertices.Add(FVector(100, -100, 0));
	m.Vertices.Add(FVector(-100, -100, 0));
	m.Vertices.Add(FVector(-100, 100, 0));

	// Add UV coordinates
	m.UV.Add(FVector2D(1, 1));
	m.UV.Add(FVector2D(1, -1));
	m.UV.Add(FVector2D(-1, -1));
	m.UV.Add(FVector2D(-1, 1));

	// Add triangles
	m.Triangles.Add(0);
	m.Triangles.Add(1);
	m.Triangles.Add(2);

	m.Triangles.Add(0);
	m.Triangles.Add(2);
	m.Triangles.Add(3);

	return m;
}

void ASimpleMeshActor::CreateMesh(SimpleMesh drawMesh) {
	// Ensure we only draw complete triangles.
	auto numTriangles = drawMesh.Triangles.Num() / 3;

	// Initialize all the data we need (outside vertex/triangle).
	TArray<FVector> normals = drawMesh.Normals;
	TArray<FProcMeshTangent> tangents;
	TArray<FVector2D> UV = drawMesh.UV;
	TArray<FLinearColor> vertexColors;

	// Calculate face normals, if needed.
	if (normals.IsEmpty()) {
		for (int i = 0; i < numTriangles; i++) {
			// Get the vertex data for the triangle
			auto v0 = drawMesh.Vertices[drawMesh.Triangles[i * 3 + 0]];
			auto v1 = drawMesh.Vertices[drawMesh.Triangles[i * 3 + 1]];
			auto v2 = drawMesh.Vertices[drawMesh.Triangles[i * 3 + 2]];

			// Plane "winding order" is the opposite of face winding order...
			auto trianglePlane = FPlane(v2, v1, v0);
			auto triNormal = trianglePlane.GetNormal();
			normals.Add(triNormal);
			normals.Add(triNormal);
			normals.Add(triNormal);
		}
	}

	// Add whatever UVs, if needed.
	if (UV.IsEmpty()) {
		TArray<FVector2D> uvValues = {
			FVector2D(0.5, 1),
			FVector2D(0, 0),
			FVector2D(1, 0)
		};
		for (int i = 0; i < drawMesh.Vertices.Num(); i++) {
			UV.Add(uvValues[i % uvValues.Num()]);
		}
	}

	// Add fake tangent and vertex color data cause we don't care...
	for (int i = 0; i < numTriangles; i++) {
		tangents.Add(FProcMeshTangent(0, 1, 0));
		tangents.Add(FProcMeshTangent(0, 1, 0));
		tangents.Add(FProcMeshTangent(0, 1, 0));
	}
	for (int i = 0; i < drawMesh.Vertices.Num(); i++) {
		vertexColors.Add(FLinearColor(1, 0, 0, 1.0));
	}

	mesh->CreateMeshSection_LinearColor(0, drawMesh.Vertices, drawMesh.Triangles, normals, UV, vertexColors, tangents, true);
	mesh->ContainsPhysicsTriMeshData(true);
}

// Called when the game starts or when spawned
void ASimpleMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

