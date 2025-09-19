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

    class GS2DICTIONARY_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Dictionary::Domain::FGs2DictionaryDomainPtr Service;
        const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> Url;
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2DICTIONARY_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2DICTIONARY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2DICTIONARY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2DICTIONARY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        class GS2DICTIONARY_API FCreateEntryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>,
            public TSharedFromThis<FCreateEntryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FCreateEntryModelMasterRequestPtr Request;
        public:
            explicit FCreateEntryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FCreateEntryModelMasterRequestPtr Request
            );

            FCreateEntryModelMasterTask(
                const FCreateEntryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>> Result
            ) override;
        };
        friend FCreateEntryModelMasterTask;

        TSharedPtr<FAsyncTask<FCreateEntryModelMasterTask>> CreateEntryModelMaster(
            Request::FCreateEntryModelMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FGetEntryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FEntryModelMaster>,
            public TSharedFromThis<FGetEntryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetEntryModelMasterRequestPtr Request;
        public:
            explicit FGetEntryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FGetEntryModelMasterRequestPtr Request
            );

            FGetEntryModelMasterTask(
                const FGetEntryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModelMaster>> Result
            ) override;
        };
        friend FGetEntryModelMasterTask;

        TSharedPtr<FAsyncTask<FGetEntryModelMasterTask>> GetEntryModelMaster(
            Request::FGetEntryModelMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FUpdateEntryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>,
            public TSharedFromThis<FUpdateEntryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateEntryModelMasterRequestPtr Request;
        public:
            explicit FUpdateEntryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FUpdateEntryModelMasterRequestPtr Request
            );

            FUpdateEntryModelMasterTask(
                const FUpdateEntryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateEntryModelMasterTask;

        TSharedPtr<FAsyncTask<FUpdateEntryModelMasterTask>> UpdateEntryModelMaster(
            Request::FUpdateEntryModelMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FDeleteEntryModelMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>,
            public TSharedFromThis<FDeleteEntryModelMasterTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteEntryModelMasterRequestPtr Request;
        public:
            explicit FDeleteEntryModelMasterTask(
                const TSharedPtr<FNamespaceDomain>& Self,
                const Request::FDeleteEntryModelMasterRequestPtr Request
            );

            FDeleteEntryModelMasterTask(
                const FDeleteEntryModelMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteEntryModelMasterTask;

        TSharedPtr<FAsyncTask<FDeleteEntryModelMasterTask>> DeleteEntryModelMaster(
            Request::FDeleteEntryModelMasterRequestPtr Request
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain> CurrentEntryMaster(
        );

        Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIteratorPtr EntryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEntryModels(
            TFunction<void()> Callback
        );

        void UnsubscribeEntryModels(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryModelDomain> EntryModel(
            const FString EntryModelName
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FUserDomain> User(
            const FString UserId
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );

        Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelMastersIteratorPtr EntryModelMasters(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEntryModelMasters(
            TFunction<void()> Callback
        );

        void UnsubscribeEntryModelMasters(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain> EntryModelMaster(
            const FString EntryModelName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2DICTIONARY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Dictionary::Model::FNamespacePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
