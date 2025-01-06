// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "ExampleActor.h"
#include "EnhancedCodeFlow.h"

AExampleActor::AExampleActor()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.f;
}

void AExampleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDoOnce)
	{
		//ForLoopCoro();
		bDoOnce = false;
	}
}
	
/*
FECFCoroutine AExampleActor::ForLoopCoro()
{
	for (int32 I = 0; I < 3; I++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ForLoopCoro %i"), I));
		co_await FFlow::WaitSeconds(this, .5f);
	}
}
*/