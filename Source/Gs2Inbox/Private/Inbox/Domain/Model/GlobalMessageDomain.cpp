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

#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Namespace.h"
#include "Inbox/Domain/Model/User.h"
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/MessageAccessToken.h"
#include "Inbox/Domain/Model/CurrentMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessageMaster.h"
#include "Inbox/Domain/Model/GlobalMessage.h"
#include "Inbox/Domain/Model/Received.h"
#include "Inbox/Domain/Model/ReceivedAccessToken.h"
#include "Inbox/Model/Cache/GlobalMessage.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FGlobalMessageDomain::FGlobalMessageDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GlobalMessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GlobalMessageName(GlobalMessageName),
        ParentKey(Gs2::Inbox::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "GlobalMessage"
        ))
    {
    }

    FGlobalMessageDomain::FGlobalMessageDomain(
        const FGlobalMessageDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GlobalMessageName(From.GlobalMessageName),
        ParentKey(From.ParentKey)
    {

    }

    FGlobalMessageDomain::FGetTask::FGetTask(
        const TSharedPtr<FGlobalMessageDomain>& Self,
        const Request::FGetGlobalMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGlobalMessageDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessage>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGlobalMessageName(Self->GlobalMessageName);
        const auto Future = Self->Client->GetGlobalMessage(
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


        Gs2::Inbox::Model::Cache::FGlobalMessageCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetGlobalMessageName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGlobalMessageDomain::FGetTask>> FGlobalMessageDomain::Get(
        Request::FGetGlobalMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FGlobalMessageDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GlobalMessageName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GlobalMessageName.IsSet() ? *GlobalMessageName : "null") + ":" +
            ChildType;
    }

    FString FGlobalMessageDomain::CreateCacheKey(
        TOptional<FString> GlobalMessageName
    )
    {
        return FString("") +
            (GlobalMessageName.IsSet() ? *GlobalMessageName : "null");
    }

    FGlobalMessageDomain::FModelTask::FModelTask(
        const TSharedPtr<FGlobalMessageDomain> Self
    ): Self(Self)
    {

    }

    FGlobalMessageDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FGlobalMessage>> Result
    )
    {
        const auto CacheParentKey = Gs2::Inbox::Model::Cache::FGlobalMessageCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Inbox::Model::Cache::FGlobalMessageCache::CreateCacheKey(

            Self->GlobalMessageName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Inbox::Model::FGlobalMessage::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Inbox::Model::FGlobalMessagePtr Value;
                const auto CacheHit = Gs2::Inbox::Model::Cache::FGlobalMessageCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GlobalMessageName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Inbox::Model::Cache::FGlobalMessageCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->GlobalMessageName,
                    TOptional<int32>(),
                    [Self](Gs2::Inbox::Model::FGlobalMessagePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Inbox::Request::FGetGlobalMessageRequest>()
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

    TSharedPtr<FAsyncTask<FGlobalMessageDomain::FModelTask>> FGlobalMessageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGlobalMessageDomain::FModelTask>>(this->AsShared());
    }

    void FGlobalMessageDomain::Invalidate()
    {
        Gs2::Inbox::Model::Cache::FGlobalMessageCache::Delete(
            Gs2->Cache,

            NamespaceName,
            GlobalMessageName,
            TOptional<int32>()
        );
    }

    FGlobalMessageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FGlobalMessageDomain>& Self,
        TFunction<void(Gs2::Inbox::Model::FGlobalMessagePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FGlobalMessageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGlobalMessageDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FGlobalMessageDomain::FSubscribeWithInitialCallTask>> FGlobalMessageDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Inbox::Model::FGlobalMessagePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FGlobalMessageDomain::Subscribe(
        TFunction<void(Gs2::Inbox::Model::FGlobalMessagePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Inbox::Model::Cache::FGlobalMessageCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inbox::Model::Cache::FGlobalMessageCache::CreateCacheKey(

            GlobalMessageName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Inbox::Domain::FGs2InboxDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGlobalMessageName = GlobalMessageName;
        return Gs2->Cache->Subscribe(
            Gs2::Inbox::Model::FGlobalMessage::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inbox::Model::FGlobalMessage>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGlobalMessageName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FGlobalMessageDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryGlobalMessageName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FGlobalMessageDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Inbox::Model::Cache::FGlobalMessageCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inbox::Model::Cache::FGlobalMessageCache::CreateCacheKey(

            GlobalMessageName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Inbox::Model::FGlobalMessage::TypeName,
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
