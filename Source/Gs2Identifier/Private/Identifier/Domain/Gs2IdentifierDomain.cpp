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

// ReSharper disable CppUnusedIncludeDirective

#include "Identifier/Domain/Gs2Identifier.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"

namespace Gs2::Identifier::Domain
{

    FGs2IdentifierDomain::FGs2IdentifierDomain(
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
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Session)),
        ParentKey("identifier")
    {
    }

    FGs2IdentifierDomain::FGs2IdentifierDomain(
        const FGs2IdentifierDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGs2IdentifierDomain::FCreateUserTask::FCreateUserTask(
        TSharedPtr<FGs2IdentifierDomain> Self,
        const Request::FCreateUserRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2IdentifierDomain::FCreateUserTask::FCreateUserTask(
        const FCreateUserTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2IdentifierDomain::FCreateUserTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateUser(
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
                Self->Cache->Put<Gs2::Identifier::Model::FUser>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Identifier::Domain::Model::FUserDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2IdentifierDomain::FCreateUserTask>> FGs2IdentifierDomain::CreateUser(
        Request::FCreateUserRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateUserTask>>(this->AsShared(), Request);
    }

    FGs2IdentifierDomain::FCreateSecurityPolicyTask::FCreateSecurityPolicyTask(
        TSharedPtr<FGs2IdentifierDomain> Self,
        const Request::FCreateSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2IdentifierDomain::FCreateSecurityPolicyTask::FCreateSecurityPolicyTask(
        const FCreateSecurityPolicyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2IdentifierDomain::FCreateSecurityPolicyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateSecurityPolicy(
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
                Self->Cache->Put<Gs2::Identifier::Model::FSecurityPolicy>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2IdentifierDomain::FCreateSecurityPolicyTask>> FGs2IdentifierDomain::CreateSecurityPolicy(
        Request::FCreateSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateSecurityPolicyTask>>(this->AsShared(), Request);
    }

    Gs2::Identifier::Domain::Iterator::FDescribeUsersIteratorPtr FGs2IdentifierDomain::Users(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Iterator::FDescribeUsersIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain> FGs2IdentifierDomain::User(
        const FString UserName
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            UserName
        );
    }

    Gs2::Identifier::Domain::Iterator::FDescribeSecurityPoliciesIteratorPtr FGs2IdentifierDomain::SecurityPolicies(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Iterator::FDescribeSecurityPoliciesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Identifier::Domain::Iterator::FDescribeCommonSecurityPoliciesIteratorPtr FGs2IdentifierDomain::CommonSecurityPolicies(
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Iterator::FDescribeCommonSecurityPoliciesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain> FGs2IdentifierDomain::SecurityPolicy(
        const FString SecurityPolicyName
    ) const
    {
        return MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            SecurityPolicyName
        );
    }

    void FGs2IdentifierDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2IdentifierDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2IdentifierDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2IdentifierDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

