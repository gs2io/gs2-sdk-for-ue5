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

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Account/Gs2Account.h"

// Model
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"

// Iterator
#include "Account/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Account/Domain/Iterator/DescribeAccountsIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOversIterator.h"
#include "Account/Domain/Iterator/DescribeTakeOversByUserIdIterator.h"

// Notification

namespace Gs2::Account::Domain
{

    class GS2ACCOUNT_API FGs2AccountDomain:
        public TSharedFromThis<FGs2AccountDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Account::FGs2AccountRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2AccountDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2AccountDomain(
            const FGs2AccountDomain& From
        );

        class GS2ACCOUNT_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Account::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2AccountDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2AccountDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Account::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2AccountDomain> FGs2AccountDomainPtr;
}
