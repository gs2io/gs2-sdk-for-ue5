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

#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> UserName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Session)),
        UserName(UserName),
        ParentKey("identifier:User")
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

    FUserDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FUpdateUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->UpdateUser(
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
                const auto ParentKey = FString("identifier:User");
                const auto Key = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Identifier::Model::FUser::TypeName,
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

    TSharedPtr<FAsyncTask<FUserDomain::FUpdateTask>> FUserDomain::Update(
        Request::FUpdateUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FUserDomain::FGetTask::FGetTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FGetUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FUser>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->GetUser(
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
                const auto ParentKey = FString("identifier:User");
                const auto Key = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Identifier::Model::FUser::TypeName,
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

    TSharedPtr<FAsyncTask<FUserDomain::FGetTask>> FUserDomain::Get(
        Request::FGetUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FDeleteUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->DeleteUser(
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
                const auto ParentKey = FString("identifier:User");
                const auto Key = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Identifier::Model::FUser::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDeleteTask>> FUserDomain::Delete(
        Request::FDeleteUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FUserDomain::FCreateIdentifierTask::FCreateIdentifierTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FCreateIdentifierRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateIdentifierTask::FCreateIdentifierTask(
        const FCreateIdentifierTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateIdentifierTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain>> Result
    )
    {
        Request
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->CreateIdentifier(
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
        auto Domain = MakeShared<Gs2::Identifier::Domain::Model::FIdentifierDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetUserName(),
            ResultModel->GetItem()->GetClientId()
        );
        Domain->ClientSecret = *ResultModel->GetClientSecret();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FCreateIdentifierTask>> FUserDomain::CreateIdentifier(
        Request::FCreateIdentifierRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateIdentifierTask>>(this->AsShared(), Request);
    }

    Gs2::Identifier::Domain::Iterator::FDescribeIdentifiersIteratorPtr FUserDomain::Identifiers(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Iterator::FDescribeIdentifiersIterator>(
            Cache,
            Client,
            UserName
        );
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain> FUserDomain::Identifier(
        const FString ClientId
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FIdentifierDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            UserName,
            ClientId
        );
    }

    Gs2::Identifier::Domain::Iterator::FDescribePasswordsIteratorPtr FUserDomain::Passwords(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Iterator::FDescribePasswordsIterator>(
            Cache,
            Client,
            UserName
        );
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain> FUserDomain::Password(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FPasswordDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            UserName
        );
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain> FUserDomain::AttachSecurityPolicy(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            UserName
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        FString ChildType
    )
    {
        return FString() +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserName
    )
    {
        return FString() +
            (UserName.IsSet() ? *UserName : "null");
    }

    FUserDomain::FModelTask::FModelTask(
        const TSharedPtr<FUserDomain> Self
    ): Self(Self)
    {

    }

    FUserDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FUser>> Result
    )
    {
        const auto ParentKey = FString("identifier:User");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Identifier::Model::FUser> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Identifier::Model::FUser>(
            ParentKey,
            Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                Self->UserName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Identifier::Request::FGetUserRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                    Self->UserName
                );
                Self->Cache->Put(
                    Gs2::Identifier::Model::FUser::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "user")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Identifier::Model::FUser>(
                ParentKey,
                Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheKey(
                    Self->UserName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FModelTask>> FUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FUserDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

