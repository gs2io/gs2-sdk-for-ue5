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

    class GS2LOG_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Log::Domain::FGs2LogDomainPtr Service;
        const Gs2::Log::FGs2LogRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<int64> TotalCount;
        TOptional<int64> ScanSize;
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
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Log::Domain::FGs2LogDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2LOG_API FSendInGameLogTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Domain::Model::FInGameLogDomain>,
            public TSharedFromThis<FSendInGameLogTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FSendInGameLogByUserIdRequestPtr Request;
        public:
            explicit FSendInGameLogTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FSendInGameLogByUserIdRequestPtr Request
            );

            FSendInGameLogTask(
                const FSendInGameLogTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FInGameLogDomain>> Result
            ) override;
        };
        friend FSendInGameLogTask;

        TSharedPtr<FAsyncTask<FSendInGameLogTask>> SendInGameLog(
            Request::FSendInGameLogByUserIdRequestPtr Request
        );

        Gs2::Log::Domain::Iterator::FQueryInGameLogIteratorPtr InGameLog(
            const TSharedPtr<TArray<TSharedPtr<Gs2::Log::Model::FInGameLogTag>>> Tags = nullptr,
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeInGameLog(
            TFunction<void()> Callback
        );

        void UnsubscribeInGameLog(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
