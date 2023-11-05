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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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

    class GS2QUEST_API FQuestGroupModelMasterDomain:
        public TSharedFromThis<FQuestGroupModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Quest::FGs2QuestRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> QuestGroupName;
    private:

        FString ParentKey;

    public:

        FQuestGroupModelMasterDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> QuestGroupName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FQuestGroupModelMasterDomain(
            const FQuestGroupModelMasterDomain& From
        );

        class GS2QUEST_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FQuestGroupModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FQuestGroupModelMasterDomain> Self;
            const Request::FGetQuestGroupModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FQuestGroupModelMasterDomain> Self,
                const Request::FGetQuestGroupModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetQuestGroupModelMasterRequestPtr Request
        );

        class GS2QUEST_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FQuestGroupModelMasterDomain> Self;
            const Request::FUpdateQuestGroupModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FQuestGroupModelMasterDomain> Self,
                const Request::FUpdateQuestGroupModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateQuestGroupModelMasterRequestPtr Request
        );

        class GS2QUEST_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FQuestGroupModelMasterDomain> Self;
            const Request::FDeleteQuestGroupModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FQuestGroupModelMasterDomain> Self,
                const Request::FDeleteQuestGroupModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteQuestGroupModelMasterRequestPtr Request
        );

        class GS2QUEST_API FCreateQuestModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>,
            public TSharedFromThis<FCreateQuestModelMasterTask>
        {
            const TSharedPtr<FQuestGroupModelMasterDomain> Self;
            const Request::FCreateQuestModelMasterRequestPtr Request;
        public:
            explicit FCreateQuestModelMasterTask(
                const TSharedPtr<FQuestGroupModelMasterDomain> Self,
                const Request::FCreateQuestModelMasterRequestPtr Request
            );

            FCreateQuestModelMasterTask(
                const FCreateQuestModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
            ) override;
        };
        friend FCreateQuestModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateQuestModelMasterTask>> CreateQuestModelMaster(
            Request::FCreateQuestModelMasterRequestPtr Request
        );

        Gs2::Quest::Domain::Iterator::FDescribeQuestModelMastersIteratorPtr QuestModelMasters(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeQuestModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeQuestModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain> QuestModelMaster(
            const FString QuestName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> QuestGroupName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> QuestGroupName
        );

        class GS2QUEST_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FQuestGroupModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FQuestGroupModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FQuestGroupModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Quest::Model::FQuestGroupModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FQuestGroupModelMasterDomain> FQuestGroupModelMasterDomainPtr;
}
