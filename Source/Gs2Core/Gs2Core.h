// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"

class GS2CORE_API FGs2Ticker : 
	public FTickableGameObject
{
	static FCriticalSection Mutex;
	static TArray<TFunction<void()>> InvokeFromGameThreads;
	
public:
	virtual void Tick(float DeltaTime) override;
        
	virtual bool IsTickable() const { return(true); }
        
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(UGs2Ticker, STATGROUP_Tickables);
	}

	virtual bool IsTickableInEditor() const override { return true; }
	
	static void EntryInvokeFromGameThreads(TFunction<void()> Func)
	{
		Mutex.Lock();
		InvokeFromGameThreads.Add(Func);
		Mutex.Unlock();
	}
};
static FGs2Ticker* Gs2TickerObject = nullptr;
