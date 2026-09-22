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

#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"
#include "Freeze/Model/Cache/Stage.h"
#include "Freeze/Model/Cache/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Freeze::Domain::Model
{

    FStageDomain::FStageDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Freeze::Domain::FGs2FreezeDomainPtr& Service,
        const TOptional<FString> StageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Freeze::FGs2FreezeRestClient>(Gs2->RestSession)),
        StageName(StageName),
        ParentKey("freeze:Stage")
    {
    }

    FStageDomain::FStageDomain(
        const FStageDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StageName(From.StageName),
        ParentKey(From.ParentKey)
    {

    }

    FStageDomain::FGetTask::FGetTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FGetStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->GetStage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Freeze::Model::Cache::FStageCache::Put(
            Self->Gs2->Cache,

            Request->GetStageName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FGetTask>> FStageDomain::Get(
        Request::FGetStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStageDomain::FPromoteTask::FPromoteTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FPromoteStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FPromoteTask::FPromoteTask(
        const FPromoteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FPromoteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->PromoteStage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Freeze::Model::Cache::FStageCache::Put(
            Self->Gs2->Cache,

            Request->GetStageName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FPromoteTask>> FStageDomain::Promote(
        Request::FPromoteStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPromoteTask>>(this->AsShared(), Request);
    }

    FStageDomain::FRollbackTask::FRollbackTask(
        const TSharedPtr<FStageDomain>& Self,
        const Request::FRollbackStageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStageDomain::FRollbackTask::FRollbackTask(
        const FRollbackTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FRollbackTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStageName(Self->StageName);
        const auto Future = Self->Client->RollbackStage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {


        Gs2::Freeze::Model::Cache::FStageCache::Put(
            Self->Gs2->Cache,

            Request->GetStageName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FRollbackTask>> FStageDomain::Rollback(
        Request::FRollbackStageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRollbackTask>>(this->AsShared(), Request);
    }

    Gs2::Freeze::Domain::Iterator::FDescribeOutputsIteratorPtr FStageDomain::Outputs(
    ) const
    {
        return MakeShared<Gs2::Freeze::Domain::Iterator::FDescribeOutputsIterator>(
            Gs2,
            Client,
            StageName
        );
    }

    Gs2::Core::Domain::CallbackID FStageDomain::SubscribeOutputs(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
                StageName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FStageDomain::UnsubscribeOutputs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
                StageName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FStageDomain::FCollectOutputsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Freeze::Model::FOutputPtr>>, public TSharedFromThis<FCollectOutputsTask>
    {
        const TSharedPtr<FStageDomain> Self;
        const TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)> OnCollected;

    public:
        explicit FCollectOutputsTask(const TSharedPtr<FStageDomain>& Self, TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectOutputsTask(const FCollectOutputsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Freeze::Model::FOutputPtr>>> Result) override
        {
            TArray<Gs2::Freeze::Model::FOutputPtr> Items;
            auto Iterator = Self->Outputs()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Freeze::Model::FOutputPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FStageDomain::SubscribeOutputs(
        TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Freeze::Domain::FGs2FreezeDomain> WeakService = this->Service;
        const auto QueryStageName = StageName;
        const auto Parent = Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
        StageName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Freeze::Model::FOutput::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Freeze::Model::FOutputPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Freeze::Model::FOutput>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryStageName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FStageDomain>(Owner, WeakService.Pin(), QueryStageName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectOutputsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FStageDomain::InvalidateOutputs()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Freeze::Model::FOutput::TypeName,
            Gs2::Freeze::Model::Cache::FOutputCache::CreateCacheParentKey(
        StageName,
        TOptional<int32>()
    )
        );
    }

    FStageDomain::FSubscribeOutputsWithInitialCallTask::FSubscribeOutputsWithInitialCallTask(const TSharedPtr<FStageDomain>& Self, TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FStageDomain::FSubscribeOutputsWithInitialCallTask::FSubscribeOutputsWithInitialCallTask(const FSubscribeOutputsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FSubscribeOutputsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectOutputsTask>>(Self, TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeOutputs(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FStageDomain::FSubscribeOutputsWithInitialCallTask>> FStageDomain::SubscribeOutputsWithInitialCall(TFunction<void(TArray<Gs2::Freeze::Model::FOutputPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeOutputsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Freeze::Domain::Model::FOutputDomain> FStageDomain::Output(
        const FString OutputName
    )
    {
        return MakeShared<Gs2::Freeze::Domain::Model::FOutputDomain>(
            Gs2,
            Service,
            StageName,
            OutputName == TEXT("") ? TOptional<FString>() : TOptional<FString>(OutputName)
        );
    }

    FString FStageDomain::CreateCacheParentKey(
        TOptional<FString> StageName,
        FString ChildType
    )
    {
        return FString("") +
            (StageName.IsSet() ? *StageName : "null") + ":" +
            ChildType;
    }

    FString FStageDomain::CreateCacheKey(
        TOptional<FString> StageName
    )
    {
        return FString("") +
            (StageName.IsSet() ? *StageName : "null");
    }

    FStageDomain::FModelTask::FModelTask(
        const TSharedPtr<FStageDomain> Self
    ): Self(Self)
    {

    }

    FStageDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Freeze::Model::FStage>> Result
    )
    {
        const auto CacheParentKey = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheKey(

            Self->StageName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Freeze::Model::FStage::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Freeze::Model::FStagePtr Value;
                const auto CacheHit = Gs2::Freeze::Model::Cache::FStageCache::TryGet(
                    Self->Gs2->Cache,

                    Self->StageName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Freeze::Model::Cache::FStageCache::Fetch(
                    Self->Gs2->Cache,

                    Self->StageName,
                    TOptional<int32>(),
                    [Self](Gs2::Freeze::Model::FStagePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Freeze::Request::FGetStageRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FStageDomain::FModelTask>> FStageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStageDomain::FModelTask>>(this->AsShared());
    }

    void FStageDomain::Invalidate()
    {
        Gs2::Freeze::Model::Cache::FStageCache::Delete(
            Gs2->Cache,

            StageName,
            TOptional<int32>()
        );
    }

    FStageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FStageDomain>& Self,
        TFunction<void(Gs2::Freeze::Model::FStagePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FStageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStageDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStageDomain::FSubscribeWithInitialCallTask>> FStageDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Freeze::Model::FStagePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FStageDomain::Subscribe(
        TFunction<void(Gs2::Freeze::Model::FStagePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheKey(

            StageName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Freeze::Domain::FGs2FreezeDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryStageName = StageName;
        return Gs2->Cache->Subscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Freeze::Model::FStage>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryStageName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FStageDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryStageName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FStageDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Freeze::Model::Cache::FStageCache::CreateCacheKey(

            StageName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
