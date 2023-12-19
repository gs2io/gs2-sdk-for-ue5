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

#include "StateMachine/Domain/Model/UserAccessToken.h"
#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Domain/Model/Namespace.h"
#include "StateMachine/Domain/Model/StateMachineMaster.h"
#include "StateMachine/Domain/Model/Status.h"
#include "StateMachine/Domain/Model/StatusAccessToken.h"
#include "StateMachine/Domain/Model/User.h"
#include "StateMachine/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::StateMachine::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const StateMachine::Domain::FGs2StateMachineDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::StateMachine::FGs2StateMachineRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::StateMachine::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::StateMachine::Domain::Iterator::FDescribeStatusesIteratorPtr FUserAccessTokenDomain::Statuses(
        const TOptional<FString> Status
    ) const
    {
        return MakeShared<Gs2::StateMachine::Domain::Iterator::FDescribeStatusesIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken,
            Status
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeStatuses(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::StateMachine::Model::FStatus::TypeName,
            Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Status"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeStatuses(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::StateMachine::Model::FStatus::TypeName,
            Gs2::StateMachine::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Status"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain> FUserAccessTokenDomain::Status(
        const FString StatusName
    )
    {
        return MakeShared<Gs2::StateMachine::Domain::Model::FStatusAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            StatusName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StatusName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
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

    FString FUserAccessTokenDomain::CreateCacheKey(
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

