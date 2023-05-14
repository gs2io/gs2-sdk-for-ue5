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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FIdentifierDomain::FIdentifierDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> UserName,
        const TOptional<FString> ClientId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Session)),
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
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FIdentifierDomain::FGetTask::FGetTask(
        const TSharedPtr<FIdentifierDomain> Self,
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
                Self->Cache->Put(
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
        const TSharedPtr<FIdentifierDomain> Self,
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
                Self->Cache->Delete(Gs2::Identifier::Model::FIdentifier::TypeName, ParentKey, Key);
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
        return FString() +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            (ClientId.IsSet() ? *ClientId : "null") + ":" +
            ChildType;
    }

    FString FIdentifierDomain::CreateCacheKey(
        TOptional<FString> ClientId
    )
    {
        return FString() +
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
        auto Value = Self->Cache->Get<Gs2::Identifier::Model::FIdentifier>(
            Self->ParentKey,
            Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                Self->ClientId
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Identifier::Request::FGetIdentifierRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "identifier")
                    {
                        Self->Cache->Delete(
                            Gs2::Identifier::Model::FIdentifier::TypeName,
                            Self->ParentKey,
                            Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                                Self->ClientId
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Identifier::Model::FIdentifier>(
                Self->ParentKey,
                Gs2::Identifier::Domain::Model::FIdentifierDomain::CreateCacheKey(
                    Self->ClientId
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIdentifierDomain::FModelTask>> FIdentifierDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FIdentifierDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

