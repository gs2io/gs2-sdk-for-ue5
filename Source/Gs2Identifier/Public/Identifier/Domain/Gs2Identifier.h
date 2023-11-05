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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Identifier/Gs2Identifier.h"

// Model
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"
#include "Identifier/Domain/Model/ProjectToken.h"

// Iterator
#include "Identifier/Domain/Iterator/DescribeUsersIterator.h"
#include "Identifier/Domain/Iterator/DescribeSecurityPoliciesIterator.h"
#include "Identifier/Domain/Iterator/DescribeCommonSecurityPoliciesIterator.h"
#include "Identifier/Domain/Iterator/DescribeIdentifiersIterator.h"
#include "Identifier/Domain/Iterator/DescribePasswordsIterator.h"

// Notification

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Identifier::Domain
{

    class GS2IDENTIFIER_API FGs2IdentifierDomain:
        public TSharedFromThis<FGs2IdentifierDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2IdentifierDomain(
            const Core::Domain::FGs2Ptr Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2IdentifierDomain(
            const FGs2IdentifierDomain& From
        );

        class GS2IDENTIFIER_API FCreateUserTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FUserDomain>,
            public TSharedFromThis<FCreateUserTask>
        {
            const TSharedPtr<FGs2IdentifierDomain> Self;
            const Request::FCreateUserRequestPtr Request;
        public:
            explicit FCreateUserTask(
                const TSharedPtr<FGs2IdentifierDomain> Self,
                const Request::FCreateUserRequestPtr Request
            );

            FCreateUserTask(
                const FCreateUserTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FCreateUserTask;

        TSharedPtr<FAsyncTask<FCreateUserTask>> CreateUser(
            Request::FCreateUserRequestPtr Request
        );

        class GS2IDENTIFIER_API FCreateSecurityPolicyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>,
            public TSharedFromThis<FCreateSecurityPolicyTask>
        {
            const TSharedPtr<FGs2IdentifierDomain> Self;
            const Request::FCreateSecurityPolicyRequestPtr Request;
        public:
            explicit FCreateSecurityPolicyTask(
                const TSharedPtr<FGs2IdentifierDomain> Self,
                const Request::FCreateSecurityPolicyRequestPtr Request
            );

            FCreateSecurityPolicyTask(
                const FCreateSecurityPolicyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
            ) override;
        };
        friend FCreateSecurityPolicyTask;

        TSharedPtr<FAsyncTask<FCreateSecurityPolicyTask>> CreateSecurityPolicy(
            Request::FCreateSecurityPolicyRequestPtr Request
        );

        Gs2::Identifier::Domain::Iterator::FDescribeUsersIteratorPtr Users(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeUsers(
            TFunction<void()> Callback
        );

        void UnsubscribeUsers(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain> User(
            const FString UserName
        ) const;

        Gs2::Identifier::Domain::Iterator::FDescribeSecurityPoliciesIteratorPtr SecurityPolicies(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSecurityPolicies(
            TFunction<void()> Callback
        );

        void UnsubscribeSecurityPolicies(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Identifier::Domain::Iterator::FDescribeCommonSecurityPoliciesIteratorPtr CommonSecurityPolicies(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCommonSecurityPolicies(
            TFunction<void()> Callback
        );

        void UnsubscribeCommonSecurityPolicies(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain> SecurityPolicy(
            const FString SecurityPolicyName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2IdentifierDomain> FGs2IdentifierDomainPtr;
}
