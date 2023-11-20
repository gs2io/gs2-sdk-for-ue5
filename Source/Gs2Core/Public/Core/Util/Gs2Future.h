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

        TSharedRef<DelegateContext> Delegates;
    
    public:
        TGs2Future(
        ): ResultValue(nullptr), ErrorValue(MakeShared<Model::FNotExecutedError>(MakeShared<TArray<Model::FGs2ErrorDetailPtr>>())), Delegates(MakeShared<DelegateContext>())
        {
            
        }

        TGs2Future(
            const TGs2Future& From
        ): ResultValue(From.ResultValue), ErrorValue(From.ErrorValue), Delegates(From.Delegates)
        {
            
        }

        virtual ~TGs2Future() = default;
        
        virtual Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TResult>> Result)
        {
            return nullptr;
        }
    
        bool IsComplete() const
        {
            return (ResultValue != nullptr && ResultValue.IsValid()) || (ErrorValue != nullptr && ErrorValue.IsValid());
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
            FGs2Ticker::EntryInvokeFromGameThreads([Delegates=this->Delegates, Error]
            {
                // ReSharper disable once CppExpressionWithoutSideEffects
                Delegates->ErrorDelegate.ExecuteIfBound(Error);
            });
            this->ErrorValue = Error;
        }
    
        virtual void OnComplete(TSharedPtr<TResult> Result)
        {
            FGs2Ticker::EntryInvokeFromGameThreads([Delegates=this->Delegates, Result]
            {
                // ReSharper disable once CppExpressionWithoutSideEffects
                Delegates->SuccessDelegate.ExecuteIfBound(Result);
            });
            this->ErrorValue = nullptr;
            this->ResultValue = Result;
        }
    };

    GS2CORE_API extern TArray<TSharedPtr<FAsyncTaskBase>> RunningTasks;

    template <typename InObjectType, typename... InArgTypes>
    static TSharedPtr<InObjectType> New(InArgTypes&&... Args)
    {
        for (auto Iterator = RunningTasks.CreateIterator(); Iterator; ++Iterator)
        {
            if ((*Iterator)->IsDone()) Iterator.RemoveCurrent();
        }
        
        auto Future = MakeShared<InObjectType>(Args...);
        RunningTasks.Add(Future);
        return Future;
    }

}
