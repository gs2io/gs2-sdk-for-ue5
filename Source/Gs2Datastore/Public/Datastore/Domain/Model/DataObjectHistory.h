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
#include "Datastore/Gs2Datastore.h"
#include "Datastore/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectsIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectsByUserIdIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectHistoriesIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectHistoriesByUserIdIterator.h"

namespace Gs2::Datastore::Domain::Model
{
    class FNamespaceDomain;
    class FDataObjectDomain;
    class FDataObjectAccessTokenDomain;
    class FDataObjectHistoryDomain;
    class FDataObjectHistoryAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2DATASTORE_API FDataObjectHistoryDomain:
        public TSharedFromThis<FDataObjectHistoryDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Datastore::FGs2DatastoreRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> DataObjectName;
        TOptional<FString> Generation;
    private:

        FString ParentKey;

    public:

        FDataObjectHistoryDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> DataObjectName,
            const TOptional<FString> Generation
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDataObjectHistoryDomain(
            const FDataObjectHistoryDomain& From
        );

        class GS2DATASTORE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Model::FDataObjectHistory>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FDataObjectHistoryDomain> Self;
            const Request::FGetDataObjectHistoryByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FDataObjectHistoryDomain> Self,
                const Request::FGetDataObjectHistoryByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetDataObjectHistoryByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> DataObjectName,
            TOptional<FString> Generation,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> Generation
        );

        class GS2DATASTORE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Model::FDataObjectHistory>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FDataObjectHistoryDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FDataObjectHistoryDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Datastore::Model::FDataObjectHistoryPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FDataObjectHistoryDomain> FDataObjectHistoryDomainPtr;
}
