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

#include "Identifier/Domain/Model/ProjectToken.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FProjectTokenDomain::FProjectTokenDomain(
        const Core::Domain::FGs2Ptr Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        ParentKey("identifier:ProjectToken")
    {
    }

    FProjectTokenDomain::FProjectTokenDomain(
        const FProjectTokenDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FProjectTokenDomain::FLoginTask::FLoginTask(
        const TSharedPtr<FProjectTokenDomain> Self,
        const Request::FLoginRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProjectTokenDomain::FLoginTask::FLoginTask(
        const FLoginTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProjectTokenDomain::FLoginTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FProjectTokenDomain>> Result
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
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetAccessToken().IsSet())
            {
                Self->AccessToken = Domain->AccessToken = ResultModel->GetAccessToken();
            }
            if (ResultModel->GetTokenType().IsSet())
            {
                Self->TokenType = Domain->TokenType = ResultModel->GetTokenType();
            }
            if (ResultModel->GetExpiresIn().IsSet())
            {
                Self->ExpiresIn = Domain->ExpiresIn = ResultModel->GetExpiresIn();
            }
            if (ResultModel->GetOwnerId().IsSet())
            {
                Self->OwnerId = Domain->OwnerId = ResultModel->GetOwnerId();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProjectTokenDomain::FLoginTask>> FProjectTokenDomain::Login(
        Request::FLoginRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLoginTask>>(this->AsShared(), Request);
    }

    FProjectTokenDomain::FLoginByUserTask::FLoginByUserTask(
        const TSharedPtr<FProjectTokenDomain> Self,
        const Request::FLoginByUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProjectTokenDomain::FLoginByUserTask::FLoginByUserTask(
        const FLoginByUserTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProjectTokenDomain::FLoginByUserTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FProjectTokenDomain>> Result
    )
    {
        const auto Future = Self->Client->LoginByUser(
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
                const auto ParentKey = FString("identifier:ProjectToken");
                const auto Key = Gs2::Identifier::Domain::Model::FProjectTokenDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FProjectToken::TypeName,
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

    TSharedPtr<FAsyncTask<FProjectTokenDomain::FLoginByUserTask>> FProjectTokenDomain::LoginByUser(
        Request::FLoginByUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FLoginByUserTask>>(this->AsShared(), Request);
    }

    FString FProjectTokenDomain::CreateCacheParentKey(
        FString ChildType
    )
    {
        return FString("") +
            ChildType;
    }

    FString FProjectTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FProjectTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FProjectTokenDomain> Self
    ): Self(Self)
    {

    }

    FProjectTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FProjectTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FProjectToken>> Result
    )
    {
        const auto ParentKey = FString("identifier:ProjectToken");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Identifier::Model::FProjectToken> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FProjectToken>(
            ParentKey,
            Gs2::Identifier::Domain::Model::FProjectTokenDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProjectTokenDomain::FModelTask>> FProjectTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FProjectTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FProjectTokenDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FProjectTokenPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FProjectToken::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FProjectTokenDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FProjectToken>(obj));
            }
        );
    }

    void FProjectTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FProjectToken::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FProjectTokenDomain::CreateCacheKey(
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

