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

    class GS2IDENTIFIER_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Identifier::Domain::FGs2IdentifierDomainPtr Service;
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        public:
        TOptional<FString> ClientSecret;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetClientSecret() const
        {
            return ClientSecret;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> UserName;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
            const TOptional<FString> UserName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2IDENTIFIER_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FUserDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FUpdateUserRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FUpdateUserRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateUserRequestPtr Request
        );

        class GS2IDENTIFIER_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FUser>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FGetUserRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FGetUserRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FUser>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetUserRequestPtr Request
        );

        class GS2IDENTIFIER_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FUserDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDeleteUserRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FDeleteUserRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteUserRequestPtr Request
        );

        class GS2IDENTIFIER_API FCreateIdentifierTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Domain::Model::FIdentifierDomain>,
            public TSharedFromThis<FCreateIdentifierTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FCreateIdentifierRequestPtr Request;
        public:
            explicit FCreateIdentifierTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FCreateIdentifierRequestPtr Request
            );

            FCreateIdentifierTask(
                const FCreateIdentifierTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain>> Result
            ) override;
        };
        friend FCreateIdentifierTask;

        TSharedPtr<FAsyncTask<FCreateIdentifierTask>> CreateIdentifier(
            Request::FCreateIdentifierRequestPtr Request
        );

        Gs2::Identifier::Domain::Iterator::FDescribeIdentifiersIteratorPtr Identifiers(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeIdentifiers(
            TFunction<void()> Callback
        );

        void UnsubscribeIdentifiers(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Identifier::Domain::Iterator::FDescribeAttachedGuardsIteratorPtr AttachedGuards(
            const TOptional<FString> ClientId = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAttachedGuards(
            TFunction<void()> Callback
        );

        void UnsubscribeAttachedGuards(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Identifier::Domain::Model::FIdentifierDomain> Identifier(
            const FString ClientId
        );

        TSharedPtr<Gs2::Identifier::Domain::Model::FPasswordDomain> Password(
        );

        TSharedPtr<Gs2::Identifier::Domain::Model::FAttachSecurityPolicyDomain> AttachSecurityPolicy(
        );

        static FString CreateCacheParentKey(
            TOptional<FString> UserName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserName
        );

        class GS2IDENTIFIER_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Identifier::Model::FUser>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FUserDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FUserDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FUser>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Identifier::Model::FUserPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
