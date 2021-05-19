// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"

#include "SandboxPawn.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSanboxPlayerController, All, All)

void ASandboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!InputComponent)
		return;
	
	InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
}

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::ChangePawn()
{
	if(Pawns.Num() <=1)
		return;

	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();

	if(!CurrentPawn)
		return;

	UE_LOG(LogSanboxPlayerController, Warning, TEXT("Pawn changed"))

	Possess(CurrentPawn);
}
