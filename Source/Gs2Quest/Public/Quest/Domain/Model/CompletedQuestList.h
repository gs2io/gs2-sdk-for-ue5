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

    class GS2QUEST_API FCompletedQuestListDomain:
        public TSharedFromThis<FCompletedQuestListDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Quest::Domain::FGs2QuestDomainPtr Service;
        const Gs2::Quest::FGs2QuestRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> QuestGroupName;
    private:

        FString ParentKey;

    public:

        FCompletedQuestListDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Quest::Domain::FGs2QuestDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> QuestGroupName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCompletedQuestListDomain(
            const FCompletedQuestListDomain& From
        );

        class GS2QUEST_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FCompletedQuestList>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCompletedQuestListDomain> Self;
            const Request::FGetCompletedQuestListByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCompletedQuestListDomain>& Self,
                const Request::FGetCompletedQuestListByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCompletedQuestList>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCompletedQuestListByUserIdRequestPtr Request
        );

        class GS2QUEST_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FCompletedQuestListDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FCompletedQuestListDomain> Self;
            const Request::FDeleteCompletedQuestListByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FCompletedQuestListDomain>& Self,
                const Request::FDeleteCompletedQuestListByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FCompletedQuestListDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteCompletedQuestListByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> QuestGroupName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> QuestGroupName
        );

        class GS2QUEST_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FCompletedQuestList>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCompletedQuestListDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCompletedQuestListDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FCompletedQuestList>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Quest::Model::FCompletedQuestListPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FCompletedQuestListDomain> FCompletedQuestListDomainPtr;
}
