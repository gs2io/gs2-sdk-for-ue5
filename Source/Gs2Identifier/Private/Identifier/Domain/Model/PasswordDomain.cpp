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

#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FPasswordDomain::FPasswordDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
        const TOptional<FString> UserName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        UserName(UserName),
        ParentKey(Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
            UserName,
            "Password"
        ))
    {
    }

    FPasswordDomain::FPasswordDomain(
        const FPasswordDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        UserName(From.UserName),
        ParentKey(From.ParentKey)
    {

    }

    FPasswordDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FCreatePasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FCreateTask>> FPasswordDomain::Create(
        Request::FCreatePasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FGetTask::FGetTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FGetPasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FGetTask>> FPasswordDomain::Get(
        Request::FGetPasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FEnableMfaTask::FEnableMfaTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FEnableMfaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FEnableMfaTask::FEnableMfaTask(
        const FEnableMfaTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FEnableMfaTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->ChallengeToken = *ResultModel->GetChallengeToken();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FEnableMfaTask>> FPasswordDomain::EnableMfa(
        Request::FEnableMfaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEnableMfaTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FChallengeMfaTask::FChallengeMfaTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FChallengeMfaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FChallengeMfaTask::FChallengeMfaTask(
        const FChallengeMfaTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FChallengeMfaTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FChallengeMfaTask>> FPasswordDomain::ChallengeMfa(
        Request::FChallengeMfaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FChallengeMfaTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FDisableMfaTask::FDisableMfaTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FDisableMfaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FDisableMfaTask::FDisableMfaTask(
        const FDisableMfaTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FDisableMfaTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FDisableMfaTask>> FPasswordDomain::DisableMfa(
        Request::FDisableMfaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDisableMfaTask>>(this->AsShared(), Request);
    }

    FPasswordDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPasswordDomain>& Self,
        const Request::FDeletePasswordRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPasswordDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FDeleteTask>> FPasswordDomain::Delete(
        Request::FDeletePasswordRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPasswordDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        FString ChildType
    )
    {
        return FString("") +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            ChildType;
    }

    FString FPasswordDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FPasswordDomain::FModelTask::FModelTask(
        const TSharedPtr<FPasswordDomain> Self
    ): Self(Self)
    {

    }

    FPasswordDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPasswordDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Identifier::Model::FPassword> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FPassword>(
            Self->ParentKey,
            Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Identifier::Request::FGetPasswordRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
                );
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FPassword::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "password")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FPassword>(
                Self->ParentKey,
                Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPasswordDomain::FModelTask>> FPasswordDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPasswordDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FPasswordDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FPasswordPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FPassword::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FPassword>(obj));
            }
        );
    }

    void FPasswordDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FPassword::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FPasswordDomain::CreateCacheKey(
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

