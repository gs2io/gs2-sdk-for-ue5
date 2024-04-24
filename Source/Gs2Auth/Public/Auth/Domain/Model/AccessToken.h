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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Auth::Domain
{
    class FGs2AuthDomain;
    typedef TSharedPtr<FGs2AuthDomain> FGs2AuthDomainPtr;
}

namespace Gs2::Auth::Domain::Model
{
    class FAccessTokenDomain;

    class GS2AUTH_API FAccessTokenDomain:
        public TSharedFromThis<FAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Auth::Domain::FGs2AuthDomainPtr Service;
        const Gs2::Auth::FGs2AuthRestClientPtr Client;

        public:
        TOptional<FString> Token;
        TOptional<FString> UserId;
        TOptional<int64> Expire;
        TOptional<FString> Status;
        TOptional<FString> GetToken() const
        {
            return Token;
        }
        TOptional<FString> GetUserId() const
        {
            return UserId;
        }
        TOptional<int64> GetExpire() const
        {
            return Expire;
        }
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
    private:

        FString ParentKey;

    public:

        FAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Auth::Domain::FGs2AuthDomainPtr& Service
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAccessTokenDomain(
            const FAccessTokenDomain& From
        );

        class GS2AUTH_API FLoginTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Auth::Domain::Model::FAccessTokenDomain>,
            public TSharedFromThis<FLoginTask>
        {
            const TSharedPtr<FAccessTokenDomain> Self;
            const Request::FLoginRequestPtr Request;
        public:
            explicit FLoginTask(
                const TSharedPtr<FAccessTokenDomain>& Self,
                const Request::FLoginRequestPtr Request
            );

            FLoginTask(
                const FLoginTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
            ) override;
        };
        friend FLoginTask;

        TSharedPtr<FAsyncTask<FLoginTask>> Login(
            Request::FLoginRequestPtr Request
        );

        class GS2AUTH_API FLoginBySignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Auth::Domain::Model::FAccessTokenDomain>,
            public TSharedFromThis<FLoginBySignatureTask>
        {
            const TSharedPtr<FAccessTokenDomain> Self;
            const Request::FLoginBySignatureRequestPtr Request;
        public:
            explicit FLoginBySignatureTask(
                const TSharedPtr<FAccessTokenDomain>& Self,
                const Request::FLoginBySignatureRequestPtr Request
            );

            FLoginBySignatureTask(
                const FLoginBySignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
            ) override;
        };
        friend FLoginBySignatureTask;

        TSharedPtr<FAsyncTask<FLoginBySignatureTask>> LoginBySignature(
            Request::FLoginBySignatureRequestPtr Request
        );

        class GS2AUTH_API FFederationTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Auth::Domain::Model::FAccessTokenDomain>,
            public TSharedFromThis<FFederationTask>
        {
            const TSharedPtr<FAccessTokenDomain> Self;
            const Request::FFederationRequestPtr Request;
        public:
            explicit FFederationTask(
                const TSharedPtr<FAccessTokenDomain>& Self,
                const Request::FFederationRequestPtr Request
            );

            FFederationTask(
                const FFederationTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
            ) override;
        };
        friend FFederationTask;

        TSharedPtr<FAsyncTask<FFederationTask>> Federation(
            Request::FFederationRequestPtr Request
        );

        class GS2AUTH_API FIssueTimeOffsetTokenTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Auth::Domain::Model::FAccessTokenDomain>,
            public TSharedFromThis<FIssueTimeOffsetTokenTask>
        {
            const TSharedPtr<FAccessTokenDomain> Self;
            const Request::FIssueTimeOffsetTokenByUserIdRequestPtr Request;
        public:
            explicit FIssueTimeOffsetTokenTask(
                const TSharedPtr<FAccessTokenDomain>& Self,
                const Request::FIssueTimeOffsetTokenByUserIdRequestPtr Request
            );

            FIssueTimeOffsetTokenTask(
                const FIssueTimeOffsetTokenTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
            ) override;
        };
        friend FIssueTimeOffsetTokenTask;

        TSharedPtr<FAsyncTask<FIssueTimeOffsetTokenTask>> IssueTimeOffsetToken(
            Request::FIssueTimeOffsetTokenByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2AUTH_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Auth::Model::FAccessToken>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Auth::Model::FAccessToken>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Auth::Model::FAccessTokenPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FAccessTokenDomain> FAccessTokenDomainPtr;
}
