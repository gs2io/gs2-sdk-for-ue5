/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Core/Model/Gs2Error.h"
#include "../../Gs2Core/Gs2Core.h"

#include <atomic>

namespace Gs2::Core::Util
{
    template <class TResult>
    class TGs2Future :
        public FNonAbandonableTask
    {
        friend class FAutoDeleteAsyncTask<TGs2Future>;

    public:
        DECLARE_DELEGATE_OneParam(FSuccessDelegate, TSharedPtr<TResult>);
        DECLARE_DELEGATE_OneParam(FErrorDelegate, Model::FGs2ErrorPtr);

        struct DelegateContext
        {
            FSuccessDelegate SuccessDelegate;
            FErrorDelegate ErrorDelegate;

            DelegateContext() = default;

            DelegateContext(const DelegateContext& From) :
                SuccessDelegate(From.SuccessDelegate),
                ErrorDelegate(From.ErrorDelegate)
            {}
        };

    private:
        TSharedPtr<TResult> ResultValue;
        Model::FGs2ErrorPtr ErrorValue;
        std::atomic<bool> Complete;

        TSharedRef<DelegateContext> Delegates;
    
    public:
        TGs2Future(
        ): ResultValue(nullptr), ErrorValue(MakeShared<Model::FNotExecutedError>(MakeShared<TArray<Model::FGs2ErrorDetailPtr>>())), Complete(false), Delegates(MakeShared<DelegateContext>())
        {
            
        }

        TGs2Future(
            const TGs2Future& From
        ): ResultValue(From.ResultValue), ErrorValue(From.ErrorValue), Complete(From.Complete.load(std::memory_order_acquire)), Delegates(From.Delegates)
        {
            
        }

        TGs2Future& operator=(const TGs2Future& From)
        {
            if (this != &From)
            {
                this->ResultValue = From.ResultValue;
                this->ErrorValue = From.ErrorValue;
                this->Complete.store(From.Complete.load(std::memory_order_acquire), std::memory_order_release);
                this->Delegates = From.Delegates;
            }
            return *this;
        }

        virtual ~TGs2Future() = default;
        
        virtual Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TResult>> Result)
        {
            return nullptr;
        }
    
        bool IsComplete() const
        {
            return this->Complete.load(std::memory_order_acquire);
        }

        bool IsError() const
        {
            return ErrorValue != nullptr && ErrorValue.IsValid();
        }

        FSuccessDelegate& OnSuccessDelegate()
        {
            return this->Delegates->SuccessDelegate;
        }

        FErrorDelegate& OnErrorDelegate()
        {
            return this->Delegates->ErrorDelegate;
        }

        TSharedPtr<TResult> Result() const
        {
            return this->ResultValue;
        }

        Model::FGs2ErrorPtr Error() const
        {
            return this->ErrorValue;
        }

        void DoWork()
        {
            TSharedPtr<TSharedPtr<TResult>> Result = MakeShared<TSharedPtr<TResult>>();
            auto Error = this->Action(Result);
            if (Error)
            {
                this->OnError(Error);
            } else
            {
                this->OnComplete(*Result);
            }
        }
        
        FORCEINLINE TStatId GetStatId() const
        {
            RETURN_QUICK_DECLARE_CYCLE_STAT(TGs2Future, STATGROUP_ThreadPoolAsyncTasks);
        }

    protected:
        
        virtual void OnError(Model::FGs2ErrorPtr Error)
        {
            this->ResultValue = nullptr;
            this->ErrorValue = Error;
            this->Complete.store(true, std::memory_order_release);
            FGs2Ticker::EntryInvokeFromGameThreads([Delegates=this->Delegates, Error]
            {
                // ReSharper disable once CppExpressionWithoutSideEffects
                Delegates->ErrorDelegate.ExecuteIfBound(Error);
            });
        }
    
        virtual void OnComplete(TSharedPtr<TResult> Result)
        {
            this->ErrorValue = nullptr;
            this->ResultValue = Result;
            this->Complete.store(true, std::memory_order_release);
            FGs2Ticker::EntryInvokeFromGameThreads([Delegates=this->Delegates, Result]
            {
                // ReSharper disable once CppExpressionWithoutSideEffects
                Delegates->SuccessDelegate.ExecuteIfBound(Result);
            });
        }
    };

    GS2CORE_API extern TArray<TSharedPtr<FAsyncTaskBase>> RunningTasks;
    GS2CORE_API void RegisterRunningTask(const TSharedPtr<FAsyncTaskBase>& Task);

    template <typename InObjectType, typename... InArgTypes>
    static TSharedPtr<InObjectType> New(InArgTypes&&... Args)
    {
        // SDK tasks are single-use. Keep a strong pointer while starting or waiting. After
        // releasing the caller's last strong pointer, do not start, reuse, or synchronize
        // the task by pinning a weak pointer.
        auto Future = MakeShared<InObjectType>(Args...);
        RegisterRunningTask(Future);
        return Future;
    }

}
