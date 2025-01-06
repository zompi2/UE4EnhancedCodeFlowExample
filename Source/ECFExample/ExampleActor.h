// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedCodeFlow.h"
#include "ExampleActor.generated.h"

UCLASS(BlueprintType, Blueprintable)
class ECFEXAMPLE_API AExampleActor : public AActor
{
	GENERATED_BODY()
	
public:

	AExampleActor();
	void Tick(float DeltaTime) override;

	//FECFCoroutine ForLoopCoro();
	bool bDoOnce = true;
};
