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

#include "Showcase/Domain/Model/RandomShowcaseStatusAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseStatus.h"
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

    FRandomShowcaseStatusAccessTokenDomain::FRandomShowcaseStatusAccessTokenDomain(
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
            "RandomShowcaseStatus"
        ))
    {
    }

    FRandomShowcaseStatusAccessTokenDomain::FRandomShowcaseStatusAccessTokenDomain(
        const FRandomShowcaseStatusAccessTokenDomain& From
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

    FRandomShowcaseStatusAccessTokenDomain::FIncrementPurchaseCountTask::FIncrementPurchaseCountTask(
        const TSharedPtr<FRandomShowcaseStatusAccessTokenDomain>& Self,
        const Request::FIncrementPurchaseCountRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomShowcaseStatusAccessTokenDomain::FIncrementPurchaseCountTask::FIncrementPurchaseCountTask(
        const FIncrementPurchaseCountTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseStatusAccessTokenDomain::FIncrementPurchaseCountTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->IncrementPurchaseCount(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetShowcaseName(),
            Request->GetDisplayItemName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRandomShowcaseStatusAccessTokenDomain::FIncrementPurchaseCountTask>> FRandomShowcaseStatusAccessTokenDomain::IncrementPurchaseCount(
        Request::FIncrementPurchaseCountRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIncrementPurchaseCountTask>>(this->AsShared(), Request);
    }

    FString FRandomShowcaseStatusAccessTokenDomain::CreateCacheParentKey(
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

    FString FRandomShowcaseStatusAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ShowcaseName
    )
    {
        return FString("") +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

