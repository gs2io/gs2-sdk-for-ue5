// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gs2Tutorial.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GameLog, Log, All);

UCLASS()
class EZGS2_API AGs2Tutorial : public AActor
{
	GENERATED_BODY()

public:
	AGs2Tutorial();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
