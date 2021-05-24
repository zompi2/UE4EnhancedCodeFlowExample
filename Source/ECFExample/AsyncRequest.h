// Copyright (c) 2021 Damian Nowakowski. All rights reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncRequest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComplete, bool, Success);

UCLASS()
class ECFEXAMPLE_API UAsyncRequest : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnComplete OnComplete;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
	static UAsyncRequest* AsyncRequest(UObject* WorldContextObject, FString InURL);

	void Activate() override;

protected:

	UPROPERTY()
	class UObject* Proxy_WorldContextObject;

	FString Proxy_URL;
};
