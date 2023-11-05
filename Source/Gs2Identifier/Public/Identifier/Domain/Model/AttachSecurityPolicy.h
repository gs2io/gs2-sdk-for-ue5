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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Identifier::Domain::Model
{
    class FUserDomain;
    class FSecurityPolicyDomain;
    class FIdentifierDomain;
    class FPasswordDomain;
    class FAttachSecurityPolicyDomain;

    class GS2IDENTIFIER_API FAttachSecurityPolicyDomain:
        public TSharedFromThis<FAttachSecurityPolicyDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        public:
        TOptional<FString> UserName;
    private:

        FString ParentKey;

    public:

        FAttachSecurityPolicyDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> UserName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAttachSecurityPolicyDomain(
            const FAttachSecurityPolicyDomain& From
        );

        class GS2IDENTIFIER_API FGetHasSecurityPolicyTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>,
            public TSharedFromThis<FGetHasSecurityPolicyTask>
        {
            const TSharedPtr<FAttachSecurityPolicyDomain> Self;
            const Request::FGetHasSecurityPolicyRequestPtr Request;
        public:
            explicit FGetHasSecurityPolicyTask(
                const TSharedPtr<FAttachSecurityPolicyDomain> Self,
                const Request::FGetHasSecurityPolicyRequestPtr Request
            );

            FGetHasSecurityPolicyTask(
                const FGetHasSecurityPolicyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
            ) override;
        };
        friend FGetHasSecurityPolicyTask;

        TSharedPtr<FAsyncTask<FGetHasSecurityPolicyTask>> GetHasSecurityPolicy(
            Request::FGetHasSecurityPolicyRequestPtr Request
        );

        class GS2IDENTIFIER_API FAttachSecurityPolicyTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>,
            public TSharedFromThis<FAttachSecurityPolicyTask>
        {
            const TSharedPtr<FAttachSecurityPolicyDomain> Self;
            const Request::FAttachSecurityPolicyRequestPtr Request;
        public:
            explicit FAttachSecurityPolicyTask(
                const TSharedPtr<FAttachSecurityPolicyDomain> Self,
                const Request::FAttachSecurityPolicyRequestPtr Request
            );

            FAttachSecurityPolicyTask(
                const FAttachSecurityPolicyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
            ) override;
        };
        friend FAttachSecurityPolicyTask;

        TSharedPtr<FAsyncTask<FAttachSecurityPolicyTask>> AttachSecurityPolicy(
            Request::FAttachSecurityPolicyRequestPtr Request
        );

        class GS2IDENTIFIER_API FDetachSecurityPolicyTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>,
            public TSharedFromThis<FDetachSecurityPolicyTask>
        {
            const TSharedPtr<FAttachSecurityPolicyDomain> Self;
            const Request::FDetachSecurityPolicyRequestPtr Request;
        public:
            explicit FDetachSecurityPolicyTask(
                const TSharedPtr<FAttachSecurityPolicyDomain> Self,
                const Request::FDetachSecurityPolicyRequestPtr Request
            );

            FDetachSecurityPolicyTask(
                const FDetachSecurityPolicyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
            ) override;
        };
        friend FDetachSecurityPolicyTask;

        TSharedPtr<FAsyncTask<FDetachSecurityPolicyTask>> DetachSecurityPolicy(
            Request::FDetachSecurityPolicyRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> UserName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2IDENTIFIER_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FAttachSecurityPolicy>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FAttachSecurityPolicyDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAttachSecurityPolicyDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FAttachSecurityPolicy>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Identifier::Model::FAttachSecurityPolicyPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FAttachSecurityPolicyDomain> FAttachSecurityPolicyDomainPtr;
}
