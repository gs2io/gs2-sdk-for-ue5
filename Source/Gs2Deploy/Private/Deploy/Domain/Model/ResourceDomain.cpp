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

#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"
#include "Deploy/Model/Cache/Resource.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FResourceDomain::FResourceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Deploy::Domain::FGs2DeployDomainPtr& Service,
        const TOptional<FString> StackName,
        const TOptional<FString> ResourceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        StackName(StackName),
        ResourceName(ResourceName),
        ParentKey(Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
            StackName,
            "Resource"
        ))
    {
    }

    FResourceDomain::FResourceDomain(
        const FResourceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StackName(From.StackName),
        ResourceName(From.ResourceName),
        ParentKey(From.ParentKey)
    {

    }

    FResourceDomain::FGetTask::FGetTask(
        const TSharedPtr<FResourceDomain>& Self,
        const Request::FGetResourceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FResourceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FResourceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStackName(Self->StackName)
            ->WithResourceName(Self->ResourceName);
        const auto Future = Self->Client->GetResource(
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


        Gs2::Deploy::Model::Cache::FResourceCache::Put(
            Self->Gs2->Cache,

            Request->GetStackName(),
            Request->GetResourceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FResourceDomain::FGetTask>> FResourceDomain::Get(
        Request::FGetResourceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FResourceDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        TOptional<FString> ResourceName,
        FString ChildType
    )
    {
        return FString("") +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            (ResourceName.IsSet() ? *ResourceName : "null") + ":" +
            ChildType;
    }

    FString FResourceDomain::CreateCacheKey(
        TOptional<FString> ResourceName
    )
    {
        return FString("") +
            (ResourceName.IsSet() ? *ResourceName : "null");
    }

    FResourceDomain::FModelTask::FModelTask(
        const TSharedPtr<FResourceDomain> Self
    ): Self(Self)
    {

    }

    FResourceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FResourceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
    )
    {
        const auto CacheParentKey = Gs2::Deploy::Model::Cache::FResourceCache::CreateCacheParentKey(

            Self->StackName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Deploy::Model::Cache::FResourceCache::CreateCacheKey(

            Self->ResourceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Deploy::Model::FResource::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Deploy::Model::FResourcePtr Value;
                const auto CacheHit = Gs2::Deploy::Model::Cache::FResourceCache::TryGet(
                    Self->Gs2->Cache,

                    Self->StackName,
                    Self->ResourceName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Deploy::Model::Cache::FResourceCache::Fetch(
                    Self->Gs2->Cache,

                    Self->StackName,
                    Self->ResourceName,
                    TOptional<int32>(),
                    [Self](Gs2::Deploy::Model::FResourcePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Deploy::Request::FGetResourceRequest>()
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

    TSharedPtr<FAsyncTask<FResourceDomain::FModelTask>> FResourceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FResourceDomain::FModelTask>>(this->AsShared());
    }

    void FResourceDomain::Invalidate()
    {
        Gs2::Deploy::Model::Cache::FResourceCache::Delete(
            Gs2->Cache,

            StackName,
            ResourceName,
            TOptional<int32>()
        );
    }

    FResourceDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FResourceDomain>& Self,
        TFunction<void(Gs2::Deploy::Model::FResourcePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FResourceDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FResourceDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FResourceDomain::FSubscribeWithInitialCallTask>> FResourceDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Deploy::Model::FResourcePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FResourceDomain::Subscribe(
        TFunction<void(Gs2::Deploy::Model::FResourcePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Deploy::Model::Cache::FResourceCache::CreateCacheParentKey(

            StackName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Deploy::Model::Cache::FResourceCache::CreateCacheKey(

            ResourceName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Deploy::Domain::FGs2DeployDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryStackName = StackName;
        const TOptional<FString> QueryResourceName = ResourceName;
        return Gs2->Cache->Subscribe(
            Gs2::Deploy::Model::FResource::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Deploy::Model::FResource>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryStackName, QueryResourceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FResourceDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryStackName,
                    QueryResourceName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FResourceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Deploy::Model::Cache::FResourceCache::CreateCacheParentKey(

            StackName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Deploy::Model::Cache::FResourceCache::CreateCacheKey(

            ResourceName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Deploy::Model::FResource::TypeName,
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
