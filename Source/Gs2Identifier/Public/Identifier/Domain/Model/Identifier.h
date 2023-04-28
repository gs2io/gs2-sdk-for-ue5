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
#include "Auth/Gs2Auth.h"
#include "Identifier/Gs2Identifier.h"
#include "Identifier/Domain/Iterator/DescribeUsersIterator.h"
#include "Identifier/Domain/Iterator/DescribeSecurityPoliciesIterator.h"
#include "Identifier/Domain/Iterator/DescribeCommonSecurityPoliciesIterator.h"
#include "Identifier/Domain/Iterator/DescribeIdentifiersIterator.h"
#include "Identifier/Domain/Iterator/DescribePasswordsIterator.h"

namespace Gs2::Identifier::Domain::Model
{
    class FUserDomain;
    class FSecurityPolicyDomain;
    class FIdentifierDomain;
    class FPasswordDomain;
    class FAttachSecurityPolicyDomain;

    class GS2IDENTIFIER_API FIdentifierDomain:
        public TSharedFromThis<FIdentifierDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        public:
        TOptional<FString> ClientSecret;
        TOptional<FString> Status;
        TOptional<FString> GetClientSecret() const
        {
            return ClientSecret;
        }
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> UserName;
        TOptional<FString> ClientId;
    private:

        FString ParentKey;

    public:

        FIdentifierDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> UserName,
            const TOptional<FString> ClientId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FIdentifierDomain(
            const FIdentifierDomain& From
        );

        class GS2IDENTIFIER_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FIdentifier>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FIdentifierDomain> Self;
            const Request::FGetIdentifierRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FIdentifierDomain> Self,
                const Request::FGetIdentifierRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FIdentifier>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetIdentifierRequestPtr Request
        );

        class GS2IDENTIFIER_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FIdentifierDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FIdentifierDomain> Self;
            const Request::FDeleteIdentifierRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FIdentifierDomain> Self,
                const Request::FDeleteIdentifierRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteIdentifierRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> UserName,
            TOptional<FString> ClientId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ClientId
        );

        class GS2IDENTIFIER_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FIdentifier>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FIdentifierDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FIdentifierDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FIdentifier>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FIdentifierDomain> FIdentifierDomainPtr;
}
