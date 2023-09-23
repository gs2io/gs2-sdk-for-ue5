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

#include "AdReward/Domain/Model/PointAccessToken.h"
#include "AdReward/Domain/Model/Point.h"
#include "AdReward/Domain/Model/Namespace.h"
#include "AdReward/Domain/Model/User.h"
#include "AdReward/Domain/Model/UserAccessToken.h"
#include "AdReward/Domain/Model/Point.h"
#include "AdReward/Domain/Model/PointAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::AdReward::Domain::Model
{

    FPointAccessTokenDomain::FPointAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::AdReward::FGs2AdRewardRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Point"
        ))
    {
    }

    FPointAccessTokenDomain::FPointAccessTokenDomain(
        const FPointAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FPointAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FPointAccessTokenDomain> Self,
        const Request::FGetPointRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->GetPoint(
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
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
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

    TSharedPtr<FAsyncTask<FPointAccessTokenDomain::FGetTask>> FPointAccessTokenDomain::Get(
        Request::FGetPointRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPointAccessTokenDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FPointAccessTokenDomain> Self,
        const Request::FConsumePointRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointAccessTokenDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointAccessTokenDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->ConsumePoint(
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
                const auto ParentKey = Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Point"
                );
                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointAccessTokenDomain::FConsumeTask>> FPointAccessTokenDomain::Consume(
        Request::FConsumePointRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FString FPointAccessTokenDomain::CreateCacheParentKey(
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

    FString FPointAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FPointAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FPointAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FPointAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPointAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::AdReward::Model::FPoint> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::AdReward::Model::FPoint>(
            Self->ParentKey,
            Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::AdReward::Request::FGetPointRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                );
                Self->Cache->Put(
                    Gs2::AdReward::Model::FPoint::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "point")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::AdReward::Model::FPoint>(
                Self->ParentKey,
                Gs2::AdReward::Domain::Model::FPointDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointAccessTokenDomain::FModelTask>> FPointAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPointAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
