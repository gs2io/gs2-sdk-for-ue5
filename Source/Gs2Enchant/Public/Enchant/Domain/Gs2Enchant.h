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
#include "Enchant/Gs2Enchant.h"

// Model
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Domain/Model/BalanceParameterModelMaster.h"
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/CurrentParameterMaster.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/BalanceParameterStatus.h"
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"

// Iterator
#include "Enchant/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelsIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterModelMastersIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeBalanceParameterStatusesByUserIdIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesIterator.h"
#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesByUserIdIterator.h"

// Notification

namespace Gs2::Enchant::Domain
{

    class GS2ENCHANT_API FGs2EnchantDomain:
        public TSharedFromThis<FGs2EnchantDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Enchant::FGs2EnchantRestClientPtr Client;

        public:
        TOptional<FString> Url;
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
    private:

        FString ParentKey;

    public:

        FGs2EnchantDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2EnchantDomain(
            const FGs2EnchantDomain& From
        );

        class GS2ENCHANT_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Enchant::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2EnchantDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2EnchantDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        class GS2ENCHANT_API FDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2EnchantDomain>,
            public TSharedFromThis<FDumpUserDataTask>
        {
            const TSharedPtr<FGs2EnchantDomain> Self;
            const Request::FDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FDumpUserDataTask(
                const TSharedPtr<FGs2EnchantDomain> Self,
                const Request::FDumpUserDataByUserIdRequestPtr Request
            );

            FDumpUserDataTask(
                const FDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2EnchantDomain>> Result
            ) override;
        };
        friend FDumpUserDataTask;

        TSharedPtr<FAsyncTask<FDumpUserDataTask>> DumpUserData(
            Request::FDumpUserDataByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FCheckDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2EnchantDomain>,
            public TSharedFromThis<FCheckDumpUserDataTask>
        {
            const TSharedPtr<FGs2EnchantDomain> Self;
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckDumpUserDataTask(
                const TSharedPtr<FGs2EnchantDomain> Self,
                const Request::FCheckDumpUserDataByUserIdRequestPtr Request
            );

            FCheckDumpUserDataTask(
                const FCheckDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2EnchantDomain>> Result
            ) override;
        };
        friend FCheckDumpUserDataTask;

        TSharedPtr<FAsyncTask<FCheckDumpUserDataTask>> CheckDumpUserData(
            Request::FCheckDumpUserDataByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2EnchantDomain>,
            public TSharedFromThis<FCleanUserDataTask>
        {
            const TSharedPtr<FGs2EnchantDomain> Self;
            const Request::FCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCleanUserDataTask(
                const TSharedPtr<FGs2EnchantDomain> Self,
                const Request::FCleanUserDataByUserIdRequestPtr Request
            );

            FCleanUserDataTask(
                const FCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2EnchantDomain>> Result
            ) override;
        };
        friend FCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCleanUserDataTask>> CleanUserData(
            Request::FCleanUserDataByUserIdRequestPtr Request
        );

        class GS2ENCHANT_API FCheckCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2EnchantDomain>,
            public TSharedFromThis<FCheckCleanUserDataTask>
        {
            const TSharedPtr<FGs2EnchantDomain> Self;
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckCleanUserDataTask(
                const TSharedPtr<FGs2EnchantDomain> Self,
                const Request::FCheckCleanUserDataByUserIdRequestPtr Request
            );

            FCheckCleanUserDataTask(
                const FCheckCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2EnchantDomain>> Result
            ) override;
        };
        friend FCheckCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCheckCleanUserDataTask>> CheckCleanUserData(
            Request::FCheckCleanUserDataByUserIdRequestPtr Request
        );

        Gs2::Enchant::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Enchant::Domain::Model::FNamespaceDomain> Namespace(
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
    typedef TSharedPtr<FGs2EnchantDomain> FGs2EnchantDomainPtr;
}
