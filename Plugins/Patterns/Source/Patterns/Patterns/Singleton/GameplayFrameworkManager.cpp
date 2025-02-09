#include "GameplayFrameworkManager.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Patterns/GameplayFramework/PatternsGameMode.h"

UGameplayFrameworkManager* UGameplayFrameworkManager::Instance = nullptr;

UGameplayFrameworkManager::UGameplayFrameworkManager()
{
	FWorldDelegates::OnWorldCleanup.AddUObject(this, &UGameplayFrameworkManager::ResetInstancePIE);
}

UGameplayFrameworkManager* UGameplayFrameworkManager::GetGameplayFrameworkManager(UObject* WorldContext)
{
	if (!Instance)
	{
		UWorld* World = nullptr;
		if (WorldContext)
		{
			World = WorldContext->GetWorld();
		}
		else
		{
			ResetInstance();
			UE_LOG(LogTemp, Error,
			       TEXT(
				       "UGameplayFrameworkManager::GetGameplayFrameworkManager Failed to create instance. Invalid WorldContext."
			       ));
			return nullptr;
		}

		Instance = NewObject<UGameplayFrameworkManager>(World, UGameplayFrameworkManager::StaticClass());
		if (!Instance)
		{
			ResetInstance();
			UE_LOG(LogTemp, Error,
			       TEXT(
				       "UGameplayFrameworkManager::GetGameplayFrameworkManager Failed to Initialize Instance. Instance is not valid."
			       ));
			return nullptr;
		}
	}
	return Instance;
}

void UGameplayFrameworkManager::ResetInstance()
{
	if (Instance)
	{
		Instance->ResetInstancePIE(Instance->GetWorld(), true, true);
	}
}

void UGameplayFrameworkManager::ResetInstancePIE(UWorld* World, bool bCleanupResources, bool bSessionEnded)
{
	if (Instance)
	{
		Instance->Cleanup();
		Instance = nullptr;
	}
}

void UGameplayFrameworkManager::Cleanup()
{
	if (CurrentGameMode)
	{
		CurrentGameMode = nullptr;
	}

	FWorldDelegates::OnWorldCleanup.RemoveAll(this);
}

APatternsGameMode* UGameplayFrameworkManager::GetCurrentGameMode()
{
	if (Instance && Instance->CurrentGameMode)
	{
		return Instance->CurrentGameMode;
	}

	if (Instance)
	{
		UWorld* World = Instance->GetWorld();
		if (!World)
		{
			UE_LOG(LogTemp, Error, TEXT("UGameplayFrameworkManager::GetCurrentGameMode World is not valid"));
			return nullptr;
		}

		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(World);
		Instance->CurrentGameMode = Cast<APatternsGameMode>(GameModeBase);

		if (Instance->CurrentGameMode)
		{
			return Instance->CurrentGameMode;
		}

		UE_LOG(LogTemp, Error,
		       TEXT("UGameplayFrameworkManager::GetCurrentGameMode Instance->CurrentGameMode is not valid"));
	}

	UE_LOG(LogTemp, Error, TEXT("UGameplayFrameworkManager::GetCurrentGameMode Instance is not valid"));

	return nullptr;
}
