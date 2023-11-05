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

#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Domain/Model/Namespace.h"
#include "StateMachine/Domain/Model/StateMachineMaster.h"
#include "StateMachine/Domain/Model/Status.h"
#include "StateMachine/Domain/Model/StatusAccessToken.h"
#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::StateMachine::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::StateMachine::FGs2StateMachineRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::StateMachine::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FStartStateMachineTask::FStartStateMachineTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FStartStateMachineByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FStartStateMachineTask::FStartStateMachineTask(
        const FStartStateMachineTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FStartStateMachineTask::Action(
        TSharedPtr<TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->StartStateMachineByUserId(
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
                const auto ParentKey = Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Status"
                );
                const auto Key = Gs2::StateMachine::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::StateMachine::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::StateMachine::Domain::Model::FStatusDomain>(
            Self->Gs2,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FStartStateMachineTask>> FUserDomain::StartStateMachine(
        Request::FStartStateMachineByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FStartStateMachineTask>>(this->AsShared(), Request);
    }

    Gs2::StateMachine::Domain::Iterator::FDescribeStatusesByUserIdIteratorPtr FUserDomain::Statuses(
        const TOptional<FString> Status
    ) const
    {
        return MakeShared<Gs2::StateMachine::Domain::Iterator::FDescribeStatusesByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId,
            Status
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeStatuses(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::StateMachine::Model::FStatus::TypeName,
            Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Status"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::StateMachine::Model::FStatus::TypeName,
            Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Status"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusDomain> FUserDomain::Status(
        const FString StatusName
    ) const
    {
        return MakeShared<Gs2::StateMachine::Domain::Model::FStatusDomain>(
            Gs2,
            NamespaceName,
            UserId,
            StatusName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StatusName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

