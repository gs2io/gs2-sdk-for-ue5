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

    class GS2QUEST_API FQuestModelMasterDomain:
        public TSharedFromThis<FQuestModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Quest::FGs2QuestRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> QuestGroupName;
        TOptional<FString> QuestName;
    private:

        FString ParentKey;

    public:

        FQuestModelMasterDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> QuestGroupName,
            const TOptional<FString> QuestName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FQuestModelMasterDomain(
            const FQuestModelMasterDomain& From
        );

        class GS2QUEST_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FQuestModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FQuestModelMasterDomain> Self;
            const Request::FGetQuestModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FQuestModelMasterDomain> Self,
                const Request::FGetQuestModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetQuestModelMasterRequestPtr Request
        );

        class GS2QUEST_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FQuestModelMasterDomain> Self;
            const Request::FUpdateQuestModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FQuestModelMasterDomain> Self,
                const Request::FUpdateQuestModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateQuestModelMasterRequestPtr Request
        );

        class GS2QUEST_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FQuestModelMasterDomain> Self;
            const Request::FDeleteQuestModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FQuestModelMasterDomain> Self,
                const Request::FDeleteQuestModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteQuestModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> QuestGroupName,
            TOptional<FString> QuestName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> QuestName
        );

        class GS2QUEST_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FQuestModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FQuestModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FQuestModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Quest::Model::FQuestModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FQuestModelMasterDomain> FQuestModelMasterDomainPtr;
}
