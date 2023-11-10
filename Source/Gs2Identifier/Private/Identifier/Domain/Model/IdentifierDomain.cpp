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

#include "Identifier/Domain/Model/Identifier.h"
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

    FIdentifierDomain::FIdentifierDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
        const TOptional<FString> UserName,
        const TOptional<FString> ClientId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        UserName(UserName),
        ClientId(ClientId),
        ParentKey(Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
            UserName,
            "Identifier"
        ))
    {
    }

    FIdentifierDomain::FIdentifierDomain(
        const FIdentifierDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        UserName(From.UserName),
        ClientId(From.ClientId),
        ParentKey(From.ParentKey)
    {

    }

    FIdentifierDomain::FGetTask::FGetTask(
        const TSharedPtr<FIdentifierDomain>& Self,
        const Request::FGetIdentifierRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIdentifierDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIdentifierDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FIdentifier>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName)
            ->WithClientId(Self->ClientId);
        const auto Future = Self->Client->GetIdentifier(
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
                const auto ParentKey = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->UserName,
                    "Identifier"
                );
                const auto Key = Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetClientId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FIdentifier::TypeName,
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

    TSharedPtr<FAsyncTask<FIdentifierDomain::FGetTask>> FIdentifierDomain::Get(
        Request::FGetIdentifierRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FIdentifierDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FIdentifierDomain>& Self,
        const Request::FDeleteIdentifierRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIdentifierDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIdentifierDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName)
            ->WithClientId(Self->ClientId);
        const auto Future = Self->Client->DeleteIdentifier(
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
                const auto ParentKey = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->UserName,
                    "Identifier"
                );
                const auto Key = Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetClientId()
                );
                Self->Gs2->Cache->Delete(Gs2::Identifier::Model::FIdentifier::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIdentifierDomain::FDeleteTask>> FIdentifierDomain::Delete(
        Request::FDeleteIdentifierRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FIdentifierDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        TOptional<FString> ClientId,
        FString ChildType
    )
    {
        return FString("") +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            (ClientId.IsSet() ? *ClientId : "null") + ":" +
            ChildType;
    }

    FString FIdentifierDomain::CreateCacheKey(
        TOptional<FString> ClientId
    )
    {
        return FString("") +
            (ClientId.IsSet() ? *ClientId : "null");
    }

    FIdentifierDomain::FModelTask::FModelTask(
        const TSharedPtr<FIdentifierDomain> Self
    ): Self(Self)
    {

    }

    FIdentifierDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIdentifierDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FIdentifier>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Identifier::Model::FIdentifier> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FIdentifier>(
            Self->ParentKey,
            Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                Self->ClientId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Identifier::Request::FGetIdentifierRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                    Self->ClientId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Identifier::Model::FIdentifier::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "identifier")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Identifier::Model::FIdentifier>(
                Self->ParentKey,
                Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                    Self->ClientId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIdentifierDomain::FModelTask>> FIdentifierDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FIdentifierDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FIdentifierDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FIdentifierPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FIdentifier::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                ClientId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FIdentifier>(obj));
            }
        );
    }

    void FIdentifierDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FIdentifier::TypeName,
            ParentKey,
            Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                ClientId
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

