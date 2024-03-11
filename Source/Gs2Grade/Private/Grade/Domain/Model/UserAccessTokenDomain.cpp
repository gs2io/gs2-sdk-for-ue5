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

#include "Grade/Domain/Model/UserAccessToken.h"
#include "Grade/Domain/Model/User.h"
#include "Grade/Domain/Model/Namespace.h"
#include "Grade/Domain/Model/GradeModelMaster.h"
#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/User.h"
#include "Grade/Domain/Model/UserAccessToken.h"
#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/StatusAccessToken.h"
#include "Grade/Domain/Model/CurrentGradeMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Grade::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Grade::Domain::FGs2GradeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Grade::FGs2GradeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Grade::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    Gs2::Grade::Domain::Iterator::FDescribeStatusesIteratorPtr FUserAccessTokenDomain::Statuses(
        const TOptional<FString> GradeName
    ) const
    {
        return MakeShared<Gs2::Grade::Domain::Iterator::FDescribeStatusesIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken,
            GradeName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeStatuses(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Grade::Model::FStatus::TypeName,
            Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
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
            Gs2::Grade::Model::FStatus::TypeName,
            Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Status"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain> FUserAccessTokenDomain::Status(
        const FString GradeName,
        const FString PropertyId
    )
    {
        return MakeShared<Gs2::Grade::Domain::Model::FStatusAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            GradeName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GradeName),
            PropertyId == TEXT("") ? TOptional<FString>() : TOptional<FString>(PropertyId)
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

