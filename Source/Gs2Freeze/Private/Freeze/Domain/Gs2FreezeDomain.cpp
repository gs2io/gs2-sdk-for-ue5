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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Freeze/Domain/Gs2Freeze.h"
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"

#include "Freeze/Model/Cache/Stage.h"
#include "Freeze/Model/Cache/Output.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Freeze::Domain
{

    FGs2FreezeDomain::FGs2FreezeDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Freeze::FGs2FreezeRestClient>(Gs2->RestSession)),
        ParentKey("freeze")
    {
    }

    FGs2FreezeDomain::FGs2FreezeDomain(
        const FGs2FreezeDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Freeze::Domain::Iterator::FDescribeStagesIteratorPtr FGs2FreezeDomain::Stages(
    ) const
    {
        return MakeShared<Gs2::Freeze::Domain::Iterator::FDescribeStagesIterator>(
            Gs2,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2FreezeDomain::SubscribeStages(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2FreezeDomain::UnsubscribeStages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2FreezeDomain::FCollectStagesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Freeze::Model::FStagePtr>>, public TSharedFromThis<FCollectStagesTask>
    {
        const TSharedPtr<FGs2FreezeDomain> Self;
        const TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> OnCollected;

    public:
        explicit FCollectStagesTask(const TSharedPtr<FGs2FreezeDomain>& Self, TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectStagesTask(const FCollectStagesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Freeze::Model::FStagePtr>>> Result) override
        {
            TArray<Gs2::Freeze::Model::FStagePtr> Items;
            auto Iterator = Self->Stages()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Freeze::Model::FStagePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2FreezeDomain::SubscribeStages(
        TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto Parent = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Freeze::Model::FStage::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Freeze::Model::FStagePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Freeze::Model::FStage>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2FreezeDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStagesTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2FreezeDomain::InvalidateStages()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Freeze::Model::FStage::TypeName,
            Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2FreezeDomain::FSubscribeStagesWithInitialCallTask::FSubscribeStagesWithInitialCallTask(const TSharedPtr<FGs2FreezeDomain>& Self, TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> Callback) : Self(Self), Callback(Callback) {}
    FGs2FreezeDomain::FSubscribeStagesWithInitialCallTask::FSubscribeStagesWithInitialCallTask(const FSubscribeStagesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2FreezeDomain::FSubscribeStagesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStagesTask>>(Self, TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStages(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2FreezeDomain::FSubscribeStagesWithInitialCallTask>> FGs2FreezeDomain::SubscribeStagesWithInitialCall(TFunction<void(TArray<Gs2::Freeze::Model::FStagePtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStagesWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain> FGs2FreezeDomain::Stage(
        const FString StageName
    )
    {
        return MakeShared<Gs2::Freeze::Domain::Model::FStageDomain>(
            Gs2,
            AsShared(),
            StageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StageName)
        );
    }

    void FGs2FreezeDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2FreezeDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2FreezeDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2FreezeDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
