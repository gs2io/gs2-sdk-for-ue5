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
#include "Ranking/Gs2Ranking.h"

// Model
#include "Ranking/Domain/Model/Namespace.h"
#include "Ranking/Domain/Model/CategoryModel.h"
#include "Ranking/Domain/Model/CategoryModelMaster.h"
#include "Ranking/Domain/Model/Score.h"
#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Domain/Model/Ranking.h"
#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Domain/Model/CurrentRankingMaster.h"
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Domain/Model/RankingCategoryAccessToken.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"

// Iterator
#include "Ranking/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Ranking/Domain/Iterator/DescribeCategoryModelsIterator.h"
#include "Ranking/Domain/Iterator/DescribeCategoryModelMastersIterator.h"
#include "Ranking/Domain/Iterator/DescribeScoresIterator.h"
#include "Ranking/Domain/Iterator/DescribeScoresByUserIdIterator.h"
#include "Ranking/Domain/Iterator/DescribeRankingsIterator.h"
#include "Ranking/Domain/Iterator/DescribeRankingsByUserIdIterator.h"
#include "Ranking/Domain/Iterator/DescribeNearRankingsIterator.h"
#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameIterator.h"
#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameAndUserIdIterator.h"

// Notification

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Ranking::Domain
{

    class GS2RANKING_API FGs2RankingDomain:
        public TSharedFromThis<FGs2RankingDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Ranking::FGs2RankingRestClientPtr Client;

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

        FGs2RankingDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2RankingDomain(
            const FGs2RankingDomain& From
        );

        class GS2RANKING_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Ranking::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        class GS2RANKING_API FDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2RankingDomain>,
            public TSharedFromThis<FDumpUserDataTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FDumpUserDataTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FDumpUserDataByUserIdRequestPtr Request
            );

            FDumpUserDataTask(
                const FDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2RankingDomain>> Result
            ) override;
        };
        friend FDumpUserDataTask;

        TSharedPtr<FAsyncTask<FDumpUserDataTask>> DumpUserData(
            Request::FDumpUserDataByUserIdRequestPtr Request
        );

        class GS2RANKING_API FCheckDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2RankingDomain>,
            public TSharedFromThis<FCheckDumpUserDataTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckDumpUserDataTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FCheckDumpUserDataByUserIdRequestPtr Request
            );

            FCheckDumpUserDataTask(
                const FCheckDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2RankingDomain>> Result
            ) override;
        };
        friend FCheckDumpUserDataTask;

        TSharedPtr<FAsyncTask<FCheckDumpUserDataTask>> CheckDumpUserData(
            Request::FCheckDumpUserDataByUserIdRequestPtr Request
        );

        class GS2RANKING_API FCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2RankingDomain>,
            public TSharedFromThis<FCleanUserDataTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCleanUserDataTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FCleanUserDataByUserIdRequestPtr Request
            );

            FCleanUserDataTask(
                const FCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2RankingDomain>> Result
            ) override;
        };
        friend FCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCleanUserDataTask>> CleanUserData(
            Request::FCleanUserDataByUserIdRequestPtr Request
        );

        class GS2RANKING_API FCheckCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2RankingDomain>,
            public TSharedFromThis<FCheckCleanUserDataTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckCleanUserDataTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FCheckCleanUserDataByUserIdRequestPtr Request
            );

            FCheckCleanUserDataTask(
                const FCheckCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2RankingDomain>> Result
            ) override;
        };
        friend FCheckCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCheckCleanUserDataTask>> CheckCleanUserData(
            Request::FCheckCleanUserDataByUserIdRequestPtr Request
        );

        class GS2RANKING_API FPrepareImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2RankingDomain>,
            public TSharedFromThis<FPrepareImportUserDataTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FPrepareImportUserDataTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FPrepareImportUserDataByUserIdRequestPtr Request
            );

            FPrepareImportUserDataTask(
                const FPrepareImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2RankingDomain>> Result
            ) override;
        };
        friend FPrepareImportUserDataTask;

        TSharedPtr<FAsyncTask<FPrepareImportUserDataTask>> PrepareImportUserData(
            Request::FPrepareImportUserDataByUserIdRequestPtr Request
        );

        class GS2RANKING_API FImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2RankingDomain>,
            public TSharedFromThis<FImportUserDataTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FImportUserDataTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FImportUserDataByUserIdRequestPtr Request
            );

            FImportUserDataTask(
                const FImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2RankingDomain>> Result
            ) override;
        };
        friend FImportUserDataTask;

        TSharedPtr<FAsyncTask<FImportUserDataTask>> ImportUserData(
            Request::FImportUserDataByUserIdRequestPtr Request
        );

        class GS2RANKING_API FCheckImportUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2RankingDomain>,
            public TSharedFromThis<FCheckImportUserDataTask>
        {
            const TSharedPtr<FGs2RankingDomain> Self;
            const Request::FCheckImportUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckImportUserDataTask(
                const TSharedPtr<FGs2RankingDomain>& Self,
                const Request::FCheckImportUserDataByUserIdRequestPtr Request
            );

            FCheckImportUserDataTask(
                const FCheckImportUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2RankingDomain>> Result
            ) override;
        };
        friend FCheckImportUserDataTask;

        TSharedPtr<FAsyncTask<FCheckImportUserDataTask>> CheckImportUserData(
            Request::FCheckImportUserDataByUserIdRequestPtr Request
        );

        Gs2::Ranking::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Ranking::Domain::Model::FNamespaceDomain> Namespace(
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

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2RankingDomain> FGs2RankingDomainPtr;
}
