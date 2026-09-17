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

#include "Inbox/Domain/Model/Received.h"
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
#include "Inbox/Model/Cache/Received.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inbox::Domain::Model
{

    FReceivedDomain::FReceivedDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inbox::Domain::FGs2InboxDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inbox::FGs2InboxRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Received"
        ))
    {
    }

    FReceivedDomain::FReceivedDomain(
        const FReceivedDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FReceivedDomain::FGetTask::FGetTask(
        const TSharedPtr<FReceivedDomain>& Self,
        const Request::FGetReceivedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceivedDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FReceived>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetReceivedByUserId(
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

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Inbox::Model::Cache::FReceivedCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedDomain::FGetTask>> FReceivedDomain::Get(
        Request::FGetReceivedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FReceivedDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FReceivedDomain>& Self,
        const Request::FUpdateReceivedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceivedDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateReceivedByUserId(
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

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Inbox::Model::Cache::FReceivedCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedDomain::FUpdateTask>> FReceivedDomain::Update(
        Request::FUpdateReceivedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FReceivedDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FReceivedDomain>& Self,
        const Request::FDeleteReceivedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceivedDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Domain::Model::FReceivedDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteReceivedByUserId(
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

              if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Inbox::Model::Cache::FReceivedCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceivedDomain::FDeleteTask>> FReceivedDomain::Delete(
        Request::FDeleteReceivedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FReceivedDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FReceivedDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FReceivedDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceivedDomain> Self
    ): Self(Self)
    {

    }

    FReceivedDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FReceived>> Result
    )
    {
        const auto CacheParentKey = Gs2::Inbox::Model::Cache::FReceivedCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Inbox::Model::Cache::FReceivedCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Inbox::Model::FReceived::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Inbox::Model::FReceivedPtr Value;
                const auto CacheHit = Gs2::Inbox::Model::Cache::FReceivedCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Inbox::Model::Cache::FReceivedCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    TOptional<int32>(),
                    [Self](Gs2::Inbox::Model::FReceivedPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Inbox::Request::FGetReceivedByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FReceivedDomain::FModelTask>> FReceivedDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceivedDomain::FModelTask>>(this->AsShared());
    }

    void FReceivedDomain::Invalidate()
    {
        Gs2::Inbox::Model::Cache::FReceivedCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
    }

    FReceivedDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FReceivedDomain>& Self,
        TFunction<void(Gs2::Inbox::Model::FReceivedPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FReceivedDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceivedDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FReceivedDomain::FSubscribeWithInitialCallTask>> FReceivedDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Inbox::Model::FReceivedPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FReceivedDomain::Subscribe(
        TFunction<void(Gs2::Inbox::Model::FReceivedPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Inbox::Model::Cache::FReceivedCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inbox::Model::Cache::FReceivedCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Inbox::Domain::FGs2InboxDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        return Gs2->Cache->Subscribe(
            Gs2::Inbox::Model::FReceived::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inbox::Model::FReceived>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FReceivedDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FReceivedDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Inbox::Model::Cache::FReceivedCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Inbox::Model::Cache::FReceivedCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Inbox::Model::FReceived::TypeName,
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
