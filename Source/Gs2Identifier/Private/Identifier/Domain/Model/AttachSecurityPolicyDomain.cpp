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

#include "Identifier/Domain/Model/AttachSecurityPolicy.h"
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

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyDomain(
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
            "AttachSecurityPolicy"
        ))
    {
    }

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyDomain(
        const FAttachSecurityPolicyDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        UserName(From.UserName),
        ParentKey(From.ParentKey)
    {

    }

    FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask::FGetHasSecurityPolicyTask(
        const TSharedPtr<FAttachSecurityPolicyDomain>& Self,
        const Request::FGetHasSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask::FGetHasSecurityPolicyTask(
        const FGetHasSecurityPolicyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
                    Self->Gs2,
                    Self->Service,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
            const auto ParentKey = "identifier:SecurityPolicy";
            const auto Key = Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Identifier::Model::FSecurityPolicy::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask>> FAttachSecurityPolicyDomain::GetHasSecurityPolicy(
        Request::FGetHasSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetHasSecurityPolicyTask>>(this->AsShared(), Request);
    }

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask::FAttachSecurityPolicyTask(
        const TSharedPtr<FAttachSecurityPolicyDomain>& Self,
        const Request::FAttachSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask::FAttachSecurityPolicyTask(
        const FAttachSecurityPolicyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
                    Self->Gs2,
                    Self->Service,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
            const auto ParentKey = "identifier:SecurityPolicy";
            const auto Key = Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Identifier::Model::FSecurityPolicy::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask>> FAttachSecurityPolicyDomain::AttachSecurityPolicy(
        Request::FAttachSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAttachSecurityPolicyTask>>(this->AsShared(), Request);
    }

    FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask::FDetachSecurityPolicyTask(
        const TSharedPtr<FAttachSecurityPolicyDomain>& Self,
        const Request::FDetachSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask::FDetachSecurityPolicyTask(
        const FDetachSecurityPolicyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithUserName(Self->UserName);
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
                    Self->Gs2,
                    Self->Service,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
            const auto ParentKey = "identifier:SecurityPolicy";
            const auto Key = Gs2::Identifier::Domain::Model::FSecurityPolicyDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Identifier::Model::FSecurityPolicy::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask>> FAttachSecurityPolicyDomain::DetachSecurityPolicy(
        Request::FDetachSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDetachSecurityPolicyTask>>(this->AsShared(), Request);
    }

    FString FAttachSecurityPolicyDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        FString ChildType
    )
    {
        return FString("") +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            ChildType;
    }

    FString FAttachSecurityPolicyDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FAttachSecurityPolicyDomain::FModelTask::FModelTask(
        const TSharedPtr<FAttachSecurityPolicyDomain> Self
    ): Self(Self)
    {

    }

    FAttachSecurityPolicyDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FAttachSecurityPolicy>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Identifier::Model::FAttachSecurityPolicy> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FAttachSecurityPolicy>(
            Self->ParentKey,
            Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain::CreateCacheKey(
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FModelTask>> FAttachSecurityPolicyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAttachSecurityPolicyDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAttachSecurityPolicyDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FAttachSecurityPolicyPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain::CreateCacheKey(
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FAttachSecurityPolicy>(obj));
            }
        );
    }

    void FAttachSecurityPolicyDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain::CreateCacheKey(
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

