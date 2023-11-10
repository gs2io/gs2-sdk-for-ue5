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
#include "Identifier/Domain/Iterator/DescribeUsersIterator.h"
#include "Identifier/Domain/Iterator/DescribeSecurityPoliciesIterator.h"
#include "Identifier/Domain/Iterator/DescribeCommonSecurityPoliciesIterator.h"
#include "Identifier/Domain/Iterator/DescribeIdentifiersIterator.h"
#include "Identifier/Domain/Iterator/DescribePasswordsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Identifier::Domain
{
    class FGs2IdentifierDomain;
    typedef TSharedPtr<FGs2IdentifierDomain> FGs2IdentifierDomainPtr;
}

namespace Gs2::Identifier::Domain::Model
{
    class FUserDomain;
    class FSecurityPolicyDomain;
    class FIdentifierDomain;
    class FPasswordDomain;
    class FAttachSecurityPolicyDomain;

    class GS2IDENTIFIER_API FProjectTokenDomain:
        public TSharedFromThis<FProjectTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Identifier::Domain::FGs2IdentifierDomainPtr Service;
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        public:
        TOptional<FString> AccessToken;
        TOptional<FString> TokenType;
        TOptional<int32> ExpiresIn;
        TOptional<FString> OwnerId;
        TOptional<FString> GetAccessToken() const
        {
            return AccessToken;
        }
        TOptional<FString> GetTokenType() const
        {
            return TokenType;
        }
        TOptional<int32> GetExpiresIn() const
        {
            return ExpiresIn;
        }
        TOptional<FString> GetOwnerId() const
        {
            return OwnerId;
        }
    private:

        FString ParentKey;

    public:

        FProjectTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Identifier::Domain::FGs2IdentifierDomainPtr& Service
            // ReSharper disable once CppMemberInitializersOrder
        );

        FProjectTokenDomain(
            const FProjectTokenDomain& From
        );

        class GS2IDENTIFIER_API FLoginTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FProjectTokenDomain>,
            public TSharedFromThis<FLoginTask>
        {
            const TSharedPtr<FProjectTokenDomain> Self;
            const Request::FLoginRequestPtr Request;
        public:
            explicit FLoginTask(
                const TSharedPtr<FProjectTokenDomain>& Self,
                const Request::FLoginRequestPtr Request
            );

            FLoginTask(
                const FLoginTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FProjectTokenDomain>> Result
            ) override;
        };
        friend FLoginTask;

        TSharedPtr<FAsyncTask<FLoginTask>> Login(
            Request::FLoginRequestPtr Request
        );

        class GS2IDENTIFIER_API FLoginByUserTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FProjectTokenDomain>,
            public TSharedFromThis<FLoginByUserTask>
        {
            const TSharedPtr<FProjectTokenDomain> Self;
            const Request::FLoginByUserRequestPtr Request;
        public:
            explicit FLoginByUserTask(
                const TSharedPtr<FProjectTokenDomain>& Self,
                const Request::FLoginByUserRequestPtr Request
            );

            FLoginByUserTask(
                const FLoginByUserTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FProjectTokenDomain>> Result
            ) override;
        };
        friend FLoginByUserTask;

        TSharedPtr<FAsyncTask<FLoginByUserTask>> LoginByUser(
            Request::FLoginByUserRequestPtr Request
        );

        static FString CreateCacheParentKey(
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2IDENTIFIER_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FProjectToken>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FProjectTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FProjectTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FProjectToken>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Identifier::Model::FProjectTokenPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FProjectTokenDomain> FProjectTokenDomainPtr;
}
