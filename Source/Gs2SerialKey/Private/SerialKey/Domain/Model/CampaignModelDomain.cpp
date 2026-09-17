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

#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/Namespace.h"
#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/UserAccessToken.h"
#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/CampaignModelMaster.h"
#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"
#include "SerialKey/Model/Cache/CampaignModel.h"
#include "SerialKey/Model/Cache/IssueJob.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FCampaignModelDomain::FCampaignModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CampaignModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        CampaignModelName(CampaignModelName),
        ParentKey(Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CampaignModel"
        ))
    {
    }

    FCampaignModelDomain::FCampaignModelDomain(
        const FCampaignModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        CampaignModelName(From.CampaignModelName),
        ParentKey(From.ParentKey)
    {

    }

    FCampaignModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FCampaignModelDomain>& Self,
        const Request::FGetCampaignModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCampaignModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName);
        const auto Future = Self->Client->GetCampaignModel(
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


        Gs2::SerialKey::Model::Cache::FCampaignModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetCampaignModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCampaignModelDomain::FGetTask>> FCampaignModelDomain::Get(
        Request::FGetCampaignModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCampaignModelDomain::FIssueTask::FIssueTask(
        const TSharedPtr<FCampaignModelDomain>& Self,
        const Request::FIssueRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCampaignModelDomain::FIssueTask::FIssueTask(
        const FIssueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FIssueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FIssueJobDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName);
        const auto Future = Self->Client->Issue(
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


        Gs2::SerialKey::Model::Cache::FIssueJobCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetCampaignModelName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::SerialKey::Domain::Model::FIssueJobDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetCampaignModelName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCampaignModelDomain::FIssueTask>> FCampaignModelDomain::Issue(
        Request::FIssueRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIssueTask>>(this->AsShared(), Request);
    }

    Gs2::SerialKey::Domain::Iterator::FDescribeIssueJobsIteratorPtr FCampaignModelDomain::IssueJobs(
    ) const
    {
        return MakeShared<Gs2::SerialKey::Domain::Iterator::FDescribeIssueJobsIterator>(
            Gs2,
            Client,
            NamespaceName,
            CampaignModelName
        );
    }

    Gs2::Core::Domain::CallbackID FCampaignModelDomain::SubscribeIssueJobs(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::SerialKey::Model::FIssueJob::TypeName,
            Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheParentKey(
                NamespaceName,
                CampaignModelName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FCampaignModelDomain::UnsubscribeIssueJobs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::SerialKey::Model::FIssueJob::TypeName,
            Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheParentKey(
                NamespaceName,
                CampaignModelName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FCampaignModelDomain::FCollectIssueJobsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::SerialKey::Model::FIssueJobPtr>>, public TSharedFromThis<FCollectIssueJobsTask>
    {
        const TSharedPtr<FCampaignModelDomain> Self;
        const TFunction<void(TArray<Gs2::SerialKey::Model::FIssueJobPtr>)> OnCollected;

    public:
        explicit FCollectIssueJobsTask(const TSharedPtr<FCampaignModelDomain>& Self, TFunction<void(TArray<Gs2::SerialKey::Model::FIssueJobPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectIssueJobsTask(const FCollectIssueJobsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::SerialKey::Model::FIssueJobPtr>>> Result) override
        {
            TArray<Gs2::SerialKey::Model::FIssueJobPtr> Items;
            auto Iterator = Self->IssueJobs()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::SerialKey::Model::FIssueJobPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FCampaignModelDomain::SubscribeIssueJobs(
        TFunction<void(TArray<Gs2::SerialKey::Model::FIssueJobPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<SerialKey::Domain::FGs2SerialKeyDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryCampaignModelName = CampaignModelName;
        const auto Parent = Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheParentKey(
        NamespaceName,
        CampaignModelName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::SerialKey::Model::FIssueJob::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::SerialKey::Model::FIssueJobPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::SerialKey::Model::FIssueJob>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryCampaignModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FCampaignModelDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryCampaignModelName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIssueJobsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FCampaignModelDomain::InvalidateIssueJobs()
    {
        Gs2->Cache->ClearListCache(
            Gs2::SerialKey::Model::FIssueJob::TypeName,
            Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheParentKey(
        NamespaceName,
        CampaignModelName,
        TOptional<int32>()
    )
        );
    }

    FCampaignModelDomain::FSubscribeIssueJobsWithInitialCallTask::FSubscribeIssueJobsWithInitialCallTask(const TSharedPtr<FCampaignModelDomain>& Self, TFunction<void(TArray<Gs2::SerialKey::Model::FIssueJobPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FCampaignModelDomain::FSubscribeIssueJobsWithInitialCallTask::FSubscribeIssueJobsWithInitialCallTask(const FSubscribeIssueJobsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FSubscribeIssueJobsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectIssueJobsTask>>(Self, TFunction<void(TArray<Gs2::SerialKey::Model::FIssueJobPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeIssueJobs(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FCampaignModelDomain::FSubscribeIssueJobsWithInitialCallTask>> FCampaignModelDomain::SubscribeIssueJobsWithInitialCall(TFunction<void(TArray<Gs2::SerialKey::Model::FIssueJobPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeIssueJobsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::SerialKey::Domain::Model::FIssueJobDomain> FCampaignModelDomain::IssueJob(
        const FString IssueJobName
    )
    {
        return MakeShared<Gs2::SerialKey::Domain::Model::FIssueJobDomain>(
            Gs2,
            Service,
            NamespaceName,
            CampaignModelName,
            IssueJobName == TEXT("") ? TOptional<FString>() : TOptional<FString>(IssueJobName)
        );
    }

    FString FCampaignModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> CampaignModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (CampaignModelName.IsSet() ? *CampaignModelName : "null") + ":" +
            ChildType;
    }

    FString FCampaignModelDomain::CreateCacheKey(
        TOptional<FString> CampaignModelName
    )
    {
        return FString("") +
            (CampaignModelName.IsSet() ? *CampaignModelName : "null");
    }

    FCampaignModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FCampaignModelDomain> Self
    ): Self(Self)
    {

    }

    FCampaignModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FCampaignModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::SerialKey::Model::Cache::FCampaignModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::SerialKey::Model::Cache::FCampaignModelCache::CreateCacheKey(

            Self->CampaignModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SerialKey::Model::FCampaignModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SerialKey::Model::FCampaignModelPtr Value;
                const auto CacheHit = Gs2::SerialKey::Model::Cache::FCampaignModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->CampaignModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::SerialKey::Model::Cache::FCampaignModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->CampaignModelName,
                    TOptional<int32>(),
                    [Self](Gs2::SerialKey::Model::FCampaignModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::SerialKey::Request::FGetCampaignModelRequest>()
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

    TSharedPtr<FAsyncTask<FCampaignModelDomain::FModelTask>> FCampaignModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCampaignModelDomain::FModelTask>>(this->AsShared());
    }

    void FCampaignModelDomain::Invalidate()
    {
        Gs2::SerialKey::Model::Cache::FCampaignModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            CampaignModelName,
            TOptional<int32>()
        );
    }

    FCampaignModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FCampaignModelDomain>& Self,
        TFunction<void(Gs2::SerialKey::Model::FCampaignModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FCampaignModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCampaignModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FCampaignModelDomain::FSubscribeWithInitialCallTask>> FCampaignModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::SerialKey::Model::FCampaignModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FCampaignModelDomain::Subscribe(
        TFunction<void(Gs2::SerialKey::Model::FCampaignModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::SerialKey::Model::Cache::FCampaignModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SerialKey::Model::Cache::FCampaignModelCache::CreateCacheKey(

            CampaignModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SerialKey::Domain::FGs2SerialKeyDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryCampaignModelName = CampaignModelName;
        return Gs2->Cache->Subscribe(
            Gs2::SerialKey::Model::FCampaignModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SerialKey::Model::FCampaignModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryCampaignModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FCampaignModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryCampaignModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FCampaignModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::SerialKey::Model::Cache::FCampaignModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SerialKey::Model::Cache::FCampaignModelCache::CreateCacheKey(

            CampaignModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::SerialKey::Model::FCampaignModel::TypeName,
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
