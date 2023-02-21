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

    class GS2QUEST_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Quest::FGs2QuestRestClientPtr Client;

        public:
        TOptional<FString> TransactionId;
        TOptional<bool> AutoRunStampSheet;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetTransactionId() const
        {
            return TransactionId;
        }
        TOptional<bool> GetAutoRunStampSheet() const
        {
            return AutoRunStampSheet;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2QUEST_API FStartTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FUserAccessTokenDomain>,
            public TSharedFromThis<FStartTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FStartRequestPtr Request;
        public:
            explicit FStartTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FStartRequestPtr Request
            );

            FStartTask(
                const FStartTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FUserAccessTokenDomain>> Result
            ) override;
        };
        friend FStartTask;

        TSharedPtr<FAsyncTask<FStartTask>> Start(
            Request::FStartRequestPtr Request
        );

        class GS2QUEST_API FDeleteProgressTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>,
            public TSharedFromThis<FDeleteProgressTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FDeleteProgressRequestPtr Request;
        public:
            explicit FDeleteProgressTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FDeleteProgressRequestPtr Request
            );

            FDeleteProgressTask(
                const FDeleteProgressTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteProgressTask;

        TSharedPtr<FAsyncTask<FDeleteProgressTask>> DeleteProgress(
            Request::FDeleteProgressRequestPtr Request
        );

        TSharedPtr<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain> Progress(
        ) const;

        Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIteratorPtr CompletedQuestLists(
        ) const;

        TSharedPtr<Gs2::Quest::Domain::Model::FCompletedQuestListAccessTokenDomain> CompletedQuestList(
            const FString QuestGroupName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
