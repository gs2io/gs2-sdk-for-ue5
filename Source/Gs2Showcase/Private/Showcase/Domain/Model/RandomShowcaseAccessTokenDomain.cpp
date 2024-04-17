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

#include "Showcase/Domain/Model/RandomShowcaseAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
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

    FRandomShowcaseAccessTokenDomain::FRandomShowcaseAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> ShowcaseName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ShowcaseName(ShowcaseName),
        ParentKey(Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "RandomShowcase"
        ))
    {
    }

    FRandomShowcaseAccessTokenDomain::FRandomShowcaseAccessTokenDomain(
        const FRandomShowcaseAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ShowcaseName(From.ShowcaseName),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsIteratorPtr FRandomShowcaseAccessTokenDomain::RandomDisplayItems(
    ) const
    {
        return MakeShared<Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsIterator>(
            Gs2,
            Client,
            NamespaceName,
            ShowcaseName,
            AccessToken
        );
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseAccessTokenDomain::SubscribeRandomDisplayItems(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                ShowcaseName,
                "RandomDisplayItem"
            ),
            Callback
        );
    }

    void FRandomShowcaseAccessTokenDomain::UnsubscribeRandomDisplayItems(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                ShowcaseName,
                "RandomDisplayItem"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain> FRandomShowcaseAccessTokenDomain::RandomDisplayItem(
        const FString DisplayItemName
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            ShowcaseName,
            DisplayItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DisplayItemName)
        );
    }

    FString FRandomShowcaseAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ShowcaseName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null") + ":" +
            ChildType;
    }

    FString FRandomShowcaseAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ShowcaseName
    )
    {
        return FString("") +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null");
    }

    FRandomShowcaseAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRandomShowcaseAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRandomShowcaseAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomShowcase>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Showcase::Model::FRandomShowcase> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Showcase::Model::FRandomShowcase>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheKey(
                Self->ShowcaseName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRandomShowcaseAccessTokenDomain::FModelTask>> FRandomShowcaseAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FRandomShowcasePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheKey(
                ShowcaseName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FRandomShowcase>(obj));
            }
        );
    }

    void FRandomShowcaseAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FRandomShowcase::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheKey(
                ShowcaseName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

