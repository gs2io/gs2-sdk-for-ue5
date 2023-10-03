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
#include "Dictionary/Gs2Dictionary.h"
#include "Dictionary/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntryModelsIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntryModelMastersIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntriesIterator.h"
#include "Dictionary/Domain/Iterator/DescribeEntriesByUserIdIterator.h"

namespace Gs2::Dictionary::Domain::Model
{
    class FNamespaceDomain;
    class FEntryModelDomain;
    class FEntryModelMasterDomain;
    class FEntryDomain;
    class FEntryAccessTokenDomain;
    class FCurrentEntryMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2DICTIONARY_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

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
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
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
                const TSharedPtr<FUserDomain> Self,
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
                const TSharedPtr<FUserDomain> Self,
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

        class GS2DICTIONARY_API FVerifyEntryTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FUserDomain>,
            public TSharedFromThis<FVerifyEntryTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FVerifyEntryByUserIdRequestPtr Request;
        public:
            explicit FVerifyEntryTask(
                const TSharedPtr<FUserDomain> Self,
                const Request::FVerifyEntryByUserIdRequestPtr Request
            );

            FVerifyEntryTask(
                const FVerifyEntryTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FVerifyEntryTask;

        TSharedPtr<FAsyncTask<FVerifyEntryTask>> VerifyEntry(
            Request::FVerifyEntryByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FDeleteEntriesTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>>>,
            public TSharedFromThis<FDeleteEntriesTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDeleteEntriesByUserIdRequestPtr Request;
        public:
            explicit FDeleteEntriesTask(
                const TSharedPtr<FUserDomain> Self,
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

        Gs2::Dictionary::Domain::Iterator::FDescribeEntriesByUserIdIteratorPtr Entries(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEntries(
            TFunction<void()> Callback
        );

        void UnsubscribeEntries(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain> Entry(
            const FString EntryName
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

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
