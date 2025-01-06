// Copyright (c) 2024 Damian Nowakowski. All rights reserved.

#include "ExampleWidget.h"
#include "EnhancedCodeFlow.h"
#include "ExampleActor.h"

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::CoroActorTest()
{
	if (ExActor)
	{
		return;
	}

	ExActor = GetWorld()->SpawnActor<AExampleActor>();
}

void UExampleWidget::ForceGC()
{
	GEngine->ForceGarbageCollection(true);
}

void UExampleWidget::AddToLog_Internal(FString Log, bool bStopped/* = false*/)
{
	if (bStopped)
	{
		Log += TEXT(" (Stopped)");
	}
	AddToLog(FDateTime::Now().ToString() + TEXT(": ") + Log);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::DelayTest()
{
	AddToLog_Internal(TEXT("Start Delay Test"));
	FFlow::Delay(this, 2.f, [this](bool bStopped)
	{
		AddToLog_Internal(TEXT("Delay Test Finished"), bStopped);
		DelayTestFinished();
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::WaitSecondsTest()
{
	WaitSecondsTest_Implementation();
}

FECFCoroutine UExampleWidget::WaitSecondsTest_Implementation()
{
#ifdef __cpp_impl_coroutine
	AddToLog_Internal(TEXT("Start Wait Three Test"));
	co_await FFlow::WaitSeconds(this, 1.f);
	AddToLog_Internal(TEXT("Wait Test Finished 1/3"));
	co_await FFlow::WaitSeconds(this, 1.f);
	AddToLog_Internal(TEXT("Wait Test Finished 2/3"));
	co_await FFlow::WaitSeconds(this, 1.f);
	AddToLog_Internal(TEXT("Wait Test Finished 3/3"));
	WaitSecondsTestFinished();
#endif
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::WaitTicksTest()
{
	WaitTicksTest_Implementation();
}

FECFCoroutine UExampleWidget::WaitTicksTest_Implementation()
{
#ifdef __cpp_impl_coroutine
	AddToLog_Internal(TEXT("Start Wait Ticks Test"));
	co_await FFlow::WaitTicks(this, 100);
	AddToLog_Internal(TEXT("Wait Ticks Test Finished"));
	WaitTicksTestFinished();
#endif
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::DelayTicksTest()
{
	AddToLog_Internal(TEXT("Start Delay Ticks Test"));
	FFlow::DelayTicks(this, 100, [this](bool bStopped)
	{
		AddToLog_Internal(TEXT("Delay Test Ticks Finished"), bStopped);
		DelayTicksTestFinished();
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::TickerTest()
{
	AddToLog_Internal(TEXT("Start Ticker Test"));

	TickerValue = 0.f;
	SetTickerValue_BP(TickerValue);

	FFlow::AddTicker(this, 2.f,
	[this](float DeltaTime)
	{
		TickerValue += DeltaTime;
		SetTickerValue_BP(TickerValue);
	},
	[this](bool bStopped)
	{
		AddToLog_Internal(TEXT("Ticker Test Finished"), bStopped);
		TickerTestFinished(bStopped);
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::TimelineTest(EECFBlendFunc TimelineFunc, float StartValue, float StopValue)
{
	AddToLog_Internal(TEXT("Start Timeline Test"));

	SetTimelineValue_BP(0.f, 0.f);

	TimelinesTestsCount++;
	FFlow::AddTimeline(this, StartValue, StopValue, 2.f, [this](float Value, float Time)
	{
		SetTimelineValue_BP(Value, Time);
	}, [this](float Value, float Time)
	{
		SetTimelineValue_BP(Value, Time);
		AddToLog_Internal(TEXT("Timeline Test Finished"), false);
		TimelinesTestsCount--;
		if (TimelinesTestsCount <= 0)
		{
			TimelineTestFinished();
		}
	}, TimelineFunc, 2.f);
}

void UExampleWidget::TimelineTestVec(EECFBlendFunc TimelineFunc, FVector StartValue, FVector StopValue)
{
	AddToLog_Internal(TEXT("Start Timeline Test Vec"));

	SetTimelineValueVec_BP(FVector(0,0,0), 0.f);

	TimelinesTestsCount++;
	FFlow::AddTimelineVector(this, StartValue, StopValue, 2.f, [this](FVector Value, float Time)
	{
		SetTimelineValueVec_BP(Value, Time);
	}, [this](FVector Value, float Time)
	{
		SetTimelineValueVec_BP(Value, Time);
		AddToLog_Internal(TEXT("Timeline Test Finished Vec"), false);
		TimelinesTestsCount--;
		if (TimelinesTestsCount <= 0)
		{
			TimelineTestFinished();
		}
	}, TimelineFunc, 2.f);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::CustomTimelineTest(UCurveFloat* Curve)
{
	AddToLog_Internal(TEXT("Start Custom Timeline Test"));

	SetCustomTimelineValue_BP(0.f, 0.f);

	FFlow::AddCustomTimeline(this, Curve, [this](float Value, float Time)
	{
		SetCustomTimelineValue_BP(Value, Time);
	}, [this](float Value, float Time, bool bStopped)
	{
		SetCustomTimelineValue_BP(Value, Time);
		AddToLog_Internal(TEXT("Custom Timeline Test Finished"), bStopped);
		CustomTimelineTestFinished();
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::WaitAndExecuteTest(float TimeOut)
{
	AddToLog_Internal(TEXT("Start Wait And Execute Test"));
	WaitAndExecuteTime = 0.f;
	FFlow::WaitAndExecute(this, [this](float DeltaTime)
	{
		WaitAndExecuteTime += DeltaTime;
		return bWaitAndExecuteConditional;
	},
	[this](bool bTimedOut, bool bStopped)
	{
		if (bTimedOut)
		{
			AddToLog_Internal(FString::Printf(TEXT("Wait And Execute Test Finished - TimeOut!\n>>> Total Time: %f"), WaitAndExecuteTime), bStopped);
		}
		else
		{
			AddToLog_Internal(FString::Printf(TEXT("Wait And Execute Test Finished.\n>>> Total Time: %f"), WaitAndExecuteTime), bStopped);
		}
		WaitAndExecuteTestFinished(bTimedOut);
	}, TimeOut);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::WaitUntilTest(float TimeOut)
{
	WaitUntilTest_Implementation(TimeOut);
}

FECFCoroutine UExampleWidget::WaitUntilTest_Implementation(float TimeOut)
{
#ifdef __cpp_impl_coroutine
	AddToLog_Internal(TEXT("Start Wait Until Test"));
	WaitAndExecuteTime = 0.f;
	co_await FFlow::WaitUntil(this, [this](float DeltaTime)
	{
		WaitAndExecuteTime += DeltaTime;
		return bWaitAndExecuteConditional;
	}, TimeOut);
	AddToLog_Internal(FString::Printf(TEXT("Wait Until Test Finished\n>>> Total Time: %f"), WaitAndExecuteTime));
	WaitUntilTestFinished();
#endif
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::WhileTrueExecuteTest(float TimeOut/* = 0.f*/)
{
	AddToLog_Internal(TEXT("Start While True Execute Test"));
	WhileTrueExecuteTickerValue = 0.f;
	FFlow::WhileTrueExecute(this, [this]()
	{
		return bWhileTrueExecuteConditional;
	},
	[this](float DeltaTime)
	{
		WhileTrueExecuteTickerValue += DeltaTime;
		SetWhileTrueExecuteTickerValue_BP(WhileTrueExecuteTickerValue);
	}, 
	[this](bool bTimedOut, bool bStopped)
	{
		if (bTimedOut)
		{
			AddToLog_Internal(TEXT("While True Execute Test Finished - TimeOut!"), bStopped);
		}
		else
		{
			AddToLog_Internal(TEXT("While True Execute Test Finished"), bStopped);
		}
		WhileTrueExecuteTestFinished(bTimedOut);
	},
	TimeOut);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::RunAsyncTaskThenTest(float TimeOut, EECFAsyncPrio Prio)
{
	AddToLog_Internal(TEXT("Start Run Async Task Then Test"));

	FFlow::RunAsyncThen(this, [this]()
	{
		int32 Count = 0;
		while (Count < 3)
		{
			Count++;
			FPlatformProcess::Sleep(1.f);
		}
	},
	[this](bool bTimedOut, bool bStopped)
	{
		if (bTimedOut)
		{
			AddToLog_Internal(TEXT("Run Async Task Then Test Finished - TimeOut!"), bStopped);
		}
		else
		{
			AddToLog_Internal(TEXT(" Run Async Task Then Test Finished"), bStopped);
		}
		RunAsyncTaskThenTestFinished(bTimedOut);
	},
	TimeOut, Prio);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::RunAsyncAndWaitTest(float TimeOut, EECFAsyncPrio Prio)
{
	RunAsyncAndWaitTest_Implementation(TimeOut,  Prio);
}

FECFCoroutine UExampleWidget::RunAsyncAndWaitTest_Implementation(float TimeOut, EECFAsyncPrio Prio)
{
#ifdef __cpp_impl_coroutine
	AddToLog_Internal(TEXT("Start Run Async And Wait Test"));
	co_await FFlow::RunAsyncAndWait(this, [this]()
	{
		int32 Count = 0;
		while (Count < 3)
		{
			Count++;
			FPlatformProcess::Sleep(1.f);
		}
	}, TimeOut, Prio);
	AddToLog_Internal(TEXT("Run Async And Wait Test Finished"));
	RunAsyncAndWaitTestFinished();
#endif
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::TimeLockTest(ETimeLockTestType Type)
{
	if (Type == ETimeLockTestType::TL2Sec)
	{
		static FECFInstanceId Inst2Sec = FECFInstanceId::NewId();
		FFlow::TimeLock(this, 2.f, [this]()
		{
			AddToLog_Internal(TEXT("TimeLock 2 sec Is Opened"));
		}, Inst2Sec);
	}
	else if (Type == ETimeLockTestType::TL5Sec)
	{
		static FECFInstanceId Inst5Sec = FECFInstanceId::NewId();
		FFlow::TimeLock(this, 5.f, [this]()
		{
			AddToLog_Internal(TEXT("TimeLock 5 sec Is Opened"));
		}, Inst5Sec);
	}
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

static FECFInstanceId DoOnceInst = FECFInstanceId::NewId();
void UExampleWidget::DoOnceTest()
{
	FFlow::DoOnce(this, [this]()
	{
		AddToLog_Internal(TEXT("DoOnce Test"));
	}, DoOnceInst);
}

void UExampleWidget::ResetDoOnce()
{
	FFlow::StopInstancedAction(GetWorld(), DoOnceInst);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

static FECFInstanceId DoNTimesInst = FECFInstanceId::NewId();
void UExampleWidget::DoNTimesTest(int32 Times)
{
	if (Times > 0)
	{
		FFlow::DoNTimes(this, Times, [this](int32 Counter)
		{
			AddToLog_Internal(FString::Printf(TEXT("DoNTimes Test, counter: %i"), Counter));
		}, DoNTimesInst);
	}
}

void UExampleWidget::ResetDoNTimes()
{
	FFlow::StopInstancedAction(GetWorld(), DoNTimesInst);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

static FECFInstanceId DoNoMoreThanXTimeInst = FECFInstanceId::NewId();
void UExampleWidget::DoNoMoreThanXTime(float Time/* = 5.f*/, int32 MaxExecsEnqueue/* = 1*/)
{
	FFlow::DoNoMoreThanXTime(this, [this]()
	{
		AddToLog_Internal(TEXT("Do No More Than X Times Executed"));
	}, Time, MaxExecsEnqueue, DoNoMoreThanXTimeInst);
}
