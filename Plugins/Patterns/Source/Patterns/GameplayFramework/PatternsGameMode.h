// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeManager.h"
#include "GameFramework/GameMode.h"
#include "PatternsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PATTERNS_API APatternsGameMode : public AGameMode, public IGameModeManager
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintCallable)
	virtual void CommonFunction() override;
	
};
