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
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Money2/Gs2Money2.h"

// Model
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/SubscriptionStatus.h"
#include "Money2/Domain/Model/SubscriptionStatusAccessToken.h"
#include "Money2/Domain/Model/StoreContentModel.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModel.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModelMaster.h"
#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/UnusedBalance.h"

// Iterator
#include "Money2/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsIterator.h"
#include "Money2/Domain/Iterator/DescribeWalletsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeEventsByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesIterator.h"
#include "Money2/Domain/Iterator/DescribeSubscriptionStatusesByUserIdIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelsIterator.h"
#include "Money2/Domain/Iterator/DescribeStoreSubscriptionContentModelMastersIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesByCurrencyIterator.h"
#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesIterator.h"
#include "Money2/Domain/Iterator/DescribeUnusedBalancesIterator.h"

// Notification
#include "Money2/Model/ChangeSubscriptionStatus.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Money2::Domain
{
    DECLARE_EVENT_OneParam(FGs2Money2Domain, FChangeSubscriptionStatusEvent, Gs2::Money2::Model::FChangeSubscriptionStatusPtr);

    class GS2MONEY2_API FGs2Money2Domain:
        public TSharedFromThis<FGs2Money2Domain>
    {
        FChangeSubscriptionStatusEvent ChangeSubscriptionStatusEvent;
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Money2::FGs2Money2RestClientPtr Client;

        public:
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
    private:

        FString ParentKey;

    public:

        FGs2Money2Domain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2Money2Domain(
            const FGs2Money2Domain& From
        );

        class GS2MONEY2_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        class GS2MONEY2_API FDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2Money2Domain>,
            public TSharedFromThis<FDumpUserDataTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FDumpUserDataTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FDumpUserDataByUserIdRequestPtr Request
            );

            FDumpUserDataTask(
                const FDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2Money2Domain>> Result
            ) override;
        };
        friend FDumpUserDataTask;

        TSharedPtr<FAsyncTask<FDumpUserDataTask>> DumpUserData(
            Request::FDumpUserDataByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FCheckDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2Money2Domain>,
            public TSharedFromThis<FCheckDumpUserDataTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckDumpUserDataTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FCheckDumpUserDataByUserIdRequestPtr Request
            );

            FCheckDumpUserDataTask(
                const FCheckDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2Money2Domain>> Result
            ) override;
        };
        friend FCheckDumpUserDataTask;

        TSharedPtr<FAsyncTask<FCheckDumpUserDataTask>> CheckDumpUserData(
            Request::FCheckDumpUserDataByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2Money2Domain>,
            public TSharedFromThis<FCleanUserDataTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCleanUserDataTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FCleanUserDataByUserIdRequestPtr Request
            );

            FCleanUserDataTask(
                const FCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2Money2Domain>> Result
            ) override;
        };
        friend FCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCleanUserDataTask>> CleanUserData(
            Request::FCleanUserDataByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FCheckCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2Money2Domain>,
            public TSharedFromThis<FCheckCleanUserDataTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckCleanUserDataTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FCheckCleanUserDataByUserIdRequestPtr Request
            );

            FCheckCleanUserDataTask(
                const FCheckCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2Money2Domain>> Result
            ) override;
        };
        friend FCheckCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCheckCleanUserDataTask>> CheckCleanUserData(
            Request::FCheckCleanUserDataByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FPrepareImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2Money2Domain>,
            public TSharedFromThis<FPrepareImportUserDataTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FPrepareImportUserDataTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FPrepareImportUserDataByUserIdRequestPtr Request
            );

            FPrepareImportUserDataTask(
                const FPrepareImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2Money2Domain>> Result
            ) override;
        };
        friend FPrepareImportUserDataTask;

        TSharedPtr<FAsyncTask<FPrepareImportUserDataTask>> PrepareImportUserData(
            Request::FPrepareImportUserDataByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2Money2Domain>,
            public TSharedFromThis<FImportUserDataTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FImportUserDataTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FImportUserDataByUserIdRequestPtr Request
            );

            FImportUserDataTask(
                const FImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2Money2Domain>> Result
            ) override;
        };
        friend FImportUserDataTask;

        TSharedPtr<FAsyncTask<FImportUserDataTask>> ImportUserData(
            Request::FImportUserDataByUserIdRequestPtr Request
        );

        class GS2MONEY2_API FCheckImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2Money2Domain>,
            public TSharedFromThis<FCheckImportUserDataTask>
        {
            const TSharedPtr<FGs2Money2Domain> Self;
            const Request::FCheckImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckImportUserDataTask(
                const TSharedPtr<FGs2Money2Domain>& Self,
                const Request::FCheckImportUserDataByUserIdRequestPtr Request
            );

            FCheckImportUserDataTask(
                const FCheckImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2Money2Domain>> Result
            ) override;
        };
        friend FCheckImportUserDataTask;

        TSharedPtr<FAsyncTask<FCheckImportUserDataTask>> CheckImportUserData(
            Request::FCheckImportUserDataByUserIdRequestPtr Request
        );

        Gs2::Money2::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Money2::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        );

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
        FChangeSubscriptionStatusEvent& OnChangeSubscriptionStatus();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2Money2Domain> FGs2Money2DomainPtr;
}
