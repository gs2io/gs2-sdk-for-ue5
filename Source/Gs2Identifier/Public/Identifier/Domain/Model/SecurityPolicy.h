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
#include "Identifier/Domain/Iterator/DescribeAttachedGuardsIterator.h"

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

    class GS2IDENTIFIER_API FSecurityPolicyDomain:
        public TSharedFromThis<FSecurityPolicyDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Identifier::Domain::FGs2IdentifierDomainPtr Service;
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        public:
        TOptional<FString> SecurityPolicyName;
    private:

        FString ParentKey;

    public:

        FSecurityPolicyDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
            const TOptional<FString> SecurityPolicyName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSecurityPolicyDomain(
            const FSecurityPolicyDomain& From
        );

        class GS2IDENTIFIER_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FSecurityPolicyDomain> Self;
            const Request::FUpdateSecurityPolicyRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FSecurityPolicyDomain>& Self,
                const Request::FUpdateSecurityPolicyRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateSecurityPolicyRequestPtr Request
        );

        class GS2IDENTIFIER_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FSecurityPolicy>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSecurityPolicyDomain> Self;
            const Request::FGetSecurityPolicyRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSecurityPolicyDomain>& Self,
                const Request::FGetSecurityPolicyRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSecurityPolicyRequestPtr Request
        );

        class GS2IDENTIFIER_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FSecurityPolicyDomain> Self;
            const Request::FDeleteSecurityPolicyRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FSecurityPolicyDomain>& Self,
                const Request::FDeleteSecurityPolicyRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteSecurityPolicyRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> SecurityPolicyName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> SecurityPolicyName
        );

        class GS2IDENTIFIER_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FSecurityPolicy>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSecurityPolicyDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSecurityPolicyDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Identifier::Model::FSecurityPolicyPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSecurityPolicyDomain> FSecurityPolicyDomainPtr;
}
