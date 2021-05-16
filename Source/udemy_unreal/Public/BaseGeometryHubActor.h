// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "BaseGeometryHubActor.generated.h"


USTRUCT(BlueprintType)
struct FGeometryPayload {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
};


UCLASS()
class UDEMY_UNREAL_API ABaseGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass; //ABaseGeometryActor and subclasses

	UPROPERTY(EditAnywhere)
	UClass* Class; // All unreal classes

	UPROPERTY(EditAnywhere)
	ABaseGeometryActor* GeometryObject; // Only ABaseGeometryActor

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

	void SpawnRandomMovement();
	void SpawnRandomColor();
	void SpawnPayloads();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};