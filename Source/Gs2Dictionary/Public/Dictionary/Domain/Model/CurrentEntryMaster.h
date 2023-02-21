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

    class GS2DICTIONARY_API FCurrentEntryMasterDomain:
        public TSharedFromThis<FCurrentEntryMasterDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FCurrentEntryMasterDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FCurrentEntryMasterDomain(
            const FCurrentEntryMasterDomain& From
        );

        class GS2DICTIONARY_API FExportMasterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>,
            public TSharedFromThis<FExportMasterTask>
        {
            const TSharedPtr<FCurrentEntryMasterDomain> Self;
            const Request::FExportMasterRequestPtr Request;
        public:
            explicit FExportMasterTask(
                const TSharedPtr<FCurrentEntryMasterDomain> Self,
                const Request::FExportMasterRequestPtr Request
            );

            FExportMasterTask(
                const FExportMasterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>> Result
            ) override;
        };
        friend FExportMasterTask;

        TSharedPtr<FAsyncTask<FExportMasterTask>> ExportMaster(
            Request::FExportMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FCurrentEntryMaster>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FCurrentEntryMasterDomain> Self;
            const Request::FGetCurrentEntryMasterRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FCurrentEntryMasterDomain> Self,
                const Request::FGetCurrentEntryMasterRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FCurrentEntryMaster>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetCurrentEntryMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FCurrentEntryMasterDomain> Self;
            const Request::FUpdateCurrentEntryMasterRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FCurrentEntryMasterDomain> Self,
                const Request::FUpdateCurrentEntryMasterRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateCurrentEntryMasterRequestPtr Request
        );

        class GS2DICTIONARY_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FCurrentEntryMasterDomain> Self;
            const Request::FUpdateCurrentEntryMasterFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FCurrentEntryMasterDomain> Self,
                const Request::FUpdateCurrentEntryMasterFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Domain::Model::FCurrentEntryMasterDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateCurrentEntryMasterFromGitHubRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2DICTIONARY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Dictionary::Model::FCurrentEntryMaster>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FCurrentEntryMasterDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FCurrentEntryMasterDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Dictionary::Model::FCurrentEntryMaster>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FCurrentEntryMasterDomain> FCurrentEntryMasterDomainPtr;
}
