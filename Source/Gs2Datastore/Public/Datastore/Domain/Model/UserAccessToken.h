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

    class GS2DATASTORE_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Datastore::FGs2DatastoreRestClientPtr Client;

        public:
        TOptional<FString> UploadUrl;
        TOptional<FString> FileUrl;
        TOptional<int64> ContentLength;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
        TOptional<FString> GetFileUrl() const
        {
            return FileUrl;
        }
        TOptional<int64> GetContentLength() const
        {
            return ContentLength;
        }
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
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2DATASTORE_API FPrepareUploadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FPrepareUploadTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FPrepareUploadRequestPtr Request;
        public:
            explicit FPrepareUploadTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FPrepareUploadRequestPtr Request
            );

            FPrepareUploadTask(
                const FPrepareUploadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FPrepareUploadTask;

        TSharedPtr<FAsyncTask<FPrepareUploadTask>> PrepareUpload(
            Request::FPrepareUploadRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareDownloadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FPrepareDownloadTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FPrepareDownloadRequestPtr Request;
        public:
            explicit FPrepareDownloadTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FPrepareDownloadRequestPtr Request
            );

            FPrepareDownloadTask(
                const FPrepareDownloadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FPrepareDownloadTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadTask>> PrepareDownload(
            Request::FPrepareDownloadRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareDownloadByGenerationTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FPrepareDownloadByGenerationTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FPrepareDownloadByGenerationRequestPtr Request;
        public:
            explicit FPrepareDownloadByGenerationTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FPrepareDownloadByGenerationRequestPtr Request
            );

            FPrepareDownloadByGenerationTask(
                const FPrepareDownloadByGenerationTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FPrepareDownloadByGenerationTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadByGenerationTask>> PrepareDownloadByGeneration(
            Request::FPrepareDownloadByGenerationRequestPtr Request
        );

        Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIteratorPtr DataObjects(
            const TOptional<FString> Status
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDataObjects(
            TFunction<void()> Callback
        );

        void UnsubscribeDataObjects(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain> DataObject(
            const FString DataObjectName
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

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
