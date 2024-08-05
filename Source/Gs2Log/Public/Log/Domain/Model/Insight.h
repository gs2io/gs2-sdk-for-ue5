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

    class GS2LOG_API FInsightDomain:
        public TSharedFromThis<FInsightDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Log::Domain::FGs2LogDomainPtr Service;
        const Gs2::Log::FGs2LogRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> InsightName;
    private:

        FString ParentKey;

    public:

        FInsightDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Log::Domain::FGs2LogDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> InsightName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FInsightDomain(
            const FInsightDomain& From
        );

        class GS2LOG_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FInsight>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FInsightDomain> Self;
            const Request::FGetInsightRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FInsightDomain>& Self,
                const Request::FGetInsightRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Model::FInsight>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetInsightRequestPtr Request
        );

        class GS2LOG_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FInsightDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FInsightDomain> Self;
            const Request::FDeleteInsightRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FInsightDomain>& Self,
                const Request::FDeleteInsightRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FInsightDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteInsightRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> InsightName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> InsightName
        );

        class GS2LOG_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FInsight>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FInsightDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FInsightDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Model::FInsight>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Log::Model::FInsightPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FInsightDomain> FInsightDomainPtr;
}
