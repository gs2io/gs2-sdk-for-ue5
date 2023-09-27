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

    class GS2QUEST_API FProgressAccessTokenDomain:
        public TSharedFromThis<FProgressAccessTokenDomain>
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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FProgressAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FProgressAccessTokenDomain(
            const FProgressAccessTokenDomain& From
        );

        class GS2QUEST_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Model::FProgress>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FProgressAccessTokenDomain> Self;
            const Request::FGetProgressRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FProgressAccessTokenDomain> Self,
                const Request::FGetProgressRequestPtr Request
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
            Request::FGetProgressRequestPtr Request
        );

        class GS2QUEST_API FEndTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>,
            public TSharedFromThis<FEndTask>
        {
            const TSharedPtr<FProgressAccessTokenDomain> Self;
            const Request::FEndRequestPtr Request;
        public:
            explicit FEndTask(
                const TSharedPtr<FProgressAccessTokenDomain> Self,
                const Request::FEndRequestPtr Request
            );

            FEndTask(
                const FEndTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>> Result
            ) override;
        };
        friend FEndTask;

        TSharedPtr<FAsyncTask<FEndTask>> End(
            Request::FEndRequestPtr Request
        );

        class GS2QUEST_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FProgressAccessTokenDomain> Self;
            const Request::FDeleteProgressRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FProgressAccessTokenDomain> Self,
                const Request::FDeleteProgressRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FProgressAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteProgressRequestPtr Request
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
            const TSharedPtr<FProgressAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FProgressAccessTokenDomain> Self
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

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Quest::Model::FProgressPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FProgressAccessTokenDomain> FProgressAccessTokenDomainPtr;
}
