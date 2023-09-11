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
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FMessageDomain::FMessageDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password,
        const TOptional<FString> MessageName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Session)),
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
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
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
        const TSharedPtr<FMessageDomain> Self,
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
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->GetMessageByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    TOptional<FString>("Singleton"),
                    Self->RoomName,
                    "Message"
                );
                const auto Key = Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Chat::Model::FMessage::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
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
        const TSharedPtr<FMessageDomain> Self,
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
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName)
            ->WithMessageName(Self->MessageName);
        const auto Future = Self->Client->DeleteMessage(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    TOptional<FString>("Singleton"),
                    Self->RoomName,
                    "Message"
                );
                const auto Key = Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Chat::Model::FMessage::TypeName, ParentKey, Key);
            }
        }
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Chat::Model::FMessage> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Chat::Model::FMessage>(
            Self->ParentKey,
            Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                Self->MessageName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Chat::Request::FGetMessageByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                    Self->MessageName
                );
                Self->Cache->Put(
                    Gs2::Chat::Model::FMessage::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "message")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Chat::Model::FMessage>(
                Self->ParentKey,
                Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                    Self->MessageName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMessageDomain::FModelTask>> FMessageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMessageDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

