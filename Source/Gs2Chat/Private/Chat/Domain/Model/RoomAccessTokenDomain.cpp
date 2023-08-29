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

#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Room.h"
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

    FRoomAccessTokenDomain::FRoomAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        RoomName(RoomName),
        Password(Password),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Room"
        ))
    {
    }

    FRoomAccessTokenDomain::FRoomAccessTokenDomain(
        const FRoomAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FRoomAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRoomAccessTokenDomain> Self,
        const Request::FUpdateRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password);
        const auto Future = Self->Client->UpdateRoom(
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
                const auto ParentKey = Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    TOptional<FString>("Singleton"),
                    "Room"
                );
                const auto Key = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Chat::Model::FRoom::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FUpdateTask>> FRoomAccessTokenDomain::Update(
        Request::FUpdateRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRoomAccessTokenDomain> Self,
        const Request::FDeleteRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->DeleteRoom(
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
                const auto ParentKey = Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    TOptional<FString>("Singleton"),
                    "Room"
                );
                const auto Key = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Chat::Model::FRoom::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FDeleteTask>> FRoomAccessTokenDomain::Delete(
        Request::FDeleteRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FRoomAccessTokenDomain::FPostTask::FPostTask(
        const TSharedPtr<FRoomAccessTokenDomain> Self,
        const Request::FPostRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomAccessTokenDomain::FPostTask::FPostTask(
        const FPostTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FPostTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password);
        const auto Future = Self->Client->Post(
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
        auto Domain = MakeShared<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetRoomName(),
            Request->GetPassword(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FPostTask>> FRoomAccessTokenDomain::Post(
        Request::FPostRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPostTask>>(this->AsShared(), Request);
    }

    Gs2::Chat::Domain::Iterator::FDescribeMessagesIteratorPtr FRoomAccessTokenDomain::Messages(
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeMessagesIterator>(
            Cache,
            Client,
            NamespaceName,
            RoomName,
            Password,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain> FRoomAccessTokenDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            RoomName,
            Password,
            MessageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MessageName)
        );
    }

    FString FRoomAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> RoomName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (RoomName.IsSet() ? *RoomName : "null") + ":" +
            ChildType;
    }

    FString FRoomAccessTokenDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString() +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FRoomAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRoomAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRoomAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Chat::Model::FRoom> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Chat::Model::FRoom>(
            Self->ParentKey,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                Self->RoomName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomAccessTokenDomain::FModelTask>> FRoomAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRoomAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

