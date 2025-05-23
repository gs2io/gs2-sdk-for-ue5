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
#include "Dictionary/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntryModelsIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntryModelMastersIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntriesIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntriesByUserIdIterator.h"
#include "Dictionary/Domain/Iterator/DescribeLikesIterator.h"
#include "Dictionary/Domain/Iterator/DescribeLikesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Dictionary::Domain
{
    class FGs2DictionaryDomain;
    typedef TSharedPtr<FGs2DictionaryDomain> FGs2DictionaryDomainPtr;
}

namespace Gs2::Dictionary::Domain::Model
{
    class FNamespaceDomain;
    class FEntryModelDomain;
    class FEntryModelMasterDomain;
    class FEntryDomain;
    class FEntryAccessTokenDomain;
    class FLikeDomain;
    class FLikeAccessTokenDomain;
    class FCurrentEntryMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2DICTIONARY_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Dictionary::Domain::FGs2DictionaryDomainPtr Service;
        const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

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
            const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2DICTIONARY_API FAddEntriesTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>,
            public TSharedFromThis<FAddEntriesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FAddEntriesByUserIdRequestPtr Request;
        public:
            explicit FAddEntriesTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FAddEntriesByUserIdRequestPtr Request
            );

            FAddEntriesTask(
                const FAddEntriesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>> Result
            ) override;
        };
        friend FAddEntriesTask;

        TSharedPtr<FAsyncTask<FAddEntriesTask>> AddEntries(
            Request::FAddEntriesByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FResetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FUserDomain>,
            public TSharedFromThis<FResetTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FResetByUserIdRequestPtr Request;
        public:
            explicit FResetTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FResetByUserIdRequestPtr Request
            );

            FResetTask(
                const FResetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FResetTask;

        TSharedPtr<FAsyncTask<FResetTask>> Reset(
            Request::FResetByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FDeleteEntriesTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>,
            public TSharedFromThis<FDeleteEntriesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDeleteEntriesByUserIdRequestPtr Request;
        public:
            explicit FDeleteEntriesTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FDeleteEntriesByUserIdRequestPtr Request
            );

            FDeleteEntriesTask(
                const FDeleteEntriesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>> Result
            ) override;
        };
        friend FDeleteEntriesTask;

        TSharedPtr<FAsyncTask<FDeleteEntriesTask>> DeleteEntries(
            Request::FDeleteEntriesByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FAddLikesTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeDomain>>>,
            public TSharedFromThis<FAddLikesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FAddLikesByUserIdRequestPtr Request;
        public:
            explicit FAddLikesTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FAddLikesByUserIdRequestPtr Request
            );

            FAddLikesTask(
                const FAddLikesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeDomain>>>> Result
            ) override;
        };
        friend FAddLikesTask;

        TSharedPtr<FAsyncTask<FAddLikesTask>> AddLikes(
            Request::FAddLikesByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FResetLikesTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FUserDomain>,
            public TSharedFromThis<FResetLikesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FResetLikesByUserIdRequestPtr Request;
        public:
            explicit FResetLikesTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FResetLikesByUserIdRequestPtr Request
            );

            FResetLikesTask(
                const FResetLikesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FResetLikesTask;

        TSharedPtr<FAsyncTask<FResetLikesTask>> ResetLikes(
            Request::FResetLikesByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FDeleteLikesTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeDomain>>>,
            public TSharedFromThis<FDeleteLikesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDeleteLikesByUserIdRequestPtr Request;
        public:
            explicit FDeleteLikesTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FDeleteLikesByUserIdRequestPtr Request
            );

            FDeleteLikesTask(
                const FDeleteLikesTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeDomain>>>> Result
            ) override;
        };
        friend FDeleteLikesTask;

        TSharedPtr<FAsyncTask<FDeleteLikesTask>> DeleteLikes(
            Request::FDeleteLikesByUserIdRequestPtr Request
        );

        Gs2::Dictionary::Domain::Iterator::FDescribeEntriesByUserIdIteratorPtr Entries(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEntries(
            TFunction<void()> Callback
        );

        void UnsubscribeEntries(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain> Entry(
            const FString EntryModelName
        );

        Gs2::Dictionary::Domain::Iterator::FDescribeLikesByUserIdIteratorPtr Likes(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLikes(
            TFunction<void()> Callback
        );

        void UnsubscribeLikes(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FLikeDomain> Like(
            const FString EntryModelName
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
