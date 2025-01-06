// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ECFTypes.h"
#include "Coroutines/ECFCoroutine.h"
#include "ECFInstanceId.h"
#include "ECFActionSettings.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECFActionSettings ActionSettings_CPP;

	UPROPERTY(Transient)
	class AExampleActor* ExActor = nullptr;


	UFUNCTION(BlueprintCallable)
	void CoroActorTest();

	UFUNCTION(BlueprintCallable)
	void ForceGC();


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
	void WaitSecondsTest();
	FECFCoroutine WaitSecondsTest_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void WaitSecondsTestFinished();

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void WaitTicksTest();
	FECFCoroutine WaitTicksTest_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void WaitTicksTestFinished();

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void DelayTicksTest();

	UFUNCTION(BlueprintImplementableEvent)
	void DelayTicksTestFinished();

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void TickerTest();

	UFUNCTION(BlueprintImplementableEvent)
	void TickerTestFinished(bool bStopped);

	UFUNCTION(BlueprintImplementableEvent)
	void SetTickerValue_BP(float NewValue);

	float TickerValue = 0.f;

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	int32 TimelinesTestsCount = 0;

	UFUNCTION(BlueprintCallable)
	void TimelineTest(EECFBlendFunc TimelineFunc, float StartValue, float StopValue);

	UFUNCTION(BlueprintCallable)
	void TimelineTestVec(EECFBlendFunc TimelineFunc, FVector StartValue, FVector StopValue);

	UFUNCTION(BlueprintImplementableEvent)
	void TimelineTestFinished();

	UFUNCTION(BlueprintImplementableEvent)
	void SetTimelineValue_BP(float NewValue, float NewTime);

	UFUNCTION(BlueprintImplementableEvent)
	void SetTimelineValueVec_BP(FVector NewValue, float NewTime);

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

	float WaitAndExecuteTime = 0.f;

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void WaitUntilTest(float TimeOut);
	FECFCoroutine WaitUntilTest_Implementation(float TimeOut);

	UFUNCTION(BlueprintImplementableEvent)
	void WaitUntilTestFinished();

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
	void RunAsyncTaskThenTest(float TimeOut = 0.f, EECFAsyncPrio Prio = EECFAsyncPrio::Normal);

	UFUNCTION(BlueprintImplementableEvent)
	void RunAsyncTaskThenTestFinished(bool bTimedOut);

	/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

	UFUNCTION(BlueprintCallable)
	void RunAsyncAndWaitTest(float TimeOut = 0.f, EECFAsyncPrio Prio = EECFAsyncPrio::Normal);
	FECFCoroutine RunAsyncAndWaitTest_Implementation(float TimeOut, EECFAsyncPrio Prio);

	UFUNCTION(BlueprintImplementableEvent)
	void RunAsyncAndWaitTestFinished();

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
