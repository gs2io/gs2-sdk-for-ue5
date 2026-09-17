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

#include "StateMachine/Domain/Model/StateMachineMaster.h"
#include "StateMachine/Domain/Model/Namespace.h"
#include "StateMachine/Domain/Model/StateMachineMaster.h"
#include "StateMachine/Domain/Model/Status.h"
#include "StateMachine/Domain/Model/StatusAccessToken.h"
#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Domain/Model/UserAccessToken.h"
#include "StateMachine/Model/Cache/StateMachineMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::StateMachine::Domain::Model
{

    FStateMachineMasterDomain::FStateMachineMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const StateMachine::Domain::FGs2StateMachineDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int64> Version
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::StateMachine::FGs2StateMachineRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Version(Version),
        ParentKey(Gs2::StateMachine::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "StateMachineMaster"
        ))
    {
    }

    FStateMachineMasterDomain::FStateMachineMasterDomain(
        const FStateMachineMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Version(From.Version),
        ParentKey(From.ParentKey)
    {

    }

    FStateMachineMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FStateMachineMasterDomain>& Self,
        const Request::FGetStateMachineMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStateMachineMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStateMachineMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersion(Self->Version);
        const auto Future = Self->Client->GetStateMachineMaster(
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

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetVersion().Get(int64{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStateMachineMasterDomain::FGetTask>> FStateMachineMasterDomain::Get(
        Request::FGetStateMachineMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStateMachineMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStateMachineMasterDomain>& Self,
        const Request::FDeleteStateMachineMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStateMachineMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStateMachineMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStateMachineMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersion(Self->Version);
        const auto Future = Self->Client->DeleteStateMachineMaster(
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

              if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetVersion().Get(int64{}),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStateMachineMasterDomain::FDeleteTask>> FStateMachineMasterDomain::Delete(
        Request::FDeleteStateMachineMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FStateMachineMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<int64> Version,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Version.IsSet() ? FString::FromInt(*Version) : "null") + ":" +
            ChildType;
    }

    FString FStateMachineMasterDomain::CreateCacheKey(
        TOptional<int64> Version
    )
    {
        return FString("") +
            (Version.IsSet() ? FString::FromInt(*Version) : "null");
    }

    FStateMachineMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FStateMachineMasterDomain> Self
    ): Self(Self)
    {

    }

    FStateMachineMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStateMachineMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::CreateCacheKey(

            Self->Version
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::StateMachine::Model::FStateMachineMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::StateMachine::Model::FStateMachineMasterPtr Value;
                const auto CacheHit = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Version,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->Version,
                    TOptional<int32>(),
                    [Self](Gs2::StateMachine::Model::FStateMachineMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::StateMachine::Request::FGetStateMachineMasterRequest>()
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

    TSharedPtr<FAsyncTask<FStateMachineMasterDomain::FModelTask>> FStateMachineMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStateMachineMasterDomain::FModelTask>>(this->AsShared());
    }

    void FStateMachineMasterDomain::Invalidate()
    {
        Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            Version,
            TOptional<int32>()
        );
    }

    FStateMachineMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FStateMachineMasterDomain>& Self,
        TFunction<void(Gs2::StateMachine::Model::FStateMachineMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FStateMachineMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStateMachineMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FStateMachineMasterDomain::FSubscribeWithInitialCallTask>> FStateMachineMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::StateMachine::Model::FStateMachineMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FStateMachineMasterDomain::Subscribe(
        TFunction<void(Gs2::StateMachine::Model::FStateMachineMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::CreateCacheKey(

            Version
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<StateMachine::Domain::FGs2StateMachineDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<int64> QueryVersion = Version;
        return Gs2->Cache->Subscribe(
            Gs2::StateMachine::Model::FStateMachineMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::StateMachine::Model::FStateMachineMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryVersion]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FStateMachineMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryVersion
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FStateMachineMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::StateMachine::Model::Cache::FStateMachineMasterCache::CreateCacheKey(

            Version
        );
        Gs2->Cache->Unsubscribe(
            Gs2::StateMachine::Model::FStateMachineMaster::TypeName,
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
