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
 *
 * deny overwrite
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Log/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Log/Domain/Iterator/QueryAccessLogIterator.h"
#include "Log/Domain/Iterator/CountAccessLogIterator.h"
#include "Log/Domain/Iterator/QueryIssueStampSheetLogIterator.h"
#include "Log/Domain/Iterator/CountIssueStampSheetLogIterator.h"
#include "Log/Domain/Iterator/QueryExecuteStampSheetLogIterator.h"
#include "Log/Domain/Iterator/CountExecuteStampSheetLogIterator.h"
#include "Log/Domain/Iterator/QueryExecuteStampTaskLogIterator.h"
#include "Log/Domain/Iterator/CountExecuteStampTaskLogIterator.h"
#include "Log/Domain/Iterator/QueryInGameLogIterator.h"
#include "Log/Domain/Iterator/QueryAccessLogWithTelemetryIterator.h"
#include "Log/Domain/Iterator/DescribeInsightsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Log::Domain
{
    class FGs2LogDomain;
    typedef TSharedPtr<FGs2LogDomain> FGs2LogDomainPtr;
}

namespace Gs2::Log::Domain::Model
{
    class FNamespaceDomain;
    class FAccessLogDomain;
    class FIssueStampSheetLogDomain;
    class FExecuteStampSheetLogDomain;
    class FExecuteStampTaskLogDomain;
    class FInGameLogDomain;
    class FInGameLogAccessTokenDomain;
    class FAccessLogWithTelemetryDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FInsightDomain;

    class GS2LOG_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Log::Domain::FGs2LogDomainPtr Service;
        const Gs2::Log::FGs2LogRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> NextPageToken;
        TOptional<int64> TotalCount;
        TOptional<int64> ScanSize;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<int64> GetTotalCount() const
        {
            return TotalCount;
        }
        TOptional<int64> GetScanSize() const
        {
            return ScanSize;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Log::Domain::FGs2LogDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2LOG_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2LOG_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2LOG_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2LOG_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2LOG_API FCreateInsightTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FInsightDomain>,
            public TSharedFromThis<FCreateInsightTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateInsightRequestPtr Request;
        public:
            explicit FCreateInsightTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateInsightRequestPtr Request
            );

            FCreateInsightTask(
                const FCreateInsightTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FInsightDomain>> Result
            ) override;
        };
        friend FCreateInsightTask;

        TSharedPtr<FAsyncTask<FCreateInsightTask>> CreateInsight(
            Request::FCreateInsightRequestPtr Request
        );

        Gs2::Log::Domain::Iterator::FQueryAccessLogIteratorPtr AccessLog(
            const TOptional<FString> Service = TOptional<FString>(),
            const TOptional<FString> Method = TOptional<FString>(),
            const TOptional<FString> UserId = TOptional<FString>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAccessLog(
            TFunction<void()> Callback
        );

        void UnsubscribeAccessLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FCountAccessLogIteratorPtr CountAccessLog(
            const TOptional<bool> Service = TOptional<bool>(),
            const TOptional<bool> Method = TOptional<bool>(),
            const TOptional<bool> UserId = TOptional<bool>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCountAccessLog(
            TFunction<void()> Callback
        );

        void UnsubscribeCountAccessLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FQueryExecuteStampSheetLogIteratorPtr ExecuteStampSheetLog(
            const TOptional<FString> Service = TOptional<FString>(),
            const TOptional<FString> Method = TOptional<FString>(),
            const TOptional<FString> UserId = TOptional<FString>(),
            const TOptional<FString> Action = TOptional<FString>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeExecuteStampSheetLog(
            TFunction<void()> Callback
        );

        void UnsubscribeExecuteStampSheetLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FCountExecuteStampSheetLogIteratorPtr CountExecuteStampSheetLog(
            const TOptional<bool> Service = TOptional<bool>(),
            const TOptional<bool> Method = TOptional<bool>(),
            const TOptional<bool> UserId = TOptional<bool>(),
            const TOptional<bool> Action = TOptional<bool>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCountExecuteStampSheetLog(
            TFunction<void()> Callback
        );

        void UnsubscribeCountExecuteStampSheetLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FQueryExecuteStampTaskLogIteratorPtr ExecuteStampTaskLog(
            const TOptional<FString> Service = TOptional<FString>(),
            const TOptional<FString> Method = TOptional<FString>(),
            const TOptional<FString> UserId = TOptional<FString>(),
            const TOptional<FString> Action = TOptional<FString>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeExecuteStampTaskLog(
            TFunction<void()> Callback
        );

        void UnsubscribeExecuteStampTaskLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FCountExecuteStampTaskLogIteratorPtr CountExecuteStampTaskLog(
            const TOptional<bool> Service = TOptional<bool>(),
            const TOptional<bool> Method = TOptional<bool>(),
            const TOptional<bool> UserId = TOptional<bool>(),
            const TOptional<bool> Action = TOptional<bool>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCountExecuteStampTaskLog(
            TFunction<void()> Callback
        );

        void UnsubscribeCountExecuteStampTaskLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FQueryIssueStampSheetLogIteratorPtr IssueStampSheetLog(
            const TOptional<FString> Service = TOptional<FString>(),
            const TOptional<FString> Method = TOptional<FString>(),
            const TOptional<FString> UserId = TOptional<FString>(),
            const TOptional<FString> Action = TOptional<FString>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeIssueStampSheetLog(
            TFunction<void()> Callback
        );

        void UnsubscribeIssueStampSheetLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FCountIssueStampSheetLogIteratorPtr CountIssueStampSheetLog(
            const TOptional<bool> Service = TOptional<bool>(),
            const TOptional<bool> Method = TOptional<bool>(),
            const TOptional<bool> UserId = TOptional<bool>(),
            const TOptional<bool> Action = TOptional<bool>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCountIssueStampSheetLog(
            TFunction<void()> Callback
        );

        void UnsubscribeCountIssueStampSheetLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FDescribeInsightsIteratorPtr Insights(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeInsights(
            TFunction<void()> Callback
        );

        void UnsubscribeInsights(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Log::Domain::Model::FInsightDomain> Insight(
            const FString InsightName
        );

        Gs2::Log::Domain::Iterator::FQueryAccessLogWithTelemetryIteratorPtr AccessLogWithTelemetry(
            const TOptional<FString> UserId = TOptional<FString>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeAccessLogWithTelemetry(
            TFunction<void()> Callback
        );

        void UnsubscribeAccessLogWithTelemetry(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Log::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Log::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2LOG_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Log::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FQueryInGameLogIteratorPtr InGameLog(
            const TOptional<FString> UserId = TOptional<FString>(),
            const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags = nullptr,
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;
    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
