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

    class GS2ACCOUNT_API FAccountDomain:
        public TSharedFromThis<FAccountDomain>
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
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FAccountDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Account::Domain::FGs2AccountDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FAccountDomain(
            const FAccountDomain& From
        );

        class GS2ACCOUNT_API FUpdateTimeOffsetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FUpdateTimeOffsetTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FUpdateTimeOffsetRequestPtr Request;
        public:
            explicit FUpdateTimeOffsetTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FUpdateTimeOffsetRequestPtr Request
            );

            FUpdateTimeOffsetTask(
                const FUpdateTimeOffsetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FUpdateTimeOffsetTask;

        TSharedPtr<FAsyncTask<FUpdateTimeOffsetTask>> UpdateTimeOffset(
            Request::FUpdateTimeOffsetRequestPtr Request
        );

        class GS2ACCOUNT_API FUpdateBannedTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FUpdateBannedTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FUpdateBannedRequestPtr Request;
        public:
            explicit FUpdateBannedTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FUpdateBannedRequestPtr Request
            );

            FUpdateBannedTask(
                const FUpdateBannedTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FUpdateBannedTask;

        TSharedPtr<FAsyncTask<FUpdateBannedTask>> UpdateBanned(
            Request::FUpdateBannedRequestPtr Request
        );

        class GS2ACCOUNT_API FAddBanTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FAddBanTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FAddBanRequestPtr Request;
        public:
            explicit FAddBanTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FAddBanRequestPtr Request
            );

            FAddBanTask(
                const FAddBanTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FAddBanTask;

        TSharedPtr<FAsyncTask<FAddBanTask>> AddBan(
            Request::FAddBanRequestPtr Request
        );

        class GS2ACCOUNT_API FRemoveBanTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FRemoveBanTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FRemoveBanRequestPtr Request;
        public:
            explicit FRemoveBanTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FRemoveBanRequestPtr Request
            );

            FRemoveBanTask(
                const FRemoveBanTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FRemoveBanTask;

        TSharedPtr<FAsyncTask<FRemoveBanTask>> RemoveBan(
            Request::FRemoveBanRequestPtr Request
        );

        class GS2ACCOUNT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FAccount>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FGetAccountRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FGetAccountRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FAccount>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetAccountRequestPtr Request
        );

        class GS2ACCOUNT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FDeleteAccountRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FDeleteAccountRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteAccountRequestPtr Request
        );

        class GS2ACCOUNT_API FAuthenticationTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FAccountDomain>,
            public TSharedFromThis<FAuthenticationTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FAuthenticationRequestPtr Request;
        public:
            explicit FAuthenticationTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FAuthenticationRequestPtr Request
            );

            FAuthenticationTask(
                const FAuthenticationTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
            ) override;
        };
        friend FAuthenticationTask;

        TSharedPtr<FAsyncTask<FAuthenticationTask>> Authentication(
            Request::FAuthenticationRequestPtr Request
        );

        class GS2ACCOUNT_API FCreateTakeOverOpenIdConnectAndTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverDomain>,
            public TSharedFromThis<FCreateTakeOverOpenIdConnectAndTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FCreateTakeOverOpenIdConnectAndByUserIdRequestPtr Request;
        public:
            explicit FCreateTakeOverOpenIdConnectAndTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FCreateTakeOverOpenIdConnectAndByUserIdRequestPtr Request
            );

            FCreateTakeOverOpenIdConnectAndTask(
                const FCreateTakeOverOpenIdConnectAndTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
            ) override;
        };
        friend FCreateTakeOverOpenIdConnectAndTask;

        TSharedPtr<FAsyncTask<FCreateTakeOverOpenIdConnectAndTask>> CreateTakeOverOpenIdConnectAnd(
            Request::FCreateTakeOverOpenIdConnectAndByUserIdRequestPtr Request
        );

        class GS2ACCOUNT_API FDeleteTakeOverByUserIdentifierTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverDomain>,
            public TSharedFromThis<FDeleteTakeOverByUserIdentifierTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FDeleteTakeOverByUserIdentifierRequestPtr Request;
        public:
            explicit FDeleteTakeOverByUserIdentifierTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
            );

            FDeleteTakeOverByUserIdentifierTask(
                const FDeleteTakeOverByUserIdentifierTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
            ) override;
        };
        friend FDeleteTakeOverByUserIdentifierTask;

        TSharedPtr<FAsyncTask<FDeleteTakeOverByUserIdentifierTask>> DeleteTakeOverByUserIdentifier(
            Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
        );

        class GS2ACCOUNT_API FDeleteTakeOverTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FTakeOverDomain>,
            public TSharedFromThis<FDeleteTakeOverTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FDeleteTakeOverByUserIdRequestPtr Request;
        public:
            explicit FDeleteTakeOverTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FDeleteTakeOverByUserIdRequestPtr Request
            );

            FDeleteTakeOverTask(
                const FDeleteTakeOverTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
            ) override;
        };
        friend FDeleteTakeOverTask;

        TSharedPtr<FAsyncTask<FDeleteTakeOverTask>> DeleteTakeOver(
            Request::FDeleteTakeOverByUserIdRequestPtr Request
        );

        class GS2ACCOUNT_API FDeleteDataOwnerTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FDataOwnerDomain>,
            public TSharedFromThis<FDeleteDataOwnerTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FDeleteDataOwnerByUserIdRequestPtr Request;
        public:
            explicit FDeleteDataOwnerTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FDeleteDataOwnerByUserIdRequestPtr Request
            );

            FDeleteDataOwnerTask(
                const FDeleteDataOwnerTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerDomain>> Result
            ) override;
        };
        friend FDeleteDataOwnerTask;

        TSharedPtr<FAsyncTask<FDeleteDataOwnerTask>> DeleteDataOwner(
            Request::FDeleteDataOwnerByUserIdRequestPtr Request
        );

        class GS2ACCOUNT_API FDeletePlatformIdTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FPlatformIdDomain>,
            public TSharedFromThis<FDeletePlatformIdTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FDeletePlatformIdByUserIdRequestPtr Request;
        public:
            explicit FDeletePlatformIdTask(
                const TSharedPtr<FAccountDomain>& Self,
                const Request::FDeletePlatformIdByUserIdRequestPtr Request
            );

            FDeletePlatformIdTask(
                const FDeletePlatformIdTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdDomain>> Result
            ) override;
        };
        friend FDeletePlatformIdTask;

        TSharedPtr<FAsyncTask<FDeletePlatformIdTask>> DeletePlatformId(
            Request::FDeletePlatformIdByUserIdRequestPtr Request
        );

        Gs2::Account::Domain::Iterator::FDescribeTakeOversByUserIdIteratorPtr TakeOvers(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeTakeOvers(
            TFunction<void()> Callback
        );

        void UnsubscribeTakeOvers(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain> TakeOver(
            const int32 Type
        );

        TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerDomain> DataOwner(
        );

        Gs2::Account::Domain::Iterator::FDescribePlatformIdsByUserIdIteratorPtr PlatformIds(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribePlatformIds(
            TFunction<void()> Callback
        );

        void UnsubscribePlatformIds(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdDomain> PlatformId(
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
            const TSharedPtr<FAccountDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FAccountDomain> Self
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

    typedef TSharedPtr<FAccountDomain> FAccountDomainPtr;
}
