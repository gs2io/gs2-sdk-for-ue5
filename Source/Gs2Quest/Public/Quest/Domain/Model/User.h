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
#include "Quest/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestGroupModelMastersIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestModelMastersIterator.h"
#include "Quest/Domain/Iterator/DescribeProgressesByUserIdIterator.h"
#include "Quest/Domain/Iterator/DescribeCompletedQuestListsIterator.h"
#include "Quest/Domain/Iterator/DescribeCompletedQuestListsByUserIdIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestGroupModelsIterator.h"
#include "Quest/Domain/Iterator/DescribeQuestModelsIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Quest::Domain
{
    class FGs2QuestDomain;
    typedef TSharedPtr<FGs2QuestDomain> FGs2QuestDomainPtr;
}

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

    class GS2QUEST_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Quest::Domain::FGs2QuestDomainPtr Service;
        const Gs2::Quest::FGs2QuestRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Quest::Domain::FGs2QuestDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2QUEST_API FCreateProgressTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FProgressDomain>,
            public TSharedFromThis<FCreateProgressTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FCreateProgressByUserIdRequestPtr Request;
        public:
            explicit FCreateProgressTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FCreateProgressByUserIdRequestPtr Request
            );

            FCreateProgressTask(
                const FCreateProgressTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressDomain>> Result
            ) override;
        };
        friend FCreateProgressTask;

        TSharedPtr<FAsyncTask<FCreateProgressTask>> CreateProgress(
            Request::FCreateProgressByUserIdRequestPtr Request
        );

        class GS2QUEST_API FStartTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::FTransactionDomain>,
            public TSharedFromThis<FStartTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FStartByUserIdRequestPtr Request;
        public:
            explicit FStartTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FStartByUserIdRequestPtr Request
            );

            FStartTask(
                const FStartTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
            ) override;
        };
        friend FStartTask;

        TSharedPtr<FAsyncTask<FStartTask>> Start(
            Request::FStartByUserIdRequestPtr Request
        );

        Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsByUserIdIteratorPtr CompletedQuestLists(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeCompletedQuestLists(
            TFunction<void()> Callback
        );

        void UnsubscribeCompletedQuestLists(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Quest::Domain::Model::FCompletedQuestListDomain> CompletedQuestList(
            const FString QuestGroupName
        );

        Gs2::Quest::Domain::Iterator::FDescribeProgressesByUserIdIteratorPtr Progresses(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeProgresses(
            TFunction<void()> Callback
        );

        void UnsubscribeProgresses(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Quest::Domain::Model::FProgressDomain> Progress(
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
