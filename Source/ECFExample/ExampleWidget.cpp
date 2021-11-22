// Copyright (c) 2021 Damian Nowakowski. All rights reserved.

#include "ExampleWidget.h"
#include "EnhancedCodeFlow.h"

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::AddToLog_Internal(FString Log)
{
	AddToLog(FDateTime::Now().ToString() + TEXT(": ") + Log);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::DelayTest()
{
	AddToLog_Internal(TEXT("Start Delay Test"));
	FFlow::Delay(this, 2.f, [this]()
	{
		AddToLog_Internal(TEXT("Delay Test Finished"));
		DelayTestFinished();
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::TickerTest()
{
	AddToLog_Internal(TEXT("Start Ticker Test"));

	TickerValue = 0.f;
	SetTickerValue_BP(TickerValue);

	FFlow::AddTicker(this, [this](float DeltaTime, FECFHandle TickerHandle)
	{
		TickerValue += DeltaTime;
		SetTickerValue_BP(TickerValue);

		if (TickerValue >= 2.f)
		{
			AddToLog_Internal(TEXT("Ticker Test Finished"));
			FFlow::StopAction(this, TickerHandle);
			TickerTestFinished();
		}
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::TimelineTest(EECFBlendFunc TimelineFunc, float StartValue, float StopValue)
{
	AddToLog_Internal(TEXT("Start Timeline Test"));

	SetTimelineValue_BP(0.f, 0.f);

	FFlow::AddTimeline(this, StartValue, StopValue, 2.f, [this](float Value, float Time)
	{
		SetTimelineValue_BP(Value, Time);
	}, [this](float Value, float Time)
	{
		SetTimelineValue_BP(Value, Time);
		AddToLog_Internal(TEXT("Timeline Test Finished"));
		TimelineTestFinished();
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
	}, [this](float Value, float Time)
	{
		SetCustomTimelineValue_BP(Value, Time);
		AddToLog_Internal(TEXT("Custom Timeline Test Finished"));
		CustomTimelineTestFinished();
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::WaitAndExecuteTest()
{
	AddToLog_Internal(TEXT("Start Wait And Execute Test"));
	FFlow::WaitAndExecute(this, [this]()
	{
		return bWaitAndExecuteConditional;
	},
	[this]()
	{
		AddToLog_Internal(TEXT("Wait And Execute Test Finished"));
		WaitAndExecuteTestFinished();
	});
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void UExampleWidget::WhileTrueExecuteTest()
{
	AddToLog_Internal(TEXT("Start While True Execute Test"));
	WhileTrueExecuteTickerValue = 0.f;
	FFlow::WhileTrueExecute(this, [this]()
	{
		if (bWhileTrueExecuteConditional == false)
		{
			AddToLog_Internal(TEXT("While True Execute Test Finished"));
			WhileTrueExecuteTestFinished();
		}
		return bWhileTrueExecuteConditional;
	},
	[this](float DeltaTime)
	{
		WhileTrueExecuteTickerValue += DeltaTime;
		SetWhileTrueExecuteTickerValue_BP(WhileTrueExecuteTickerValue);
	});
}

void UExampleWidget::TimeLockTest(ETimeLockTestType Type)
{
	if (Type == ETimeLockTestType::TL2Sec)
	{
		AddToLog_Internal(TEXT("Start TimeLock 2 sec Test"));

		static FECFInstanceId Inst2Sec = FECFInstanceId::NewId();
		FFlow::TimeLock(this, 2.f, [this]()
		{
			AddToLog_Internal(TEXT("TimeLock 2 sec Is Opened"));
		}, Inst2Sec);
	}
	else if (Type == ETimeLockTestType::TL5Sec)
	{
		AddToLog_Internal(TEXT("Start TimeLock 5 sec Test"));

		static FECFInstanceId Inst5Sec = FECFInstanceId::NewId();
		FFlow::TimeLock(this, 5.f, [this]()
		{
			AddToLog_Internal(TEXT("TimeLock 5 sec Is Opened"));
		}, Inst5Sec);
	}
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
