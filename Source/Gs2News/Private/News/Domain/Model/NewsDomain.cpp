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

#include "News/Domain/Model/News.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::News::Domain::Model
{

    FNewsDomain::FNewsDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "News"
        ))
    {
    }

    FNewsDomain::FNewsDomain(
        const FNewsDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FNewsDomain::FWantGrantTask::FWantGrantTask(
        const TSharedPtr<FNewsDomain> Self,
        const Request::FWantGrantByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNewsDomain::FWantGrantTask::FWantGrantTask(
        const FWantGrantTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsDomain::FWantGrantTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->WantGrantByUserId(
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
                        Self->UserId,
                        "SetCookieRequestEntry"
                    );
                    const auto Key = Gs2::News::Domain::Model::FSetCookieRequestEntryDomain::CreateCacheKey(
                        Item->GetKey(),
                        Item->GetValue()
                    );
                    Self->Cache->Put(
                        Gs2::News::Model::FSetCookieRequestEntry::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::News::Domain::Model::FSetCookieRequestEntryDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    Request->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetKey(),
                    (*ResultModel->GetItems())[i]->GetValue()
                )
            );
            const auto ParentKey = Gs2::News::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "SetCookieRequestEntry"
            );
            const auto Key = Gs2::News::Domain::Model::FSetCookieRequestEntryDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetKey(),
                (*ResultModel->GetItems())[i]->GetValue()
            );
            Self->Cache->Put(
                Gs2::News::Model::FSetCookieRequestEntry::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        Self->BrowserUrl = ResultModel->GetBrowserUrl();
        Self->ZipUrl = ResultModel->GetZipUrl();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNewsDomain::FWantGrantTask>> FNewsDomain::WantGrant(
        Request::FWantGrantByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FWantGrantTask>>(this->AsShared(), Request);
    }

    FString FNewsDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FNewsDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FNewsDomain::FModelTask::FModelTask(
        const TSharedPtr<FNewsDomain> Self
    ): Self(Self)
    {

    }

    FNewsDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNewsDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FNews>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::News::Model::FNews> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::News::Model::FNews>(
            Self->ParentKey,
            Gs2::News::Domain::Model::FNewsDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNewsDomain::FModelTask>> FNewsDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNewsDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

