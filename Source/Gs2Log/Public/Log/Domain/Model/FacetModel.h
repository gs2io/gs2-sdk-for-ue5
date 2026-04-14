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

    class GS2LOG_API FFacetModelDomain:
        public TSharedFromThis<FFacetModelDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Log::Domain::FGs2LogDomainPtr Service;
        const Gs2::Log::FGs2LogRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> Field;
    private:

        FString ParentKey;

    public:

        FFacetModelDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Log::Domain::FGs2LogDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> Field
            // ReSharper disable once CppMemberInitializersOrder
        );

        FFacetModelDomain(
            const FFacetModelDomain& From
        );

        class GS2LOG_API FCreateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FFacetModelDomain>,
            public TSharedFromThis<FCreateTask>
        {
            const TSharedPtr<FFacetModelDomain> Self;
            const Request::FCreateFacetModelRequestPtr Request;
        public:
            explicit FCreateTask(
                const TSharedPtr<FFacetModelDomain>& Self,
                const Request::FCreateFacetModelRequestPtr Request
            );

            FCreateTask(
                const FCreateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain>> Result
            ) override;
        };
        friend FCreateTask;

        TSharedPtr<FAsyncTask<FCreateTask>> Create(
            Request::FCreateFacetModelRequestPtr Request
        );

        class GS2LOG_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FFacetModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FFacetModelDomain> Self;
            const Request::FGetFacetModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FFacetModelDomain>& Self,
                const Request::FGetFacetModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Model::FFacetModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetFacetModelRequestPtr Request
        );

        class GS2LOG_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FFacetModelDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FFacetModelDomain> Self;
            const Request::FUpdateFacetModelRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FFacetModelDomain>& Self,
                const Request::FUpdateFacetModelRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateFacetModelRequestPtr Request
        );

        class GS2LOG_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FFacetModelDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FFacetModelDomain> Self;
            const Request::FDeleteFacetModelRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FFacetModelDomain>& Self,
                const Request::FDeleteFacetModelRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteFacetModelRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> Field,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> Field
        );

        class GS2LOG_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FFacetModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FFacetModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FFacetModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Model::FFacetModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Log::Model::FFacetModelPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FFacetModelDomain> FFacetModelDomainPtr;
}
