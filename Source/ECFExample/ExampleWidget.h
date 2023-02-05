// Copyright (c) 2023 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ECFTypes.h"
#include "ECFInstanceId.h"
#include "ExampleWidget.generated.h"

UENUM(BlueprintType)
enum class ETimeLockTestType : uint8
{
	TL2Sec,
	TL5Sec
};

UCLASS()
class ECFEXAMPLE_API UExampleWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	void AddToLog_Internal(FString Log, bool bStopped = false);

	UFUNCTION(BlueprintImplementableEvent)
	void AddToLog(const FString& Log);

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void DelayTest();

	UFUNCTION(BlueprintImplementableEvent)
	void DelayTestFinished();

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void TickerTest();

	UFUNCTION(BlueprintImplementableEvent)
	void TickerTestFinished(bool bStopped);

	UFUNCTION(BlueprintImplementableEvent)
	void SetTickerValue_BP(float NewValue);

	float TickerValue = 0.f;

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void TimelineTest(EECFBlendFunc TimelineFunc, float StartValue, float StopValue);

	UFUNCTION(BlueprintImplementableEvent)
	void TimelineTestFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void SetTimelineValue_BP(float NewValue, float NewTime);

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void CustomTimelineTest(UCurveFloat* Curve);

	UFUNCTION(BlueprintImplementableEvent)
	void CustomTimelineTestFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void SetCustomTimelineValue_BP(float NewValue, float NewTime);

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void WaitAndExecuteTest(float TimeOut);

	UFUNCTION(BlueprintImplementableEvent)
	void WaitAndExecuteTestFinished(bool bTimedOut);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWaitAndExecuteConditional = false;

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void WhileTrueExecuteTest(float TimeOut = 0.f);

	UFUNCTION(BlueprintImplementableEvent)
	void WhileTrueExecuteTestFinished(bool bTimedOut);

	UFUNCTION(BlueprintImplementableEvent)
	void SetWhileTrueExecuteTickerValue_BP(float NewValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWhileTrueExecuteConditional = true;

	float WhileTrueExecuteTickerValue = 0.f;

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void TimeLockTest(ETimeLockTestType Type);

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void DoOnceTest();

	UFUNCTION(BlueprintCallable)
	void ResetDoOnce();

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void DoNTimesTest(int32 Times);

	UFUNCTION(BlueprintCallable)
	void ResetDoNTimes();

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void DoNoMoreThanXTime(float Time = 5.f, int32 MaxExecsEnqueue = 1);
};
