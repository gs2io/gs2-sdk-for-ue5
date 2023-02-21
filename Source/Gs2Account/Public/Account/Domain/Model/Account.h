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

namespace Gs2::Account::Domain::Model
{
    class FNamespaceDomain;
    class FAccountDomain;
    class FAccountAccessTokenDomain;
    class FTakeOverDomain;
    class FTakeOverAccessTokenDomain;
    class FDataOwnerDomain;
    class FDataOwnerAccessTokenDomain;

    class GS2ACCOUNT_API FAccountDomain:
        public TSharedFromThis<FAccountDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Account::FGs2AccountRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
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
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
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
                const TSharedPtr<FAccountDomain> Self,
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
                const TSharedPtr<FAccountDomain> Self,
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

        class GS2ACCOUNT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FAccount>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FGetAccountRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FAccountDomain> Self,
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
                const TSharedPtr<FAccountDomain> Self,
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
                const TSharedPtr<FAccountDomain> Self,
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

        class GS2ACCOUNT_API FDeleteDataOwnerTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FDataOwnerDomain>,
            public TSharedFromThis<FDeleteDataOwnerTask>
        {
            const TSharedPtr<FAccountDomain> Self;
            const Request::FDeleteDataOwnerByUserIdRequestPtr Request;
        public:
            explicit FDeleteDataOwnerTask(
                const TSharedPtr<FAccountDomain> Self,
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

        Gs2::Account::Domain::Iterator::FDescribeTakeOversByUserIdIteratorPtr TakeOvers(
        ) const;

        TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain> TakeOver(
            const int32 Type
        ) const;

        TSharedPtr<Gs2::Account::Domain::Model::FDataOwnerDomain> DataOwner(
        ) const;

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

    };

    typedef TSharedPtr<FAccountDomain> FAccountDomainPtr;
}
