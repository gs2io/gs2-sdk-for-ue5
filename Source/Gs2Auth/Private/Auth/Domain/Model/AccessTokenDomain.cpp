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

#include "Auth/Domain/Model/AccessToken.h"
#include "Auth/Domain/Model/AccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Auth::Domain::Model
{

    FAccessTokenDomain::FAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Auth::Domain::FGs2AuthDomainPtr& Service
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Auth::FGs2AuthRestClient>(Gs2->RestSession)),
        ParentKey("auth:AccessToken")
    {
    }

    FAccessTokenDomain::FAccessTokenDomain(
        const FAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FAccessTokenDomain::FLoginTask::FLoginTask(
        const TSharedPtr<FAccessTokenDomain>& Self,
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
        Self->Gs2->Cache->Put(
            Gs2::Auth::Model::FAccessToken::TypeName,
            Self->ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(),
            MakeShared<Gs2::Auth::Model::FAccessToken>()
                    ->WithToken(ResultModel->GetToken())
                    ->WithUserId(ResultModel->GetUserId())
                    ->WithExpire(ResultModel->GetExpire()),
            FDateTime::Now() + FTimespan::FromMinutes(15)
        );
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetToken().IsSet())
            {
                Self->Token = Domain->Token = ResultModel->GetToken();
            }
            if (ResultModel->GetUserId().IsSet())
            {
                Self->UserId = Domain->UserId = ResultModel->GetUserId();
            }
            if (ResultModel->GetExpire().IsSet())
            {
                Self->Expire = Domain->Expire = ResultModel->GetExpire();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FLoginTask>> FAccessTokenDomain::Login(
        Request::FLoginRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLoginTask>>(this->AsShared(), Request);
    }

    FAccessTokenDomain::FLoginBySignatureTask::FLoginBySignatureTask(
        const TSharedPtr<FAccessTokenDomain>& Self,
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
        Self->Gs2->Cache->Put(
            Gs2::Auth::Model::FAccessToken::TypeName,
            Self->ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(),
            MakeShared<Gs2::Auth::Model::FAccessToken>()
                    ->WithToken(ResultModel->GetToken())
                    ->WithUserId(ResultModel->GetUserId())
                    ->WithExpire(ResultModel->GetExpire()),
            FDateTime::Now() + FTimespan::FromMinutes(15)
        );
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetToken().IsSet())
            {
                Self->Token = Domain->Token = ResultModel->GetToken();
            }
            if (ResultModel->GetUserId().IsSet())
            {
                Self->UserId = Domain->UserId = ResultModel->GetUserId();
            }
            if (ResultModel->GetExpire().IsSet())
            {
                Self->Expire = Domain->Expire = ResultModel->GetExpire();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FLoginBySignatureTask>> FAccessTokenDomain::LoginBySignature(
        Request::FLoginBySignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLoginBySignatureTask>>(this->AsShared(), Request);
    }

    FAccessTokenDomain::FFederationTask::FFederationTask(
        const TSharedPtr<FAccessTokenDomain>& Self,
        const Request::FFederationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccessTokenDomain::FFederationTask::FFederationTask(
        const FFederationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccessTokenDomain::FFederationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        const auto Future = Self->Client->Federation(
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
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetToken().IsSet())
            {
                Self->Token = Domain->Token = ResultModel->GetToken();
            }
            if (ResultModel->GetUserId().IsSet())
            {
                Self->UserId = Domain->UserId = ResultModel->GetUserId();
            }
            if (ResultModel->GetExpire().IsSet())
            {
                Self->Expire = Domain->Expire = ResultModel->GetExpire();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FFederationTask>> FAccessTokenDomain::Federation(
        Request::FFederationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFederationTask>>(this->AsShared(), Request);
    }

    FAccessTokenDomain::FIssueTimeOffsetTokenTask::FIssueTimeOffsetTokenTask(
        const TSharedPtr<FAccessTokenDomain>& Self,
        const Request::FIssueTimeOffsetTokenByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAccessTokenDomain::FIssueTimeOffsetTokenTask::FIssueTimeOffsetTokenTask(
        const FIssueTimeOffsetTokenTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAccessTokenDomain::FIssueTimeOffsetTokenTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        const auto Future = Self->Client->IssueTimeOffsetTokenByUserId(
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
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetToken().IsSet())
            {
                Self->Token = Domain->Token = ResultModel->GetToken();
            }
            if (ResultModel->GetUserId().IsSet())
            {
                Self->UserId = Domain->UserId = ResultModel->GetUserId();
            }
            if (ResultModel->GetExpire().IsSet())
            {
                Self->Expire = Domain->Expire = ResultModel->GetExpire();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FIssueTimeOffsetTokenTask>> FAccessTokenDomain::IssueTimeOffsetToken(
        Request::FIssueTimeOffsetTokenByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIssueTimeOffsetTokenTask>>(this->AsShared(), Request);
    }

    FString FAccessTokenDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString("") +
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
        TSharedPtr<Gs2::Auth::Model::FAccessToken> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Auth::Model::FAccessToken>(
            ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAccessTokenDomain::FModelTask>> FAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Auth::Model::FAccessTokenPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Auth::Model::FAccessToken::TypeName,
            ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Auth::Model::FAccessToken>(obj));
            }
        );
    }

    void FAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Auth::Model::FAccessToken::TypeName,
            ParentKey,
            Gs2::Auth::Domain::Model::FAccessTokenDomain::CreateCacheKey(
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

