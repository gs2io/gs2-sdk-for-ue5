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
    class FCurrentEntryMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2DICTIONARY_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2DICTIONARY_API FVerifyEntryTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FUserAccessTokenDomain>,
            public TSharedFromThis<FVerifyEntryTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FVerifyEntryRequestPtr Request;
        public:
            explicit FVerifyEntryTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FVerifyEntryRequestPtr Request
            );

            FVerifyEntryTask(
                const FVerifyEntryTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FUserAccessTokenDomain>> Result
            ) override;
        };
        friend FVerifyEntryTask;

        TSharedPtr<FAsyncTask<FVerifyEntryTask>> VerifyEntry(
            Request::FVerifyEntryRequestPtr Request
        );

        Gs2::Dictionary::Domain::Iterator::FDescribeEntriesIteratorPtr Entries(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEntries(
            TFunction<void()> Callback
        );

        void UnsubscribeEntries(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomain> Entry(
            const FString EntryName
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

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
