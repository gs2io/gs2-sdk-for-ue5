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
#include "Account/Gs2Account.h"
#include "Account/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Account/Domain/Iterator/DescribeAccountsIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOversIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOversByUserIdIterator.h"
#include "Account/Domain/Iterator/DescribePlatformIdsIterator.h"
#include "Account/Domain/Iterator/DescribePlatformIdsByUserIdIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOverTypeModelsIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOverTypeModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Account::Domain
{
    class FGs2AccountDomain;
    typedef TSharedPtr<FGs2AccountDomain> FGs2AccountDomainPtr;
}

namespace Gs2::Account::Domain::Model
{
    class FNamespaceDomain;
    class FAccountDomain;
    class FAccountAccessTokenDomain;
    class FTakeOverDomain;
    class FTakeOverAccessTokenDomain;
    class FPlatformIdDomain;
    class FPlatformIdAccessTokenDomain;
    class FDataOwnerDomain;
    class FDataOwnerAccessTokenDomain;
    class FTakeOverTypeModelDomain;
    class FTakeOverTypeModelMasterDomain;
    class FCurrentModelMasterDomain;

    class GS2ACCOUNT_API FAccountAccessTokenDomain:
        public TSharedFromThis<FAccountAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Account::Domain::FGs2AccountDomainPtr Service;
        const Gs2::Account::FGs2AccountRestClientPtr Client;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::Account::Model::FBanStatus>>> BanStatuses;
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> AuthorizationUrl;
        TOptional<FString> NextPageToken;
        TSharedPtr<TArray<TSharedPtr<Gs2::Account::Model::FBanStatus>>> GetBanStatuses() const
        {
            return BanStatuses;
        }
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> GetAuthorizationUrl() const
        {
            return AuthorizationUrl;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FAccountAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Account::Domain::FGs2AccountDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAccountAccessTokenDomain(
            const FAccountAccessTokenDomain& From
        );

        class GS2ACCOUNT_API FGetAuthorizationUrlTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountAccessTokenDomain>,
            public TSharedFromThis<FGetAuthorizationUrlTask>
        {
            const TSharedPtr<FAccountAccessTokenDomain> Self;
            const Request::FGetAuthorizationUrlRequestPtr Request;
        public:
            explicit FGetAuthorizationUrlTask(
                const TSharedPtr<FAccountAccessTokenDomain>& Self,
                const Request::FGetAuthorizationUrlRequestPtr Request
            );

            FGetAuthorizationUrlTask(
                const FGetAuthorizationUrlTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountAccessTokenDomain>> Result
            ) override;
        };
        friend FGetAuthorizationUrlTask;

        TSharedPtr<FAsyncTask<FGetAuthorizationUrlTask>> GetAuthorizationUrl(
            Request::FGetAuthorizationUrlRequestPtr Request
        );

        Gs2::Account::Domain::Iterator::FDescribeTakeOversIteratorPtr TakeOvers(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeTakeOvers(
            TFunction<void()> Callback
        );

        void UnsubscribeTakeOvers(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain> TakeOver(
            const int32 Type
        );

        TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerAccessTokenDomain> DataOwner(
        );

        Gs2::Account::Domain::Iterator::FDescribePlatformIdsIteratorPtr PlatformIds(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePlatformIds(
            TFunction<void()> Callback
        );

        void UnsubscribePlatformIds(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain> PlatformId(
            const int32 Type,
            const FString UserIdentifier
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

        class GS2ACCOUNT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FAccount>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FAccountAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAccountAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FAccount>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Account::Model::FAccountPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FAccountAccessTokenDomain> FAccountAccessTokenDomainPtr;
}
