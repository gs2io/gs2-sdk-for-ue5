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

#include "Identifier/Domain/Model/SecurityPolicy.h"
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

    FSecurityPolicyDomain::FSecurityPolicyDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
        const TOptional<FString> SecurityPolicyName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        SecurityPolicyName(SecurityPolicyName),
        ParentKey("identifier:SecurityPolicy")
    {
    }

    FSecurityPolicyDomain::FSecurityPolicyDomain(
        const FSecurityPolicyDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        SecurityPolicyName(From.SecurityPolicyName),
        ParentKey(From.ParentKey)
    {

    }

    FSecurityPolicyDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSecurityPolicyDomain>& Self,
        const Request::FUpdateSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSecurityPolicyDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
    )
    {
        Request
            ->WithSecurityPolicyName(Self->SecurityPolicyName);
        const auto Future = Self->Client->UpdateSecurityPolicy(
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
                const auto ParentKey = FString("identifier:SecurityPolicy");
                const auto Key = Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FSecurityPolicy::TypeName,
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

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FUpdateTask>> FSecurityPolicyDomain::Update(
        Request::FUpdateSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSecurityPolicyDomain::FGetTask::FGetTask(
        const TSharedPtr<FSecurityPolicyDomain>& Self,
        const Request::FGetSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSecurityPolicyDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>> Result
    )
    {
        Request
            ->WithSecurityPolicyName(Self->SecurityPolicyName);
        const auto Future = Self->Client->GetSecurityPolicy(
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
                const auto ParentKey = FString("identifier:SecurityPolicy");
                const auto Key = Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FSecurityPolicy::TypeName,
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

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FGetTask>> FSecurityPolicyDomain::Get(
        Request::FGetSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSecurityPolicyDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSecurityPolicyDomain>& Self,
        const Request::FDeleteSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSecurityPolicyDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
    )
    {
        Request
            ->WithSecurityPolicyName(Self->SecurityPolicyName);
        const auto Future = Self->Client->DeleteSecurityPolicy(
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
                const auto ParentKey = FString("identifier:SecurityPolicy");
                const auto Key = Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Identifier::Model::FSecurityPolicy::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FDeleteTask>> FSecurityPolicyDomain::Delete(
        Request::FDeleteSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSecurityPolicyDomain::CreateCacheParentKey(
        TOptional<FString> SecurityPolicyName,
        FString ChildType
    )
    {
        return FString("") +
            (SecurityPolicyName.IsSet() ? *SecurityPolicyName : "null") + ":" +
            ChildType;
    }

    FString FSecurityPolicyDomain::CreateCacheKey(
        TOptional<FString> SecurityPolicyName
    )
    {
        return FString("") +
            (SecurityPolicyName.IsSet() ? *SecurityPolicyName : "null");
    }

    FSecurityPolicyDomain::FModelTask::FModelTask(
        const TSharedPtr<FSecurityPolicyDomain> Self
    ): Self(Self)
    {

    }

    FSecurityPolicyDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>> Result
    )
    {
        const auto ParentKey = FString("identifier:SecurityPolicy");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Identifier::Model::FSecurityPolicy> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FSecurityPolicy>(
            ParentKey,
            Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                Self->SecurityPolicyName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Identifier::Request::FGetSecurityPolicyRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                    Self->SecurityPolicyName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FSecurityPolicy::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "securityPolicy")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FSecurityPolicy>(
                ParentKey,
                Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                    Self->SecurityPolicyName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FModelTask>> FSecurityPolicyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSecurityPolicyDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSecurityPolicyDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FSecurityPolicyPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FSecurityPolicy::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                SecurityPolicyName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>(obj));
            }
        );
    }

    void FSecurityPolicyDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FSecurityPolicy::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                SecurityPolicyName
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

