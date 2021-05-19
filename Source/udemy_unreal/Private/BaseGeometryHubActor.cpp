// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

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

	// SpawnRandomMovement();
	// SpawnRandomColor();
	SpawnPayloads();
	
}

void ABaseGeometryHubActor::SpawnRandomMovement() const
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

void ABaseGeometryHubActor::SpawnRandomColor() const
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
				Geometry->OnColorChanged.AddDynamic(this, &ABaseGeometryHubActor::OnColorChanged);
				Geometry->OnTimerFinished.AddUObject(this, &ABaseGeometryHubActor::OnTimerFinished);
				Geometry->FinishSpawning(PayLoad.InitialTransform);
			}
		}
	}
}

void ABaseGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor name: %s, Color: %s"), *Name, *Color.ToString());
}

void ABaseGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!Actor)
		return;

	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);

	if (!Geometry)
		return;

	UE_LOG(LogGeometryHub, Display, TEXT("Cast finished, Object ampl: %f"), Geometry->GetGeometryData().ampl);

	// Geometry->SetLifeSpan(2.f);
	Geometry->Destroy();
}

// Called every frame
void ABaseGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

