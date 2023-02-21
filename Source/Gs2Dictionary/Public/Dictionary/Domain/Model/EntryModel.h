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

    class GS2DICTIONARY_API FEntryModelDomain:
        public TSharedFromThis<FEntryModelDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> EntryName;
    private:

        FString ParentKey;

    public:

        FEntryModelDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> EntryName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FEntryModelDomain(
            const FEntryModelDomain& From
        );

        class GS2DICTIONARY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FEntryModel>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FEntryModelDomain> Self;
            const Request::FGetEntryModelRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FEntryModelDomain> Self,
                const Request::FGetEntryModelRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModel>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetEntryModelRequestPtr Request
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
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FEntryModel>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FEntryModelDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FEntryModelDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FEntryModel>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FEntryModelDomain> FEntryModelDomainPtr;
}
