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

#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/SetCookieRequestEntryAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::News::Domain::Model
{

    FNewsAccessTokenDomain::FNewsAccessTokenDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "News"
        ))
    {
    }

    FNewsAccessTokenDomain::FNewsAccessTokenDomain(
        const FNewsAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FNewsAccessTokenDomain::FWantGrantTask::FWantGrantTask(
        const TSharedPtr<FNewsAccessTokenDomain> Self,
        const Request::FWantGrantRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNewsAccessTokenDomain::FWantGrantTask::FWantGrantTask(
        const FWantGrantTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsAccessTokenDomain::FWantGrantTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->WantGrant(
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
                    const auto ParentKey = Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId(),
                        "SetCookieRequestEntry"
                    );
                    const auto Key = Gs2::News::Domain::Model::FSetCookieRequestEntryDomain::CreateCacheKey(
                        Item->GetKey(),
                        Item->GetValue()
                    );
                    Self->Gs2->Cache->Put(
                        Gs2::News::Model::FSetCookieRequestEntry::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryAccessTokenDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::News::Domain::Model::FSetCookieRequestEntryAccessTokenDomain>(
                    Self->Gs2,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    (*ResultModel->GetItems())[i]->GetKey(),
                    (*ResultModel->GetItems())[i]->GetValue()
                )
            );
            const auto ParentKey = Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "SetCookieRequestEntry"
            );
            const auto Key = Gs2::News::Domain::Model::FSetCookieRequestEntryDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetKey(),
                (*ResultModel->GetItems())[i]->GetValue()
            );
            Self->Gs2->Cache->Put(
                Gs2::News::Model::FSetCookieRequestEntry::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetBrowserUrl().IsSet())
            {
                Self->BrowserUrl = ResultModel->GetBrowserUrl();
            }
            if (ResultModel->GetZipUrl().IsSet())
            {
                Self->ZipUrl = ResultModel->GetZipUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNewsAccessTokenDomain::FWantGrantTask>> FNewsAccessTokenDomain::WantGrant(
        Request::FWantGrantRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FWantGrantTask>>(this->AsShared(), Request);
    }

    FString FNewsAccessTokenDomain::CreateCacheParentKey(
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

    FString FNewsAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FNewsAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FNewsAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FNewsAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FNews>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::News::Model::FNews> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::News::Model::FNews>(
            Self->ParentKey,
            Gs2::News::Domain::Model::FNewsDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNewsAccessTokenDomain::FModelTask>> FNewsAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNewsAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNewsAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::News::Model::FNewsPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::News::Model::FNews::TypeName,
            ParentKey,
            Gs2::News::Domain::Model::FNewsDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::News::Model::FNews>(obj));
            }
        );
    }

    void FNewsAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::News::Model::FNews::TypeName,
            ParentKey,
            Gs2::News::Domain::Model::FNewsDomain::CreateCacheKey(
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

