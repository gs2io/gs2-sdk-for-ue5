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
#include "Quest/Gs2Quest.h"
#include "Quest/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestGroupModelMastersIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestModelMastersIterator.h"
#include "Quest/Domain/Iterator/DescribeProgressesByUserIdIterator.h"
#include "Quest/Domain/Iterator/DescribeCompletedQuestListsIterator.h"
#include "Quest/Domain/Iterator/DescribeCompletedQuestListsByUserIdIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestGroupModelsIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestModelsIterator.h"

namespace Gs2::Quest::Domain::Model
{
    class FNamespaceDomain;
    class FQuestGroupModelMasterDomain;
    class FQuestModelMasterDomain;
    class FCurrentQuestMasterDomain;
    class FProgressDomain;
    class FProgressAccessTokenDomain;
    class FCompletedQuestListDomain;
    class FCompletedQuestListAccessTokenDomain;
    class FQuestGroupModelDomain;
    class FQuestModelDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2QUEST_API FProgressDomain:
        public TSharedFromThis<FProgressDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Quest::FGs2QuestRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FProgressDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FProgressDomain(
            const FProgressDomain& From
        );

        class GS2QUEST_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FProgress>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FProgressDomain> Self;
            const Request::FGetProgressByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FProgressDomain> Self,
                const Request::FGetProgressByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FProgress>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetProgressByUserIdRequestPtr Request
        );

        class GS2QUEST_API FEndTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FProgressDomain>,
            public TSharedFromThis<FEndTask>
        {
            const TSharedPtr<FProgressDomain> Self;
            const Request::FEndByUserIdRequestPtr Request;
        public:
            explicit FEndTask(
                const TSharedPtr<FProgressDomain> Self,
                const Request::FEndByUserIdRequestPtr Request
            );

            FEndTask(
                const FEndTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressDomain>> Result
            ) override;
        };
        friend FEndTask;

        TSharedPtr<FAsyncTask<FEndTask>> End(
            Request::FEndByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2QUEST_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FProgress>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FProgressDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FProgressDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FProgress>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FProgressDomain> FProgressDomainPtr;
}
