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

#include "Showcase/Domain/Model/SalesItemGroup.h"
#include "Showcase/Domain/Model/DisplayItem.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FSalesItemGroupDomain::FSalesItemGroupDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> DisplayItemId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Session)),
        NamespaceName(NamespaceName),
        DisplayItemId(DisplayItemId),
        ParentKey(Gs2::Showcase::Domain::Model::FDisplayItemDomain::CreateCacheParentKey(
            NamespaceName,
            DisplayItemId,
            "SalesItemGroup"
        ))
    {
    }

    FSalesItemGroupDomain::FSalesItemGroupDomain(
        const FSalesItemGroupDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FString FSalesItemGroupDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> DisplayItemId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (DisplayItemId.IsSet() ? *DisplayItemId : "null") + ":" +
            ChildType;
    }

    FString FSalesItemGroupDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FSalesItemGroupDomain::FModelTask::FModelTask(
        const TSharedPtr<FSalesItemGroupDomain> Self
    ): Self(Self)
    {

    }

    FSalesItemGroupDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSalesItemGroupDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FSalesItemGroup>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Showcase::Model::FSalesItemGroup>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FSalesItemGroupDomain::CreateCacheKey(
            )
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSalesItemGroupDomain::FModelTask>> FSalesItemGroupDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSalesItemGroupDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

