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

#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FUserDomain::FUserDomain(
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
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FUserDomain::FCreateAwaitTask::FCreateAwaitTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FCreateAwaitByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateAwaitTask::FCreateAwaitTask(
        const FCreateAwaitTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateAwaitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CreateAwaitByUserId(
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
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Exchange::Model::FAwait>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Exchange::Domain::Model::FAwaitDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );
        Domain->UnlockAt = *ResultModel->GetUnlockAt();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCreateAwaitTask>> FUserDomain::CreateAwait(
        Request::FCreateAwaitByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateAwaitTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Exchange::Domain::Model::FExchangeDomain> FUserDomain::Exchange(
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FExchangeDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId
        );
    }

    Gs2::Exchange::Domain::Iterator::FDescribeAwaitsByUserIdIteratorPtr FUserDomain::Awaits(
        const TOptional<FString> RateName
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            RateName
        );
    }

    TSharedPtr<Gs2::Exchange::Domain::Model::FAwaitDomain> FUserDomain::Await(
        const FString AwaitName
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FAwaitDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            AwaitName
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString() +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

