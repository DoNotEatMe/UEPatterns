#pragma once

#include "CoreMinimal.h"
#include "GameplayFrameworkManager.generated.h"

class APatternsGameMode;
/**
 * Single point to access gameplay management classes
 */
UCLASS()
class PATTERNS_API UGameplayFrameworkManager : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Singleton Initializer and getter
	 * @param WorldContext UObject for getting needed world
	 * @return Pointer to Instance of class to operate with
	 */
	UFUNCTION(BlueprintCallable, Category = "Patterns | Singleton | LifeCycle")
	static UGameplayFrameworkManager* GetGameplayFrameworkManager(UObject* WorldContext);

	/**
	 * Manual Instance cleanup 
	 */
	UFUNCTION(BlueprintCallable, Category = "Patterns | Singleton | LifeCycle")
	static void ResetInstance();

	/**
	 * Resetting current Instance to nullptr and calling Cleanup() for rese
	 * 
	 * Signature using for FWorldCleanupEvent bind delegate
	 * DECLARE_MULTICAST_DELEGATE_ThreeParams(FWorldCleanupEvent, UWorld, bool bSessionEnded, bool bCleanupResources);
	 * 
	 * Params not used if calling manually
	 */
	void ResetInstancePIE(UWorld* World, bool bCleanupResources, bool bSessionEnded);

	/**
	 * @return Current GameMode pointer 
	 */
	UFUNCTION(BlueprintCallable, Category = "Patterns | Singleton | Getters", BlueprintPure)
	static APatternsGameMode* GetCurrentGameMode();

private:
	UGameplayFrameworkManager();

	/**
	 * Singleton instance
	 */
	static UGameplayFrameworkManager* Instance;

	/**
	 * Pointers reset
	 */
	void Cleanup();
	
	UPROPERTY()
	APatternsGameMode* CurrentGameMode = nullptr;
};
