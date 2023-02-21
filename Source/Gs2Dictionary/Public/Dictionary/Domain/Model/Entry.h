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

    class GS2DICTIONARY_API FEntryDomain:
        public TSharedFromThis<FEntryDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

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
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
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
                const TSharedPtr<FEntryDomain> Self,
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
                const TSharedPtr<FEntryDomain> Self,
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

    };

    typedef TSharedPtr<FEntryDomain> FEntryDomainPtr;
}
