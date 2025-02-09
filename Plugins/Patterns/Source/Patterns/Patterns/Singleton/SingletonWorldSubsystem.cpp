// Fill out your copyright notice in the Description page of Project Settings.


#include "SingletonWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "Patterns/GameplayFramework/PatternsGameMode.h"



void USingletonWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("USingletonWorldSubsystem created."));

	
}

void USingletonWorldSubsystem::Deinitialize()
{
	CurrentGameMode = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("USingletonWorldSubsystem deleted."));
	Super::Deinitialize();
}

APatternsGameMode* USingletonWorldSubsystem::GetCurrentGameMode()
{
	if (!CurrentGameMode)
	{
		UWorld* World = GetWorld();
		if (!World)
		{
			UE_LOG(LogTemp, Error, TEXT("USingletonWorldSubsystem::GetCurrentGameMode - World is not valid"));
			return nullptr;
		}

		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(World);
		CurrentGameMode = Cast<APatternsGameMode>(GameModeBase);

		if (!CurrentGameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("USingletonWorldSubsystem::GetCurrentGameMode - CurrentGameMode is not valid"));
		}
	}

	return CurrentGameMode;
}
