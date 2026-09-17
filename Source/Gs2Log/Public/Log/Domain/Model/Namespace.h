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
#include "Log/Domain/Iterator/DescribeFacetModelsIterator.h"
#include "Log/Domain/Iterator/DescribeDashboardsIterator.h"
#include "Log/Domain/Iterator/QueryLogIterator.h"
#include "Log/Domain/Iterator/QueryTimeseriesIterator.h"
#include "Log/Domain/Iterator/DescribeMetricsIterator.h"
#include "Log/Domain/Iterator/DescribeLabelValuesIterator.h"

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
    class FFacetModelDomain;
    class FDashboardDomain;
    class FLogEntryDomain;
    class FMetricModelDomain;
    class FTimeseriesPointDomain;
    typedef TSharedPtr<FTimeseriesPointDomain> FTimeseriesPointDomainPtr;

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



        class GS2LOG_API FCreateDashboardTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FDashboardDomain>,
            public TSharedFromThis<FCreateDashboardTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateDashboardRequestPtr Request;
        public:
            explicit FCreateDashboardTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateDashboardRequestPtr Request
            );

            FCreateDashboardTask(
                const FCreateDashboardTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FDashboardDomain>> Result
            ) override;
        };
        friend FCreateDashboardTask;

        TSharedPtr<FAsyncTask<FCreateDashboardTask>> CreateDashboard(
            Request::FCreateDashboardRequestPtr Request
        );



        class GS2LOG_API FMetricsTimeseriesTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Log::Domain::Model::FTimeseriesPointDomain>>>,
            public TSharedFromThis<FMetricsTimeseriesTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FQueryMetricsTimeseriesRequestPtr Request;
        public:
            explicit FMetricsTimeseriesTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FQueryMetricsTimeseriesRequestPtr Request
            );

            FMetricsTimeseriesTask(
                const FMetricsTimeseriesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Log::Domain::Model::FTimeseriesPointDomain>>>> Result
            ) override;
        };
        friend FMetricsTimeseriesTask;

        TSharedPtr<FAsyncTask<FMetricsTimeseriesTask>> MetricsTimeseries(
            Request::FQueryMetricsTimeseriesRequestPtr Request
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

        class FCollectAccessLogTask;

        Gs2::Core::Domain::CallbackID SubscribeAccessLog(
            TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateAccessLog(const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeAccessLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeAccessLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> Callback;
        const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeAccessLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeAccessLogWithInitialCallTask(const FSubscribeAccessLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeAccessLogWithInitialCallTask>> SubscribeAccessLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FAccessLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        class FCollectCountAccessLogTask;

        Gs2::Core::Domain::CallbackID SubscribeCountAccessLog(
            TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateCountAccessLog(const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeCountAccessLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeCountAccessLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> Callback;
        const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeCountAccessLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeCountAccessLogWithInitialCallTask(const FSubscribeCountAccessLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeCountAccessLogWithInitialCallTask>> SubscribeCountAccessLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FAccessLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        class FCollectExecuteStampSheetLogTask;

        Gs2::Core::Domain::CallbackID SubscribeExecuteStampSheetLog(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateExecuteStampSheetLog(const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeExecuteStampSheetLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeExecuteStampSheetLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> Callback;
        const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<FString> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeExecuteStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeExecuteStampSheetLogWithInitialCallTask(const FSubscribeExecuteStampSheetLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeExecuteStampSheetLogWithInitialCallTask>> SubscribeExecuteStampSheetLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        class FCollectCountExecuteStampSheetLogTask;

        Gs2::Core::Domain::CallbackID SubscribeCountExecuteStampSheetLog(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateCountExecuteStampSheetLog(const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeCountExecuteStampSheetLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeCountExecuteStampSheetLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> Callback;
        const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<bool> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeCountExecuteStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeCountExecuteStampSheetLogWithInitialCallTask(const FSubscribeCountExecuteStampSheetLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeCountExecuteStampSheetLogWithInitialCallTask>> SubscribeCountExecuteStampSheetLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        class FCollectExecuteStampTaskLogTask;

        Gs2::Core::Domain::CallbackID SubscribeExecuteStampTaskLog(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateExecuteStampTaskLog(const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeExecuteStampTaskLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeExecuteStampTaskLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> Callback;
        const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<FString> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeExecuteStampTaskLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeExecuteStampTaskLogWithInitialCallTask(const FSubscribeExecuteStampTaskLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeExecuteStampTaskLogWithInitialCallTask>> SubscribeExecuteStampTaskLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        class FCollectCountExecuteStampTaskLogTask;

        Gs2::Core::Domain::CallbackID SubscribeCountExecuteStampTaskLog(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateCountExecuteStampTaskLog(const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeCountExecuteStampTaskLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeCountExecuteStampTaskLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> Callback;
        const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<bool> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeCountExecuteStampTaskLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeCountExecuteStampTaskLogWithInitialCallTask(const FSubscribeCountExecuteStampTaskLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeCountExecuteStampTaskLogWithInitialCallTask>> SubscribeCountExecuteStampTaskLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        class FCollectIssueStampSheetLogTask;

        Gs2::Core::Domain::CallbackID SubscribeIssueStampSheetLog(
            TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateIssueStampSheetLog(const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeIssueStampSheetLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeIssueStampSheetLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> Callback;
        const TOptional<FString> QueryService;const TOptional<FString> QueryMethod;const TOptional<FString> QueryUserId;const TOptional<FString> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeIssueStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> Callback,const TOptional<FString> Service,const TOptional<FString> Method,const TOptional<FString> UserId,const TOptional<FString> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeIssueStampSheetLogWithInitialCallTask(const FSubscribeIssueStampSheetLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeIssueStampSheetLogWithInitialCallTask>> SubscribeIssueStampSheetLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>)> Callback,const TOptional<FString> Service = TOptional<FString>(),const TOptional<FString> Method = TOptional<FString>(),const TOptional<FString> UserId = TOptional<FString>(),const TOptional<FString> Action = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        class FCollectCountIssueStampSheetLogTask;

        Gs2::Core::Domain::CallbackID SubscribeCountIssueStampSheetLog(
            TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateCountIssueStampSheetLog(const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeCountIssueStampSheetLogWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeCountIssueStampSheetLogWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> Callback;
        const TOptional<bool> QueryService;const TOptional<bool> QueryMethod;const TOptional<bool> QueryUserId;const TOptional<bool> QueryAction;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeCountIssueStampSheetLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service,const TOptional<bool> Method,const TOptional<bool> UserId,const TOptional<bool> Action,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeCountIssueStampSheetLogWithInitialCallTask(const FSubscribeCountIssueStampSheetLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeCountIssueStampSheetLogWithInitialCallTask>> SubscribeCountIssueStampSheetLogWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FIssueStampSheetLogCountPtr>)> Callback,const TOptional<bool> Service = TOptional<bool>(),const TOptional<bool> Method = TOptional<bool>(),const TOptional<bool> UserId = TOptional<bool>(),const TOptional<bool> Action = TOptional<bool>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );
        void UnsubscribeCountIssueStampSheetLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Log::Domain::Iterator::FDescribeInsightsIteratorPtr Insights(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeInsights(
            TFunction<void()> Callback
        );

        class FCollectInsightsTask;

        Gs2::Core::Domain::CallbackID SubscribeInsights(
            TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> Callback
        );

        void InvalidateInsights();

        class GS2LOG_API FSubscribeInsightsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeInsightsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> Callback;

        public:
            FSubscribeInsightsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> Callback);
            FSubscribeInsightsWithInitialCallTask(const FSubscribeInsightsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeInsightsWithInitialCallTask>> SubscribeInsightsWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FInsightPtr>)> Callback
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

        class FCollectAccessLogWithTelemetryTask;

        Gs2::Core::Domain::CallbackID SubscribeAccessLogWithTelemetry(
            TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> Callback,const TOptional<FString> UserId = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateAccessLogWithTelemetry(const TOptional<FString> UserId = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2LOG_API FSubscribeAccessLogWithTelemetryWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeAccessLogWithTelemetryWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> Callback;
        const TOptional<FString> QueryUserId;const TOptional<int64> QueryBegin;const TOptional<int64> QueryEnd;const TOptional<bool> QueryLongTerm;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeAccessLogWithTelemetryWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> Callback,const TOptional<FString> UserId,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm,const TOptional<FString> TimeOffsetToken);
            FSubscribeAccessLogWithTelemetryWithInitialCallTask(const FSubscribeAccessLogWithTelemetryWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeAccessLogWithTelemetryWithInitialCallTask>> SubscribeAccessLogWithTelemetryWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FAccessLogWithTelemetryPtr>)> Callback,const TOptional<FString> UserId = TOptional<FString>(),const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
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

        Gs2::Log::Domain::Iterator::FDescribeFacetModelsIteratorPtr FacetModels(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeFacetModels(
            TFunction<void()> Callback
        );

        class FCollectFacetModelsTask;

        Gs2::Core::Domain::CallbackID SubscribeFacetModels(
            TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateFacetModels(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2LOG_API FSubscribeFacetModelsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeFacetModelsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeFacetModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeFacetModelsWithInitialCallTask(const FSubscribeFacetModelsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeFacetModelsWithInitialCallTask>> SubscribeFacetModelsWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FFacetModelPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeFacetModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain> FacetModel(
            const FString Field
        );

        Gs2::Log::Domain::Iterator::FDescribeDashboardsIteratorPtr Dashboards(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDashboards(
            TFunction<void()> Callback
        );

        class FCollectDashboardsTask;

        Gs2::Core::Domain::CallbackID SubscribeDashboards(
            TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateDashboards(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2LOG_API FSubscribeDashboardsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeDashboardsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeDashboardsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeDashboardsWithInitialCallTask(const FSubscribeDashboardsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeDashboardsWithInitialCallTask>> SubscribeDashboardsWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FDashboardPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeDashboards(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Log::Domain::Model::FDashboardDomain> Dashboard(
            const FString DashboardName
        );

        Gs2::Log::Domain::Iterator::FDescribeMetricsIteratorPtr Metrics(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMetrics(
            TFunction<void()> Callback
        );

        class FCollectMetricsTask;

        Gs2::Core::Domain::CallbackID SubscribeMetrics(
            TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateMetrics(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2LOG_API FSubscribeMetricsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeMetricsWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeMetricsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeMetricsWithInitialCallTask(const FSubscribeMetricsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeMetricsWithInitialCallTask>> SubscribeMetricsWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FMetricModelPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeMetrics(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Log::Domain::Model::FMetricModelDomain> MetricModel(
            const FString Name
        );

        Gs2::Log::Domain::Iterator::FDescribeLabelValuesIteratorPtr LabelValues(
            const FString MetricName,
            const TOptional<FString> LabelNamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLabelValues(
            TFunction<void()> Callback
        );

        class FCollectLabelValuesTask;

        Gs2::Core::Domain::CallbackID SubscribeLabelValues(
            TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> Callback,const FString MetricName,const TOptional<FString> LabelNamePrefix = TOptional<FString>()
        );

        void InvalidateLabelValues(const FString MetricName,const TOptional<FString> LabelNamePrefix = TOptional<FString>());

        class GS2LOG_API FSubscribeLabelValuesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeLabelValuesWithInitialCallTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> Callback;
        const FString QueryMetricName;const TOptional<FString> QueryLabelNamePrefix;
        public:
            FSubscribeLabelValuesWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> Callback,const FString MetricName,const TOptional<FString> LabelNamePrefix);
            FSubscribeLabelValuesWithInitialCallTask(const FSubscribeLabelValuesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeLabelValuesWithInitialCallTask>> SubscribeLabelValuesWithInitialCall(
            TFunction<void(TArray<Gs2::Log::Model::FLabelPtr>)> Callback,const FString MetricName,const TOptional<FString> LabelNamePrefix = TOptional<FString>()
        );
        void UnsubscribeLabelValues(
            Gs2::Core::Domain::CallbackID CallbackID
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

        Gs2::Core::Domain::CallbackID SubscribeInGameLog(TFunction<void()> Callback);
        class FCollectInGameLogTask;
        Gs2::Core::Domain::CallbackID SubscribeInGameLog(TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> Callback);
        class GS2LOG_API FSubscribeInGameLogWithInitialCallTask final : public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>, public TSharedFromThis<FSubscribeInGameLogWithInitialCallTask>
        { const TSharedPtr<FNamespaceDomain> Self; const TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> Callback; const TOptional<FString> QueryUserId; const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> QueryTags; const TOptional<int64> QueryBegin; const TOptional<int64> QueryEnd; const TOptional<bool> QueryLongTerm; public:
            FSubscribeInGameLogWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self,TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> Callback,const TOptional<FString> UserId,const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags,const TOptional<int64> Begin,const TOptional<int64> End,const TOptional<bool> LongTerm);
            FSubscribeInGameLogWithInitialCallTask(const FSubscribeInGameLogWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override; };
        TSharedPtr<FAsyncTask<FSubscribeInGameLogWithInitialCallTask>> SubscribeInGameLogWithInitialCall(TFunction<void(TArray<Gs2::Log::Model::FInGameLogPtr>)> Callback,const TOptional<FString> UserId = TOptional<FString>(),const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags = nullptr,const TOptional<int64> Begin = TOptional<int64>(),const TOptional<int64> End = TOptional<int64>(),const TOptional<bool> LongTerm = TOptional<bool>());
        void UnsubscribeInGameLog(Gs2::Core::Domain::CallbackID CallbackID);
    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
