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

    FRoomDomain::FRoomDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
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
        UserId(UserId),
        RoomName(RoomName),
        Password(Password),
        ParentKey(Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            TOptional<FString>("Singleton"),
            "Room"
        ))
    {
    }

    FRoomDomain::FRoomDomain(
        const FRoomDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FRoomDomain::FGetTask::FGetTask(
        const TSharedPtr<FRoomDomain> Self,
        const Request::FGetRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->GetRoom(
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FGetTask>> FRoomDomain::Get(
        Request::FGetRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FUpdateFromBackendTask::FUpdateFromBackendTask(
        const TSharedPtr<FRoomDomain> Self,
        const Request::FUpdateRoomFromBackendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FUpdateFromBackendTask::FUpdateFromBackendTask(
        const FUpdateFromBackendTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FUpdateFromBackendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password);
        const auto Future = Self->Client->UpdateRoomFromBackend(
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

    TSharedPtr<FAsyncTask<FRoomDomain::FUpdateFromBackendTask>> FRoomDomain::UpdateFromBackend(
        Request::FUpdateRoomFromBackendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromBackendTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FDeleteFromBackendTask::FDeleteFromBackendTask(
        const TSharedPtr<FRoomDomain> Self,
        const Request::FDeleteRoomFromBackendRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FDeleteFromBackendTask::FDeleteFromBackendTask(
        const FDeleteFromBackendTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FDeleteFromBackendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName);
        const auto Future = Self->Client->DeleteRoomFromBackend(
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

    TSharedPtr<FAsyncTask<FRoomDomain::FDeleteFromBackendTask>> FRoomDomain::DeleteFromBackend(
        Request::FDeleteRoomFromBackendRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteFromBackendTask>>(this->AsShared(), Request);
    }

    FRoomDomain::FPostTask::FPostTask(
        const TSharedPtr<FRoomDomain> Self,
        const Request::FPostByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FPostTask::FPostTask(
        const FPostTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FPostTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithRoomName(Self->RoomName)
            ->WithPassword(Self->Password);
        const auto Future = Self->Client->PostByUserId(
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
        auto Domain = MakeShared<Gs2::Chat::Domain::Model::FMessageDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetRoomName(),
            Request->GetPassword(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FPostTask>> FRoomDomain::Post(
        Request::FPostByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPostTask>>(this->AsShared(), Request);
    }

    Gs2::Chat::Domain::Iterator::FDescribeMessagesByUserIdIteratorPtr FRoomDomain::Messages(
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeMessagesByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            RoomName,
            Password,
            UserId
        );
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain> FRoomDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Model::FMessageDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            RoomName,
            Password,
            MessageName
        );
    }

    FString FRoomDomain::CreateCacheParentKey(
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

    FString FRoomDomain::CreateCacheKey(
        TOptional<FString> RoomName
    )
    {
        return FString() +
            (RoomName.IsSet() ? *RoomName : "null");
    }

    FRoomDomain::FModelTask::FModelTask(
        const TSharedPtr<FRoomDomain> Self
    ): Self(Self)
    {

    }

    FRoomDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Chat::Model::FRoom>(
            Self->ParentKey,
            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                Self->RoomName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Chat::Request::FGetRoomRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "room")
                    {
                        Self->Cache->Delete(
                            Gs2::Chat::Model::FRoom::TypeName,
                            Self->ParentKey,
                            Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                                Self->RoomName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Chat::Model::FRoom>(
                Self->ParentKey,
                Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheKey(
                    Self->RoomName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FModelTask>> FRoomDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRoomDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

