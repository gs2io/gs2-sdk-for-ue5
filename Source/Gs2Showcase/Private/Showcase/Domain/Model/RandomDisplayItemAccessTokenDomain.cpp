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

#include "Showcase/Domain/Model/RandomDisplayItemAccessToken.h"
#include "Showcase/Domain/Model/RandomDisplayItem.h"
#include "Showcase/Domain/Model/Namespace.h"
#include "Showcase/Domain/Model/SalesItemMaster.h"
#include "Showcase/Domain/Model/SalesItemGroupMaster.h"
#include "Showcase/Domain/Model/ShowcaseMaster.h"
#include "Showcase/Domain/Model/CurrentShowcaseMaster.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/ShowcaseAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseMaster.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
#include "Showcase/Domain/Model/RandomShowcaseAccessToken.h"
#include "Showcase/Domain/Model/User.h"
#include "Showcase/Domain/Model/UserAccessToken.h"
#include "Showcase/Domain/Model/RandomShowcaseStatus.h"
#include "Showcase/Domain/Model/RandomShowcaseStatusAccessToken.h"
#include "Showcase/Domain/Model/RandomDisplayItem.h"
#include "Showcase/Domain/Model/RandomDisplayItemAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FRandomDisplayItemAccessTokenDomain::FRandomDisplayItemAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> ShowcaseName,
        const TOptional<FString> DisplayItemName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ShowcaseName(ShowcaseName),
        DisplayItemName(DisplayItemName),
        ParentKey(Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            ShowcaseName,
            "RandomDisplayItem"
        ))
    {
    }

    FRandomDisplayItemAccessTokenDomain::FRandomDisplayItemAccessTokenDomain(
        const FRandomDisplayItemAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self,
        const Request::FGetRandomDisplayItemRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemName(Self->DisplayItemName);
        const auto Future = Self->Client->GetRandomDisplayItem(
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
                    Self->UserId(),
                    Self->ShowcaseName,
                    "RandomDisplayItem"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
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

    TSharedPtr<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FGetTask>> FRandomDisplayItemAccessTokenDomain::Get(
        Request::FGetRandomDisplayItemRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask::FRandomShowcaseBuyTask(
        const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self,
        const Request::FRandomShowcaseBuyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask::FRandomShowcaseBuyTask(
        const FRandomShowcaseBuyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FRandomDisplayItemAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemName(Self->DisplayItemName);
        const auto Future = Self->Client->RandomShowcaseBuy(
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
                    Self->UserId(),
                    Self->ShowcaseName,
                    "RandomDisplayItem"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto StampSheet = MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                Self->Cache,
                Self->JobQueueDomain,
                Self->Session,
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId(),
                Self->StampSheetConfiguration
            );
            const auto Future3 = StampSheet->Run();
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return MakeShared<Core::Model::FTransactionError<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>(
                    Future3->GetTask().Error()->GetErrors(),
                    [&]() -> TSharedPtr<FAsyncTask<Gs2::Core::Domain::Model::FStampSheetDomain::FRunTask>>
                    {
                        return MakeShared<Gs2::Core::Domain::Model::FStampSheetDomain>(
                            Self->Cache,
                            Self->JobQueueDomain,
                            Self->Session,
                            *ResultModel->GetStampSheet(),
                            *ResultModel->GetStampSheetEncryptionKeyId(),
                            Self->StampSheetConfiguration
                        )->Run();
                    }
                );
            }
            Future3->EnsureCompletion();
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FRandomShowcaseBuyTask>> FRandomDisplayItemAccessTokenDomain::RandomShowcaseBuy(
        Request::FRandomShowcaseBuyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRandomShowcaseBuyTask>>(this->AsShared(), Request);
    }

    FString FRandomDisplayItemAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ShowcaseName,
        TOptional<FString> DisplayItemName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null") + ":" +
            (DisplayItemName.IsSet() ? *DisplayItemName : "null") + ":" +
            ChildType;
    }

    FString FRandomDisplayItemAccessTokenDomain::CreateCacheKey(
        TOptional<FString> DisplayItemName
    )
    {
        return FString() +
            (DisplayItemName.IsSet() ? *DisplayItemName : "null");
    }

    FRandomDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRandomDisplayItemAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRandomDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRandomDisplayItemAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Showcase::Model::FRandomDisplayItem>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                Self->DisplayItemName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Showcase::Request::FGetRandomDisplayItemRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                    Self->DisplayItemName
                );
                Self->Cache->Put(
                    Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "randomDisplayItem")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Showcase::Model::FRandomDisplayItem>(
                Self->ParentKey,
                Gs2::Showcase::Domain::Model::FRandomDisplayItemDomain::CreateCacheKey(
                    Self->DisplayItemName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FModelTask>> FRandomDisplayItemAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRandomDisplayItemAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
