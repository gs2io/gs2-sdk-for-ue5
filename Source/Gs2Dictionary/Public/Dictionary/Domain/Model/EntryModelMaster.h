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

    class GS2DICTIONARY_API FEntryModelMasterDomain:
        public TSharedFromThis<FEntryModelMasterDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Dictionary::Domain::FGs2DictionaryDomainPtr Service;
        const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> EntryName;
    private:

        FString ParentKey;

    public:

        FEntryModelMasterDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> EntryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FEntryModelMasterDomain(
            const FEntryModelMasterDomain& From
        );

        class GS2DICTIONARY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FEntryModelMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FEntryModelMasterDomain> Self;
            const Request::FGetEntryModelMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FEntryModelMasterDomain>& Self,
                const Request::FGetEntryModelMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModelMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetEntryModelMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FEntryModelMasterDomain> Self;
            const Request::FUpdateEntryModelMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FEntryModelMasterDomain>& Self,
                const Request::FUpdateEntryModelMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateEntryModelMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FEntryModelMasterDomain> Self;
            const Request::FDeleteEntryModelMasterRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FEntryModelMasterDomain>& Self,
                const Request::FDeleteEntryModelMasterRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FEntryModelMasterDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteEntryModelMasterRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> EntryName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> EntryName
        );

        class GS2DICTIONARY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FEntryModelMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FEntryModelMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FEntryModelMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModelMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Dictionary::Model::FEntryModelMasterPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FEntryModelMasterDomain> FEntryModelMasterDomainPtr;
}
