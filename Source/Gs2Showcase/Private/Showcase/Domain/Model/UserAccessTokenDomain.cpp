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

#include "Showcase/Domain/Model/UserAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/DisplayItem.h"
#include "Showcase/Domain/Model/DisplayItemAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseMaster.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
#include "Showcase/Domain/Model/RandomShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseStatus.h"
#include "Showcase/Domain/Model/RandomShowcaseStatusAccessToken.h"
#include "Showcase/Domain/Model/RandomDisplayItem.h"
#include "Showcase/Domain/Model/RandomDisplayItemAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Showcase::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
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

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseAccessTokenDomain> FUserAccessTokenDomain::RandomShowcase(
        const FString ShowcaseName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomShowcaseAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ShowcaseName)
        );
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomShowcaseStatusAccessTokenDomain> FUserAccessTokenDomain::RandomShowcaseStatus(
        const FString ShowcaseName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomShowcaseStatusAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ShowcaseName)
        );
    }

    Gs2::Showcase::Domain::Iterator::FDescribeShowcasesIteratorPtr FUserAccessTokenDomain::Showcases(
    ) const
    {
        return MakeShared<Gs2::Showcase::Domain::Iterator::FDescribeShowcasesIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeShowcases(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Showcase::Model::FShowcase::TypeName,
            Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Showcase"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeShowcases(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Showcase::Model::FShowcase::TypeName,
            Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "Showcase"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FShowcaseAccessTokenDomain> FUserAccessTokenDomain::Showcase(
        const FString ShowcaseName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FShowcaseAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ShowcaseName)
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

