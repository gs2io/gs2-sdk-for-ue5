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

#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/CategoryModel.h"
#include "Chat/Domain/Model/CategoryModelMaster.h"
#include "Chat/Domain/Model/CurrentModelMaster.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"
#include "Chat/Model/Cache/Message.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FMessageDomain::FMessageDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password,
        const TOptional<FString> MessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        RoomName(RoomName),
        Password(Password),
        MessageName(MessageName),
        ParentKey(Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            RoomName,
            "Message"
        ))
    {
    }

    FMessageDomain::FMessageDomain(
        const FMessageDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        RoomName(From.RoomName),
        Password(From.Password),
        MessageName(From.MessageName),
        ParentKey(From.ParentKey)
    {

    }

    FMessageDomain::FGetTask::FGetTask(
        const TSharedPtr<FMessageDomain>& Self,
        const Request::FGetMessageByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithMessageName(Self->MessageName)
            ->WithPassword(Self->Password)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetMessageByUserId(
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
        Gs2::Chat::Model::Cache::FMessageCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetRoomName(),
            Request->GetMessageName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FGetTask>> FMessageDomain::Get(
        Request::FGetMessageByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMessageDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMessageDomain>& Self,
        const Request::FDeleteMessageRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMessageDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName)
            ->WithUserId(Self->UserId)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->DeleteMessage(
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
              Gs2::Chat::Model::Cache::FMessageCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            ResultModel->GetItem()->GetRoomName(),
            Request->GetMessageName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FDeleteTask>> FMessageDomain::Delete(
        Request::FDeleteMessageRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMessageDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RoomName,
        TOptional<FString> MessageName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RoomName.IsSet() ? *RoomName : "null") + ":" +
            (MessageName.IsSet() ? *MessageName : "null") + ":" +
            ChildType;
    }

    FString FMessageDomain::CreateCacheKey(
        TOptional<FString> MessageName
    )
    {
        return FString("") +
            (MessageName.IsSet() ? *MessageName : "null");
    }

    FMessageDomain::FModelTask::FModelTask(
        const TSharedPtr<FMessageDomain> Self
    ): Self(Self)
    {

    }

    FMessageDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result
    )
    {
        const auto CacheParentKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            Self->RoomName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheKey(

            Self->MessageName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Chat::Model::FMessage::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result, CacheParentKey, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Chat::Model::FMessage> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Chat::Model::FMessage>(
                    CacheParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Chat::Request::FGetMessageByUserIdRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }

                        Self->Gs2->Cache->Put(
                            Gs2::Chat::Model::FMessage::TypeName,
                            CacheParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "message")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }

                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::Chat::Model::FMessage::TypeName,
                        CacheParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Chat::Model::FMessage::TypeName,
                            CacheParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }
                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FModelTask>> FMessageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMessageDomain::FModelTask>>(this->AsShared());
    }

    void FMessageDomain::Invalidate()
    {
        Gs2::Chat::Model::Cache::FMessageCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            RoomName,
            MessageName,
            TOptional<int32>()
        );
    }

    FMessageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMessageDomain> Self,
        const TFunction<void(Gs2::Chat::Model::FMessagePtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FMessageDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMessageDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FMessageDomain::FSubscribeWithInitialCallTask>> FMessageDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Chat::Model::FMessagePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMessageDomain::Subscribe(
        TFunction<void(Gs2::Chat::Model::FMessagePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            RoomName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheKey(

            MessageName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Chat::Domain::FGs2ChatDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryRoomName = RoomName;
        const TOptional<FString> QueryPassword = Password;
        const TOptional<FString> QueryMessageName = MessageName;
        return Gs2->Cache->Subscribe(
            Gs2::Chat::Model::FMessage::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Chat::Model::FMessage>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryRoomName, QueryPassword, QueryMessageName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMessageDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryRoomName,
                    QueryPassword,
                    QueryMessageName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMessageDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            RoomName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheKey(

            MessageName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Chat::Model::FMessage::TypeName,
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
