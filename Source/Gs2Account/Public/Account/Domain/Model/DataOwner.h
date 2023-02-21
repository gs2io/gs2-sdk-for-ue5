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

    class GS2ACCOUNT_API FDataOwnerDomain:
        public TSharedFromThis<FDataOwnerDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Account::FGs2AccountRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> DataOwnerName;
    private:

        FString ParentKey;

    public:

        FDataOwnerDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDataOwnerDomain(
            const FDataOwnerDomain& From
        );

        class GS2ACCOUNT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FDataOwner>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FDataOwnerDomain> Self;
            const Request::FGetDataOwnerByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FDataOwnerDomain> Self,
                const Request::FGetDataOwnerByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FDataOwner>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetDataOwnerByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2ACCOUNT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Model::FDataOwner>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FDataOwnerDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FDataOwnerDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Model::FDataOwner>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FDataOwnerDomain> FDataOwnerDomainPtr;
}
