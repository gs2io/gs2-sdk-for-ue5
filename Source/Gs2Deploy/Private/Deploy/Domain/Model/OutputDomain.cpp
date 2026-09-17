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

#include "Deploy/Domain/Model/Output.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"
#include "Deploy/Model/Cache/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FOutputDomain::FOutputDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Deploy::Domain::FGs2DeployDomainPtr& Service,
        const TOptional<FString> StackName,
        const TOptional<FString> OutputName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        StackName(StackName),
        OutputName(OutputName),
        ParentKey(Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
            StackName,
            "Output"
        ))
    {
    }

    FOutputDomain::FOutputDomain(
        const FOutputDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StackName(From.StackName),
        OutputName(From.OutputName),
        ParentKey(From.ParentKey)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const TSharedPtr<FOutputDomain>& Self,
        const Request::FGetOutputRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FOutput>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStackName(Self->StackName)
            ->WithOutputName(Self->OutputName);
        const auto Future = Self->Client->GetOutput(
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


        Gs2::Deploy::Model::Cache::FOutputCache::Put(
            Self->Gs2->Cache,

            Request->GetStackName(),
            Request->GetOutputName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FOutputDomain::FGetTask>> FOutputDomain::Get(
        Request::FGetOutputRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FOutputDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        TOptional<FString> OutputName,
        FString ChildType
    )
    {
        return FString("") +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            (OutputName.IsSet() ? *OutputName : "null") + ":" +
            ChildType;
    }

    FString FOutputDomain::CreateCacheKey(
        TOptional<FString> OutputName
    )
    {
        return FString("") +
            (OutputName.IsSet() ? *OutputName : "null");
    }

    FOutputDomain::FModelTask::FModelTask(
        const TSharedPtr<FOutputDomain> Self
    ): Self(Self)
    {

    }

    FOutputDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FOutput>> Result
    )
    {
        const auto CacheParentKey = Gs2::Deploy::Model::Cache::FOutputCache::CreateCacheParentKey(

            Self->StackName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Deploy::Model::Cache::FOutputCache::CreateCacheKey(

            Self->OutputName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Deploy::Model::FOutput::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Deploy::Model::FOutputPtr Value;
                const auto CacheHit = Gs2::Deploy::Model::Cache::FOutputCache::TryGet(
                    Self->Gs2->Cache,

                    Self->StackName,
                    Self->OutputName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Deploy::Model::Cache::FOutputCache::Fetch(
                    Self->Gs2->Cache,

                    Self->StackName,
                    Self->OutputName,
                    TOptional<int32>(),
                    [Self](Gs2::Deploy::Model::FOutputPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Deploy::Request::FGetOutputRequest>()
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

    TSharedPtr<FAsyncTask<FOutputDomain::FModelTask>> FOutputDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FOutputDomain::FModelTask>>(this->AsShared());
    }

    void FOutputDomain::Invalidate()
    {
        Gs2::Deploy::Model::Cache::FOutputCache::Delete(
            Gs2->Cache,

            StackName,
            OutputName,
            TOptional<int32>()
        );
    }

    FOutputDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FOutputDomain>& Self,
        TFunction<void(Gs2::Deploy::Model::FOutputPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FOutputDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FOutputDomain::FSubscribeWithInitialCallTask>> FOutputDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Deploy::Model::FOutputPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FOutputDomain::Subscribe(
        TFunction<void(Gs2::Deploy::Model::FOutputPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Deploy::Model::Cache::FOutputCache::CreateCacheParentKey(

            StackName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Deploy::Model::Cache::FOutputCache::CreateCacheKey(

            OutputName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Deploy::Domain::FGs2DeployDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryStackName = StackName;
        const TOptional<FString> QueryOutputName = OutputName;
        return Gs2->Cache->Subscribe(
            Gs2::Deploy::Model::FOutput::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Deploy::Model::FOutput>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryStackName, QueryOutputName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FOutputDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryStackName,
                    QueryOutputName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FOutputDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Deploy::Model::Cache::FOutputCache::CreateCacheParentKey(

            StackName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Deploy::Model::Cache::FOutputCache::CreateCacheKey(

            OutputName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Deploy::Model::FOutput::TypeName,
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
