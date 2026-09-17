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

#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/Namespace.h"
#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/CurrentExperienceMaster.h"
#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/StatusAccessToken.h"
#include "Experience/Model/Cache/ThresholdMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Experience::Domain::Model
{

    FThresholdMasterDomain::FThresholdMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ThresholdName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ThresholdName(ThresholdName),
        ParentKey(Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "ThresholdMaster"
        ))
    {
    }

    FThresholdMasterDomain::FThresholdMasterDomain(
        const FThresholdMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ThresholdName(From.ThresholdName),
        ParentKey(From.ParentKey)
    {

    }

    FThresholdMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FThresholdMasterDomain>& Self,
        const Request::FGetThresholdMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FThresholdMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FThresholdMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithThresholdName(Self->ThresholdName);
        const auto Future = Self->Client->GetThresholdMaster(
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


        Gs2::Experience::Model::Cache::FThresholdMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetThresholdName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FGetTask>> FThresholdMasterDomain::Get(
        Request::FGetThresholdMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FThresholdMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FThresholdMasterDomain>& Self,
        const Request::FUpdateThresholdMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FThresholdMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FThresholdMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithThresholdName(Self->ThresholdName);
        const auto Future = Self->Client->UpdateThresholdMaster(
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


        Gs2::Experience::Model::Cache::FThresholdMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetThresholdName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FUpdateTask>> FThresholdMasterDomain::Update(
        Request::FUpdateThresholdMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FThresholdMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FThresholdMasterDomain>& Self,
        const Request::FDeleteThresholdMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FThresholdMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FThresholdMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithThresholdName(Self->ThresholdName);
        const auto Future = Self->Client->DeleteThresholdMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();


              Gs2::Experience::Model::Cache::FThresholdMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetThresholdName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FDeleteTask>> FThresholdMasterDomain::Delete(
        Request::FDeleteThresholdMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FThresholdMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ThresholdName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ThresholdName.IsSet() ? *ThresholdName : "null") + ":" +
            ChildType;
    }

    FString FThresholdMasterDomain::CreateCacheKey(
        TOptional<FString> ThresholdName
    )
    {
        return FString("") +
            (ThresholdName.IsSet() ? *ThresholdName : "null");
    }

    FThresholdMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FThresholdMasterDomain> Self
    ): Self(Self)
    {

    }

    FThresholdMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FThresholdMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Experience::Model::Cache::FThresholdMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Experience::Model::Cache::FThresholdMasterCache::CreateCacheKey(

            Self->ThresholdName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Experience::Model::FThresholdMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Experience::Model::FThresholdMasterPtr Value;
                const auto CacheHit = Gs2::Experience::Model::Cache::FThresholdMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ThresholdName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Experience::Model::Cache::FThresholdMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ThresholdName,
                    TOptional<int32>(),
                    [Self](Gs2::Experience::Model::FThresholdMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Experience::Request::FGetThresholdMasterRequest>()
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

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FModelTask>> FThresholdMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FThresholdMasterDomain::FModelTask>>(this->AsShared());
    }

    void FThresholdMasterDomain::Invalidate()
    {
        Gs2::Experience::Model::Cache::FThresholdMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            ThresholdName,
            TOptional<int32>()
        );
    }

    FThresholdMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FThresholdMasterDomain>& Self,
        TFunction<void(Gs2::Experience::Model::FThresholdMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FThresholdMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FSubscribeWithInitialCallTask>> FThresholdMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Experience::Model::FThresholdMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FThresholdMasterDomain::Subscribe(
        TFunction<void(Gs2::Experience::Model::FThresholdMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Experience::Model::Cache::FThresholdMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Experience::Model::Cache::FThresholdMasterCache::CreateCacheKey(

            ThresholdName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Experience::Domain::FGs2ExperienceDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryThresholdName = ThresholdName;
        return Gs2->Cache->Subscribe(
            Gs2::Experience::Model::FThresholdMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Experience::Model::FThresholdMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryThresholdName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FThresholdMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryThresholdName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FThresholdMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Experience::Model::Cache::FThresholdMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Experience::Model::Cache::FThresholdMasterCache::CreateCacheKey(

            ThresholdName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Experience::Model::FThresholdMaster::TypeName,
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
