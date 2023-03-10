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

#include "Auth/Domain/Model/AccessToken.h"
#include "Auth/Domain/Model/AccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Auth::Domain::Model
{

    FAccessTokenDomain::FAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Auth::FGs2AuthRestClient>(Session)),
        ParentKey("auth:AccessToken")
    {
    }

    FAccessTokenDomain::FAccessTokenDomain(
        const FAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FAccessTokenDomain::FLoginTask::FLoginTask(
        const TSharedPtr<FAccessTokenDomain> Self,
        const Request::FLoginRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccessTokenDomain::FLoginTask::FLoginTask(
        const FLoginTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccessTokenDomain::FLoginTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        const auto Future = Self->Client->Login(
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
            
        }
        const auto Domain = Self;
        Self->Cache->Put<Gs2::Auth::Model::FAccessToken>(
            Self->ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(),
            MakeShared<Gs2::Auth::Model::FAccessToken>()
                    ->WithToken(ResultModel->GetToken())
                    ->WithUserId(ResultModel->GetUserId())
                    ->WithExpire(ResultModel->GetExpire()),
            FDateTime::Now() + FTimespan::FromMinutes(15)
        );
        Domain->Token = Domain->Token = ResultModel->GetToken();
        Domain->UserId = Domain->UserId = ResultModel->GetUserId();
        Domain->Expire = Domain->Expire = ResultModel->GetExpire();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FLoginTask>> FAccessTokenDomain::Login(
        Request::FLoginRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLoginTask>>(this->AsShared(), Request);
    }

    FAccessTokenDomain::FLoginBySignatureTask::FLoginBySignatureTask(
        const TSharedPtr<FAccessTokenDomain> Self,
        const Request::FLoginBySignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccessTokenDomain::FLoginBySignatureTask::FLoginBySignatureTask(
        const FLoginBySignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccessTokenDomain::FLoginBySignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        const auto Future = Self->Client->LoginBySignature(
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
            
        }
        const auto Domain = Self;
        Self->Cache->Put<Gs2::Auth::Model::FAccessToken>(
            Self->ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(),
            MakeShared<Gs2::Auth::Model::FAccessToken>()
                    ->WithToken(ResultModel->GetToken())
                    ->WithUserId(ResultModel->GetUserId())
                    ->WithExpire(ResultModel->GetExpire()),
            FDateTime::Now() + FTimespan::FromMinutes(15)
        );
        Domain->Token = Domain->Token = ResultModel->GetToken();
        Domain->UserId = Domain->UserId = ResultModel->GetUserId();
        Domain->Expire = Domain->Expire = ResultModel->GetExpire();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FLoginBySignatureTask>> FAccessTokenDomain::LoginBySignature(
        Request::FLoginBySignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLoginBySignatureTask>>(this->AsShared(), Request);
    }

    FString FAccessTokenDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString() +
            ChildType;
    }

    FString FAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Model::FAccessToken>> Result
    )
    {
        const auto ParentKey = FString("auth:AccessToken");
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Auth::Model::FAccessToken>(
            Self->ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(
            )
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FModelTask>> FAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

