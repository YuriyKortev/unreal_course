// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
ABaseGeometryHubActor::ABaseGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	SpawnRandomMovement();
	SpawnRandomColor();
	SpawnPayloads();
	
}

void ABaseGeometryHubActor::SpawnRandomMovement()
{
	UWorld* World = GetWorld();
	if (World) {
		for (int32 i = 0; i < 10; i++) {
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.f, 300.f * i, 300.f));
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
			if (Geometry) {
				FGeometryData Data;
				Data.move_type = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
				Geometry->SetGeometryData(Data);
			}
		}
	}
}

void ABaseGeometryHubActor::SpawnRandomColor()
{
	UWorld* World = GetWorld();
	if (World) {
		for (int32 i = 0; i < 10; i++) {
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.f, 300.f * i, 700.f));
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);
			if (Geometry) {
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void ABaseGeometryHubActor::SpawnPayloads()
{
	UWorld* World = GetWorld();
	if (World) {
		for (const FGeometryPayload PayLoad : GeometryPayloads) {
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(PayLoad.GeometryClass, PayLoad.InitialTransform);
			if (Geometry) {
				Geometry->SetGeometryData(PayLoad.Data);
				Geometry->FinishSpawning(PayLoad.InitialTransform);
			}
		}
	}
}

// Called every frame
void ABaseGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

