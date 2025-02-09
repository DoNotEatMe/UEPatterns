// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SingletonWorldSubsystem.generated.h"

class APatternsGameMode;
UCLASS()
class PATTERNS_API USingletonWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Patterns | Subsystem | Getters", BlueprintPure)
	APatternsGameMode* GetCurrentGameMode();

private:
	UPROPERTY()
	APatternsGameMode* CurrentGameMode;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
};
