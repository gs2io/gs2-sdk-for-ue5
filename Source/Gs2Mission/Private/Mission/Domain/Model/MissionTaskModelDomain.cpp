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

#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CounterAccessToken.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"
#include "Mission/Model/Cache/MissionTaskModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FMissionTaskModelDomain::FMissionTaskModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MissionGroupName,
        const TOptional<FString> MissionTaskName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        MissionGroupName(MissionGroupName),
        MissionTaskName(MissionTaskName),
        ParentKey(Gs2::Mission::Domain::Model::FMissionGroupModelDomain::CreateCacheParentKey(
            NamespaceName,
            MissionGroupName,
            "MissionTaskModel"
        ))
    {
    }

    FMissionTaskModelDomain::FMissionTaskModelDomain(
        const FMissionTaskModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        MissionGroupName(From.MissionGroupName),
        MissionTaskName(From.MissionTaskName),
        ParentKey(From.ParentKey)
    {

    }

    FMissionTaskModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionTaskModelDomain>& Self,
        const Request::FGetMissionTaskModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->GetMissionTaskModel(
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


        Gs2::Mission::Model::Cache::FMissionTaskModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            Request->GetMissionTaskName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionTaskModelDomain::FGetTask>> FMissionTaskModelDomain::Get(
        Request::FGetMissionTaskModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FMissionTaskModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MissionGroupName,
        TOptional<FString> MissionTaskName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null") + ":" +
            ChildType;
    }

    FString FMissionTaskModelDomain::CreateCacheKey(
        TOptional<FString> MissionTaskName
    )
    {
        return FString("") +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null");
    }

    FMissionTaskModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionTaskModelDomain> Self
    ): Self(Self)
    {

    }

    FMissionTaskModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->MissionGroupName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheKey(

            Self->MissionTaskName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Mission::Model::FMissionTaskModelPtr Value;
                const auto CacheHit = Gs2::Mission::Model::Cache::FMissionTaskModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MissionGroupName,
                    Self->MissionTaskName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Mission::Model::Cache::FMissionTaskModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MissionGroupName,
                    Self->MissionTaskName,
                    TOptional<int32>(),
                    [Self](Gs2::Mission::Model::FMissionTaskModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Mission::Request::FGetMissionTaskModelRequest>()
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

    TSharedPtr<FAsyncTask<FMissionTaskModelDomain::FModelTask>> FMissionTaskModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionTaskModelDomain::FModelTask>>(this->AsShared());
    }

    void FMissionTaskModelDomain::Invalidate()
    {
        Gs2::Mission::Model::Cache::FMissionTaskModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            MissionGroupName,
            MissionTaskName,
            TOptional<int32>()
        );
    }

    FMissionTaskModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMissionTaskModelDomain>& Self,
        TFunction<void(Gs2::Mission::Model::FMissionTaskModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FMissionTaskModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FMissionTaskModelDomain::FSubscribeWithInitialCallTask>> FMissionTaskModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Mission::Model::FMissionTaskModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMissionTaskModelDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FMissionTaskModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheParentKey(

            NamespaceName,
            MissionGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheKey(

            MissionTaskName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Mission::Domain::FGs2MissionDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryMissionGroupName = MissionGroupName;
        const TOptional<FString> QueryMissionTaskName = MissionTaskName;
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FMissionTaskModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryMissionGroupName, QueryMissionTaskName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMissionTaskModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryMissionGroupName,
                    QueryMissionTaskName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMissionTaskModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheParentKey(

            NamespaceName,
            MissionGroupName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheKey(

            MissionTaskName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
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
