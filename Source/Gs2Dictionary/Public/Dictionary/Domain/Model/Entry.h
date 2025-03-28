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

    class GS2DICTIONARY_API FEntryDomain:
        public TSharedFromThis<FEntryDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Dictionary::Domain::FGs2DictionaryDomainPtr Service;
        const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

        public:
        TOptional<FString> Body;
        TOptional<FString> Signature;
        TOptional<FString> GetBody() const
        {
            return Body;
        }
        TOptional<FString> GetSignature() const
        {
            return Signature;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> EntryModelName;
    private:

        FString ParentKey;

    public:

        FEntryDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> EntryModelName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FEntryDomain(
            const FEntryDomain& From
        );

        class GS2DICTIONARY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FEntry>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FEntryDomain> Self;
            const Request::FGetEntryByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FEntryDomain>& Self,
                const Request::FGetEntryByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntry>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetEntryByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FGetWithSignatureTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FEntryDomain>,
            public TSharedFromThis<FGetWithSignatureTask>
        {
            const TSharedPtr<FEntryDomain> Self;
            const Request::FGetEntryWithSignatureByUserIdRequestPtr Request;
        public:
            explicit FGetWithSignatureTask(
                const TSharedPtr<FEntryDomain>& Self,
                const Request::FGetEntryWithSignatureByUserIdRequestPtr Request
            );

            FGetWithSignatureTask(
                const FGetWithSignatureTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>> Result
            ) override;
        };
        friend FGetWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetWithSignatureTask>> GetWithSignature(
            Request::FGetEntryWithSignatureByUserIdRequestPtr Request
        );

        class GS2DICTIONARY_API FVerifyTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FEntryDomain>,
            public TSharedFromThis<FVerifyTask>
        {
            const TSharedPtr<FEntryDomain> Self;
            const Request::FVerifyEntryByUserIdRequestPtr Request;
        public:
            explicit FVerifyTask(
                const TSharedPtr<FEntryDomain>& Self,
                const Request::FVerifyEntryByUserIdRequestPtr Request
            );

            FVerifyTask(
                const FVerifyTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryDomain>> Result
            ) override;
        };
        friend FVerifyTask;

        TSharedPtr<FAsyncTask<FVerifyTask>> Verify(
            Request::FVerifyEntryByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> EntryModelName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> EntryModelName
        );

        class GS2DICTIONARY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FEntry>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FEntryDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FEntryDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntry>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Dictionary::Model::FEntryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FEntryDomain> FEntryDomainPtr;
}
