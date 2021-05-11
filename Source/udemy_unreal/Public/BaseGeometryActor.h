// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "BaseGeometryActor.generated.h"

UCLASS()
class UDEMY_UNREAL_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* BaseMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float ampl = 50.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float freq = 2.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
	int32 num_of_kills = 4;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	bool is_dead = false;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool has_weapon = true;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 num_of_weapon = 2;

	UPROPERTY(EditAnywhere, Category = "Health")
	float hp = 56.32f;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	FString name = "John Connor";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FVector init_loc;

	void print_types();
	void print_str_stats();
	void print_transform();
};
