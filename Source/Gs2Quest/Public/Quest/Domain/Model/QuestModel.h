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

    class GS2QUEST_API FQuestModelDomain:
        public TSharedFromThis<FQuestModelDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Quest::Domain::FGs2QuestDomainPtr Service;
        const Gs2::Quest::FGs2QuestRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> QuestGroupName;
        TOptional<FString> QuestName;
    private:

        FString ParentKey;

    public:

        FQuestModelDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Quest::Domain::FGs2QuestDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> QuestGroupName,
            const TOptional<FString> QuestName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FQuestModelDomain(
            const FQuestModelDomain& From
        );

        class GS2QUEST_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FQuestModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FQuestModelDomain> Self;
            const Request::FGetQuestModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FQuestModelDomain>& Self,
                const Request::FGetQuestModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetQuestModelRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FQuestModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FQuestModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FQuestModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Quest::Model::FQuestModelPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FQuestModelDomain> FQuestModelDomainPtr;
}
