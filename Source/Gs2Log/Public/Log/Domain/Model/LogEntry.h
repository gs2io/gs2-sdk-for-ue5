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
    class FFacetDomain;

    class GS2LOG_API FLogEntryDomain:
        public TSharedFromThis<FLogEntryDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Log::Domain::FGs2LogDomainPtr Service;
        const Gs2::Log::FGs2LogRestClientPtr Client;

        public:
        TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FTrace>>> Parallels;
        TOptional<bool> ParallelTruncated;
        TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FTrace>>> GetParallels() const
        {
            return Parallels;
        }
        TOptional<bool> GetParallelTruncated() const
        {
            return ParallelTruncated;
        }
    private:

        FString ParentKey;

    public:

        FLogEntryDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Log::Domain::FGs2LogDomainPtr& Service
            // ReSharper disable once CppMemberInitializersOrder
        );

        FLogEntryDomain(
            const FLogEntryDomain& From
        );

        class GS2LOG_API FGetLogTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FLogEntryDomain>,
            public TSharedFromThis<FGetLogTask>
        {
            const TSharedPtr<FLogEntryDomain> Self;
            const Request::FGetLogRequestPtr Request;
        public:
            explicit FGetLogTask(
                const TSharedPtr<FLogEntryDomain>& Self,
                const Request::FGetLogRequestPtr Request
            );

            FGetLogTask(
                const FGetLogTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FLogEntryDomain>> Result
            ) override;
        };
        friend FGetLogTask;

        TSharedPtr<FAsyncTask<FGetLogTask>> GetLog(
            Request::FGetLogRequestPtr Request
        );

        class GS2LOG_API FFacetsTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Log::Domain::Model::FFacetDomain>>>,
            public TSharedFromThis<FFacetsTask>
        {
            const TSharedPtr<FLogEntryDomain> Self;
            const Request::FQueryFacetsRequestPtr Request;
        public:
            explicit FFacetsTask(
                const TSharedPtr<FLogEntryDomain>& Self,
                const Request::FQueryFacetsRequestPtr Request
            );

            FFacetsTask(
                const FFacetsTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Log::Domain::Model::FFacetDomain>>>> Result
            ) override;
        };
        friend FFacetsTask;

        TSharedPtr<FAsyncTask<FFacetsTask>> Facets(
            Request::FQueryFacetsRequestPtr Request
        );

        class GS2LOG_API FGetTraceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FLogEntryDomain>,
            public TSharedFromThis<FGetTraceTask>
        {
            const TSharedPtr<FLogEntryDomain> Self;
            const Request::FGetTraceRequestPtr Request;
        public:
            explicit FGetTraceTask(
                const TSharedPtr<FLogEntryDomain>& Self,
                const Request::FGetTraceRequestPtr Request
            );

            FGetTraceTask(
                const FGetTraceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FLogEntryDomain>> Result
            ) override;
        };
        friend FGetTraceTask;

        TSharedPtr<FAsyncTask<FGetTraceTask>> GetTrace(
            Request::FGetTraceRequestPtr Request
        );

        static FString CreateCacheParentKey(
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2LOG_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FLogEntry>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FLogEntryDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FLogEntryDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Model::FLogEntry>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Log::Model::FLogEntryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FLogEntryDomain> FLogEntryDomainPtr;
}
