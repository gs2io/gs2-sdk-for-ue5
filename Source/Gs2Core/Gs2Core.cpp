// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gs2Core.h"

#include "Modules/ModuleManager.h"
#if WITH_EDITOR
#include "Editor.h"
#endif

#include "WebSocketsModule.h"

class FGs2Module : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule()
	{
		Gs2TickerObject = new FGs2Ticker();

		FModuleManager::LoadModuleChecked<FWebSocketsModule>("WebSockets");
	}

	virtual void ShutdownModule()
	{
		delete Gs2TickerObject;
		Gs2TickerObject = nullptr;
	}
};

void FGs2Ticker::Tick(float DeltaTime)
{
	Mutex.Lock();

#if WITH_EDITOR
	if (GIsEditor)
	{
		if (GEditor->PlayWorld || GIsPlayInEditorWorld)
		{
			for (auto Func : InvokeFromGameThreads)
			{
				Func();
			}
		}
		InvokeFromGameThreads.Reset();
	}
	else
	{
#endif
	for (auto Func : InvokeFromGameThreads)
	{
		Func();
	}
	InvokeFromGameThreads.Reset();
#if WITH_EDITOR
	}
#endif
	
	Mutex.Unlock();
}

FCriticalSection FGs2Ticker::Mutex;
TArray<TFunction<void()>> FGs2Ticker::InvokeFromGameThreads;

IMPLEMENT_MODULE( FGs2Module, Gs2 );
