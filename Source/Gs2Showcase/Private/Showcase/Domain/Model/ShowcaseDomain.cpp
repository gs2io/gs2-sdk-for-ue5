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

#include "Showcase/Domain/Model/Showcase.h"
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
#include "Showcase/Domain/Model/SalesItem.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Showcase::Domain::Model
{

    FShowcaseDomain::FShowcaseDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> ShowcaseName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Showcase::FGs2ShowcaseRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ShowcaseName(ShowcaseName),
        ParentKey(Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Showcase"
        ))
    {
    }

    FShowcaseDomain::FShowcaseDomain(
        const FShowcaseDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ShowcaseName(From.ShowcaseName),
        ParentKey(From.ParentKey)
    {

    }

    FShowcaseDomain::FGetTask::FGetTask(
        const TSharedPtr<FShowcaseDomain>& Self,
        const Request::FGetShowcaseByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FShowcaseDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FShowcaseDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FShowcase>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithShowcaseName(Self->ShowcaseName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetShowcaseByUserId(
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
                const auto ParentKey = Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Showcase"
                );
                const auto Key = Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Showcase::Model::FShowcase::TypeName,
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

    TSharedPtr<FAsyncTask<FShowcaseDomain::FGetTask>> FShowcaseDomain::Get(
        Request::FGetShowcaseByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Showcase::Domain::Model::FDisplayItemDomain> FShowcaseDomain::DisplayItem(
        const FString DisplayItemId
    )
    {
        return MakeShared<Gs2::Showcase::Domain::Model::FDisplayItemDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            ShowcaseName,
            DisplayItemId == TEXT("") ? TOptional<FString>() : TOptional<FString>(DisplayItemId)
        );
    }

    FString FShowcaseDomain::CreateCacheParentKey(
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

    FString FShowcaseDomain::CreateCacheKey(
        TOptional<FString> ShowcaseName
    )
    {
        return FString("") +
            (ShowcaseName.IsSet() ? *ShowcaseName : "null");
    }

    FShowcaseDomain::FModelTask::FModelTask(
        const TSharedPtr<FShowcaseDomain> Self
    ): Self(Self)
    {

    }

    FShowcaseDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FShowcaseDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FShowcase>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Showcase::Model::FShowcase> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Showcase::Model::FShowcase>(
            Self->ParentKey,
            Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheKey(
                Self->ShowcaseName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Showcase::Request::FGetShowcaseByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheKey(
                    Self->ShowcaseName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Showcase::Model::FShowcase::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "showcase")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Showcase::Model::FShowcase>(
                Self->ParentKey,
                Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheKey(
                    Self->ShowcaseName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FShowcaseDomain::FModelTask>> FShowcaseDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FShowcaseDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FShowcaseDomain::Subscribe(
        TFunction<void(Gs2::Showcase::Model::FShowcasePtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Showcase::Model::FShowcase::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheKey(
                ShowcaseName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Showcase::Model::FShowcase>(obj));
            }
        );
    }

    void FShowcaseDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Showcase::Model::FShowcase::TypeName,
            ParentKey,
            Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheKey(
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

