// Copyright (c) 2021 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UENUM(BlueprintType)
enum class EInExecType : uint8
{
	InType1,
	InType2,
	InType3
};

UENUM(BlueprintType)
enum class EOutExecType : uint8
{
	OutType1,
	OutType2,
	OutType3
};

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString StructId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Param1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Param2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Param3;
};


UCLASS(Blueprintable, BlueprintType)
class ECFEXAMPLE_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Exec,Then"))
	void MultipleExecsFuncion(EInExecType Exec, EOutExecType& Then);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ActorClass"))
	AActor* CreateActorOfClass(TSubclassOf<AActor> ActorClass);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ActorClass", DynamicOutputParam = "NewActors"))
	void CreateManyActorsOfClass(TSubclassOf<AActor> ActorClass, TArray<AActor*>& NewActors);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (TitleProperty = "StructId"))
	TArray<FMyStruct> MyStructs;
};
