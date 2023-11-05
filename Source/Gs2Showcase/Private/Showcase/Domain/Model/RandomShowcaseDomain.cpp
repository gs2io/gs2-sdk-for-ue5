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
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FRandomShowcaseDomain::FRandomShowcaseDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> ShowcaseName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ShowcaseName(ShowcaseName),
        ParentKey(Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "RandomShowcase"
        ))
    {
    }

    FRandomShowcaseDomain::FRandomShowcaseDomain(
        const FRandomShowcaseDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ShowcaseName(From.ShowcaseName),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsByUserIdIteratorPtr FRandomShowcaseDomain::RandomDisplayItems(
    ) const
    {
        return MakeShared<Gs2::Showcase::Domain::Iterator::FDescribeRandomDisplayItemsByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            ShowcaseName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseDomain::SubscribeRandomDisplayItems(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                ShowcaseName,
                "RandomDisplayItem"
            ),
            Callback
        );
    }

    void FRandomShowcaseDomain::UnsubscribeRandomDisplayItems(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
            Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                ShowcaseName,
                "RandomDisplayItem"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain> FRandomShowcaseDomain::RandomDisplayItem(
        const FString DisplayItemName
    ) const
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>(
            Gs2,
            NamespaceName,
            UserId,
            ShowcaseName,
            DisplayItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DisplayItemName)
        );
    }

    FString FRandomShowcaseDomain::CreateCacheParentKey(
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

    FString FRandomShowcaseDomain::CreateCacheKey(
        TOptional<FString> ShowcaseName
    )
    {
        return FString("") +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null");
    }

    FRandomShowcaseDomain::FModelTask::FModelTask(
        const TSharedPtr<FRandomShowcaseDomain> Self
    ): Self(Self)
    {

    }

    FRandomShowcaseDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FRandomShowcaseDomain::FModelTask>> FRandomShowcaseDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRandomShowcaseDomain::Subscribe(
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

    void FRandomShowcaseDomain::Unsubscribe(
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

