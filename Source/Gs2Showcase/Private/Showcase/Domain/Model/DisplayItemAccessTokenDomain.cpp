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

#include "Showcase/Domain/Model/DisplayItemAccessToken.h"
#include "Showcase/Domain/Model/DisplayItem.h"
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
#include "Showcase/Domain/SpeculativeExecutor/Transaction/BuyByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"

namespace Gs2::Showcase::Domain::Model
{

    FDisplayItemAccessTokenDomain::FDisplayItemAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> ShowcaseName,
        const TOptional<FString> DisplayItemId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ShowcaseName(ShowcaseName),
        DisplayItemId(DisplayItemId),
        ParentKey(Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            ShowcaseName,
            "DisplayItem"
        ))
    {
    }

    FDisplayItemAccessTokenDomain::FDisplayItemAccessTokenDomain(
        const FDisplayItemAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ShowcaseName(From.ShowcaseName),
        DisplayItemId(From.DisplayItemId),
        ParentKey(From.ParentKey)
    {

    }

    FDisplayItemAccessTokenDomain::FBuyTask::FBuyTask(
        const TSharedPtr<FDisplayItemAccessTokenDomain>& Self,
        const Request::FBuyRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FDisplayItemAccessTokenDomain::FBuyTask::FBuyTask(
        const FBuyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDisplayItemAccessTokenDomain::FBuyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Domain::Model::FDisplayItemAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithDisplayItemId(Self->DisplayItemId);

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FBuyByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FBuyByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->Buy(
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
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

        TSharedPtr<FAsyncTask<FDisplayItemAccessTokenDomain::FBuyTask>> FDisplayItemAccessTokenDomain::Buy(
            Request::FBuyRequestPtr Request,
            bool SpeculativeExecute
        ) {
            return Gs2::Core::Util::New<FAsyncTask<FBuyTask>>(this->AsShared(), Request, SpeculativeExecute);
        }

    FString FDisplayItemAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ShowcaseName,
        TOptional<FString> DisplayItemId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null") + ":" +
            (DisplayItemId.IsSet() ? *DisplayItemId : "null") + ":" +
            ChildType;
    }

    FString FDisplayItemAccessTokenDomain::CreateCacheKey(
        TOptional<FString> DisplayItemId
    )
    {
        return FString("") +
            (DisplayItemId.IsSet() ? *DisplayItemId : "null");
    }

    FDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FDisplayItemAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FDisplayItemAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDisplayItemAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FDisplayItem>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Showcase::Model::FDisplayItem> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Showcase::Model::FDisplayItem>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FDisplayItemDomain::CreateCacheKey(
                Self->DisplayItemId
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDisplayItemAccessTokenDomain::FModelTask>> FDisplayItemAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDisplayItemAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDisplayItemAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FDisplayItemPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FDisplayItem::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FDisplayItemDomain::CreateCacheKey(
                DisplayItemId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FDisplayItem>(obj));
            }
        );
    }

    void FDisplayItemAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FDisplayItem::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FDisplayItemDomain::CreateCacheKey(
                DisplayItemId
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

