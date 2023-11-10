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

    class GS2IDENTIFIER_API FPasswordDomain:
        public TSharedFromThis<FPasswordDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Identifier::Domain::FGs2IdentifierDomainPtr Service;
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        public:
        TOptional<FString> UserName;
    private:

        FString ParentKey;

    public:

        FPasswordDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
            const TOptional<FString> UserName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FPasswordDomain(
            const FPasswordDomain& From
        );

        class GS2IDENTIFIER_API FCreateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FPasswordDomain>,
            public TSharedFromThis<FCreateTask>
        {
            const TSharedPtr<FPasswordDomain> Self;
            const Request::FCreatePasswordRequestPtr Request;
        public:
            explicit FCreateTask(
                const TSharedPtr<FPasswordDomain>& Self,
                const Request::FCreatePasswordRequestPtr Request
            );

            FCreateTask(
                const FCreateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
            ) override;
        };
        friend FCreateTask;

        TSharedPtr<FAsyncTask<FCreateTask>> Create(
            Request::FCreatePasswordRequestPtr Request
        );

        class GS2IDENTIFIER_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FPassword>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FPasswordDomain> Self;
            const Request::FGetPasswordRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FPasswordDomain>& Self,
                const Request::FGetPasswordRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetPasswordRequestPtr Request
        );

        class GS2IDENTIFIER_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FPasswordDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FPasswordDomain> Self;
            const Request::FDeletePasswordRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FPasswordDomain>& Self,
                const Request::FDeletePasswordRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeletePasswordRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> UserName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2IDENTIFIER_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FPassword>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FPasswordDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FPasswordDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FPassword>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Identifier::Model::FPasswordPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FPasswordDomain> FPasswordDomainPtr;
}
