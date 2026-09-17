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

#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/Namespace.h"
#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/UserAccessToken.h"
#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/CampaignModelMaster.h"
#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"
#include "SerialKey/Model/Cache/IssueJob.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FIssueJobDomain::FIssueJobDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CampaignModelName,
        const TOptional<FString> IssueJobName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        CampaignModelName(CampaignModelName),
        IssueJobName(IssueJobName),
        ParentKey(Gs2::SerialKey::Domain::Model::FCampaignModelDomain::CreateCacheParentKey(
            NamespaceName,
            CampaignModelName,
            "IssueJob"
        ))
    {
    }

    FIssueJobDomain::FIssueJobDomain(
        const FIssueJobDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        CampaignModelName(From.CampaignModelName),
        IssueJobName(From.IssueJobName),
        ParentKey(From.ParentKey)
    {

    }

    FIssueJobDomain::FGetTask::FGetTask(
        const TSharedPtr<FIssueJobDomain>& Self,
        const Request::FGetIssueJobRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIssueJobDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIssueJobDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FIssueJob>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCampaignModelName(Self->CampaignModelName)
            ->WithIssueJobName(Self->IssueJobName);
        const auto Future = Self->Client->GetIssueJob(
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
            Request->GetIssueJobName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIssueJobDomain::FGetTask>> FIssueJobDomain::Get(
        Request::FGetIssueJobRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FIssueJobDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> CampaignModelName,
        TOptional<FString> IssueJobName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (CampaignModelName.IsSet() ? *CampaignModelName : "null") + ":" +
            (IssueJobName.IsSet() ? *IssueJobName : "null") + ":" +
            ChildType;
    }

    FString FIssueJobDomain::CreateCacheKey(
        TOptional<FString> IssueJobName
    )
    {
        return FString("") +
            (IssueJobName.IsSet() ? *IssueJobName : "null");
    }

    FIssueJobDomain::FModelTask::FModelTask(
        const TSharedPtr<FIssueJobDomain> Self
    ): Self(Self)
    {

    }

    FIssueJobDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIssueJobDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FIssueJob>> Result
    )
    {
        const auto CacheParentKey = Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->CampaignModelName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheKey(

            Self->IssueJobName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::SerialKey::Model::FIssueJob::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::SerialKey::Model::FIssueJobPtr Value;
                const auto CacheHit = Gs2::SerialKey::Model::Cache::FIssueJobCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->CampaignModelName,
                    Self->IssueJobName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::SerialKey::Model::Cache::FIssueJobCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->CampaignModelName,
                    Self->IssueJobName,
                    TOptional<int32>(),
                    [Self](Gs2::SerialKey::Model::FIssueJobPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::SerialKey::Request::FGetIssueJobRequest>()
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

    TSharedPtr<FAsyncTask<FIssueJobDomain::FModelTask>> FIssueJobDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FIssueJobDomain::FModelTask>>(this->AsShared());
    }

    void FIssueJobDomain::Invalidate()
    {
        Gs2::SerialKey::Model::Cache::FIssueJobCache::Delete(
            Gs2->Cache,

            NamespaceName,
            CampaignModelName,
            IssueJobName,
            TOptional<int32>()
        );
    }

    FIssueJobDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FIssueJobDomain>& Self,
        TFunction<void(Gs2::SerialKey::Model::FIssueJobPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FIssueJobDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIssueJobDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FIssueJobDomain::FSubscribeWithInitialCallTask>> FIssueJobDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::SerialKey::Model::FIssueJobPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FIssueJobDomain::Subscribe(
        TFunction<void(Gs2::SerialKey::Model::FIssueJobPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheParentKey(

            NamespaceName,
            CampaignModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheKey(

            IssueJobName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<SerialKey::Domain::FGs2SerialKeyDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryCampaignModelName = CampaignModelName;
        const TOptional<FString> QueryIssueJobName = IssueJobName;
        return Gs2->Cache->Subscribe(
            Gs2::SerialKey::Model::FIssueJob::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::SerialKey::Model::FIssueJob>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryCampaignModelName, QueryIssueJobName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FIssueJobDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryCampaignModelName,
                    QueryIssueJobName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FIssueJobDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheParentKey(

            NamespaceName,
            CampaignModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::SerialKey::Model::Cache::FIssueJobCache::CreateCacheKey(

            IssueJobName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::SerialKey::Model::FIssueJob::TypeName,
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
