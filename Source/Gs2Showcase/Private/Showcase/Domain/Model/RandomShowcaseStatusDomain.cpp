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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

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
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FRandomShowcaseStatusDomain::FRandomShowcaseStatusDomain(
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
            "RandomShowcaseStatus"
        ))
    {
    }

    FRandomShowcaseStatusDomain::FRandomShowcaseStatusDomain(
        const FRandomShowcaseStatusDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ShowcaseName(From.ShowcaseName),
        ParentKey(From.ParentKey)
    {

    }

    FRandomShowcaseStatusDomain::FIncrementPurchaseCountTask::FIncrementPurchaseCountTask(
        const TSharedPtr<FRandomShowcaseStatusDomain> Self,
        const Request::FIncrementPurchaseCountByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomShowcaseStatusDomain::FIncrementPurchaseCountTask::FIncrementPurchaseCountTask(
        const FIncrementPurchaseCountTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseStatusDomain::FIncrementPurchaseCountTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithShowcaseName(Self->ShowcaseName);
        const auto Future = Self->Client->IncrementPurchaseCountByUserId(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->ShowcaseName,
                    "RandomDisplayItem"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>(
            Self->Gs2,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetShowcaseName(),
            Request->GetDisplayItemName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRandomShowcaseStatusDomain::FIncrementPurchaseCountTask>> FRandomShowcaseStatusDomain::IncrementPurchaseCount(
        Request::FIncrementPurchaseCountByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIncrementPurchaseCountTask>>(this->AsShared(), Request);
    }

    FRandomShowcaseStatusDomain::FDecrementPurchaseCountTask::FDecrementPurchaseCountTask(
        const TSharedPtr<FRandomShowcaseStatusDomain> Self,
        const Request::FDecrementPurchaseCountByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomShowcaseStatusDomain::FDecrementPurchaseCountTask::FDecrementPurchaseCountTask(
        const FDecrementPurchaseCountTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseStatusDomain::FDecrementPurchaseCountTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithShowcaseName(Self->ShowcaseName);
        const auto Future = Self->Client->DecrementPurchaseCountByUserId(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->ShowcaseName,
                    "RandomDisplayItem"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>(
            Self->Gs2,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetShowcaseName(),
            Request->GetDisplayItemName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRandomShowcaseStatusDomain::FDecrementPurchaseCountTask>> FRandomShowcaseStatusDomain::DecrementPurchaseCount(
        Request::FDecrementPurchaseCountByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecrementPurchaseCountTask>>(this->AsShared(), Request);
    }

    FRandomShowcaseStatusDomain::FForceReDrawTask::FForceReDrawTask(
        const TSharedPtr<FRandomShowcaseStatusDomain> Self,
        const Request::FForceReDrawByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomShowcaseStatusDomain::FForceReDrawTask::FForceReDrawTask(
        const FForceReDrawTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomShowcaseStatusDomain::FForceReDrawTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithShowcaseName(Self->ShowcaseName);
        const auto Future = Self->Client->ForceReDrawByUserId(
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
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->ShowcaseName,
                        "RandomDisplayItem"
                    );
                    const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Self->Gs2->Cache->Put(
                        Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain>(
                    Self->Gs2,
                    Request->GetNamespaceName(),
                    Request->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetShowcaseName(),
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
            const auto ParentKey = Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                Self->ShowcaseName,
                "RandomDisplayItem"
            );
            const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRandomShowcaseStatusDomain::FForceReDrawTask>> FRandomShowcaseStatusDomain::ForceReDraw(
        Request::FForceReDrawByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FForceReDrawTask>>(this->AsShared(), Request);
    }

    FString FRandomShowcaseStatusDomain::CreateCacheParentKey(
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

    FString FRandomShowcaseStatusDomain::CreateCacheKey(
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

