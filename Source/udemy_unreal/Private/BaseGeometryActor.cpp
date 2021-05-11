// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	init_loc = GetActorLocation();

	// print_str_stats();
	// print_types();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector cur_loc = GetActorLocation();
	float time = GetWorld()->GetTimeSeconds();
	cur_loc.Z = init_loc.Z + ampl * FMath::Sin(freq * time);

	SetActorLocation(cur_loc);
}

void ABaseGeometryActor::print_types()
{

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor's name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Num of weapon: %d, Num of kills: %i"), num_of_weapon, num_of_kills);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HP: %f"), hp);
	UE_LOG(LogBaseGeometry, Warning, TEXT("IdDead: %d"), is_dead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon: %d"), static_cast<int>(has_weapon));
}

void ABaseGeometryActor::print_str_stats()
{
	UE_LOG(LogBaseGeometry, Display, TEXT("Actor's name: %s"), *name);


	FString num_of_kills_str = FString("Num of kills = ") + FString::FromInt(num_of_kills);
	FString is_dead_str = FString("Is dead = ") + FString(is_dead ? "true" : "false");
	FString hp_str = FString("Num of HP = ") + FString::SanitizeFloat(hp);

	FString stats = FString::Printf(TEXT("--------Actor's stats-------\n%s\n%s\n%s\n"), *num_of_kills_str, *is_dead_str, *hp_str);
	UE_LOG(LogBaseGeometry, Display, TEXT("%s"), *stats);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, stats, true, FVector2D(1.5f, 1.5f));
}

void ABaseGeometryActor::print_transform()
{

	FTransform tr = GetActorTransform();
	FVector loc = tr.GetLocation();
	FRotator rot = tr.Rotator();
	FVector sc = tr.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor's name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Transform: %s"), *tr.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Location: %s"), *loc.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Rotation: %s"), *rot.ToString());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Scale: %s"), *sc.ToString());

	UE_LOG(LogBaseGeometry, Error, TEXT("Human transform: %s"), *tr.ToHumanReadableString());
}

