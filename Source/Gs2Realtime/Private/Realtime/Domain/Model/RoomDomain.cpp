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

#include "Realtime/Domain/Model/Room.h"
#include "Realtime/Domain/Model/Namespace.h"
#include "Realtime/Domain/Model/Room.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Realtime::Domain::Model
{

    FRoomDomain::FRoomDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RoomName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Realtime::FGs2RealtimeRestClient>(Session)),
        NamespaceName(NamespaceName),
        RoomName(RoomName),
        ParentKey(Gs2::Realtime::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
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
        TSharedPtr<TSharedPtr<Gs2::Realtime::Model::FRoom>> Result
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
                const auto ParentKey = Gs2::Realtime::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Room"
                );
                const auto Key = Gs2::Realtime::Domain::Model::FRoomDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Realtime::Model::FRoom>(
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

    FRoomDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRoomDomain> Self,
        const Request::FDeleteRoomRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRoomDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRoomDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Realtime::Domain::Model::FRoomDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
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
                const auto ParentKey = Gs2::Realtime::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Room"
                );
                const auto Key = Gs2::Realtime::Domain::Model::FRoomDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete<Gs2::Realtime::Model::FRoom>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRoomDomain::FDeleteTask>> FRoomDomain::Delete(
        Request::FDeleteRoomRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRoomDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RoomName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
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
        TSharedPtr<TSharedPtr<Gs2::Realtime::Model::FRoom>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Realtime::Model::FRoom>(
            Self->ParentKey,
            Gs2::Realtime::Domain::Model::FRoomDomain::CreateCacheKey(
                Self->RoomName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Realtime::Request::FGetRoomRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "room")
                    {
                        Self->Cache->Delete<Gs2::Realtime::Model::FRoom>(
                            Self->ParentKey,
                            Gs2::Realtime::Domain::Model::FRoomDomain::CreateCacheKey(
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
            Value = Self->Cache->Get<Gs2::Realtime::Model::FRoom>(
                Self->ParentKey,
                Gs2::Realtime::Domain::Model::FRoomDomain::CreateCacheKey(
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

