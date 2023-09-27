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

    class GS2DATASTORE_API FDataObjectAccessTokenDomain:
        public TSharedFromThis<FDataObjectAccessTokenDomain>
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
        TOptional<FString> DataObjectName;
    private:

        FString ParentKey;

    public:

        FDataObjectAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> DataObjectName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDataObjectAccessTokenDomain(
            const FDataObjectAccessTokenDomain& From
        );

        class GS2DATASTORE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FDataObjectAccessTokenDomain> Self;
            const Request::FUpdateDataObjectRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FDataObjectAccessTokenDomain> Self,
                const Request::FUpdateDataObjectRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateDataObjectRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareReUploadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FPrepareReUploadTask>
        {
            const TSharedPtr<FDataObjectAccessTokenDomain> Self;
            const Request::FPrepareReUploadRequestPtr Request;
        public:
            explicit FPrepareReUploadTask(
                const TSharedPtr<FDataObjectAccessTokenDomain> Self,
                const Request::FPrepareReUploadRequestPtr Request
            );

            FPrepareReUploadTask(
                const FPrepareReUploadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FPrepareReUploadTask;

        TSharedPtr<FAsyncTask<FPrepareReUploadTask>> PrepareReUpload(
            Request::FPrepareReUploadRequestPtr Request
        );

        class GS2DATASTORE_API FDoneUploadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FDoneUploadTask>
        {
            const TSharedPtr<FDataObjectAccessTokenDomain> Self;
            const Request::FDoneUploadRequestPtr Request;
        public:
            explicit FDoneUploadTask(
                const TSharedPtr<FDataObjectAccessTokenDomain> Self,
                const Request::FDoneUploadRequestPtr Request
            );

            FDoneUploadTask(
                const FDoneUploadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FDoneUploadTask;

        TSharedPtr<FAsyncTask<FDoneUploadTask>> DoneUpload(
            Request::FDoneUploadRequestPtr Request
        );

        class GS2DATASTORE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FDataObjectAccessTokenDomain> Self;
            const Request::FDeleteDataObjectRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FDataObjectAccessTokenDomain> Self,
                const Request::FDeleteDataObjectRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteDataObjectRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareDownloadOwnDataTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FPrepareDownloadOwnDataTask>
        {
            const TSharedPtr<FDataObjectAccessTokenDomain> Self;
            const Request::FPrepareDownloadOwnDataRequestPtr Request;
        public:
            explicit FPrepareDownloadOwnDataTask(
                const TSharedPtr<FDataObjectAccessTokenDomain> Self,
                const Request::FPrepareDownloadOwnDataRequestPtr Request
            );

            FPrepareDownloadOwnDataTask(
                const FPrepareDownloadOwnDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FPrepareDownloadOwnDataTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadOwnDataTask>> PrepareDownloadOwnData(
            Request::FPrepareDownloadOwnDataRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareDownloadOwnDataByGenerationTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>,
            public TSharedFromThis<FPrepareDownloadOwnDataByGenerationTask>
        {
            const TSharedPtr<FDataObjectAccessTokenDomain> Self;
            const Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request;
        public:
            explicit FPrepareDownloadOwnDataByGenerationTask(
                const TSharedPtr<FDataObjectAccessTokenDomain> Self,
                const Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request
            );

            FPrepareDownloadOwnDataByGenerationTask(
                const FPrepareDownloadOwnDataByGenerationTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
            ) override;
        };
        friend FPrepareDownloadOwnDataByGenerationTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadOwnDataByGenerationTask>> PrepareDownloadOwnDataByGeneration(
            Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request
        );

        Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIteratorPtr DataObjectHistories(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDataObjectHistories(
            TFunction<void()> Callback
        );

        void UnsubscribeDataObjectHistories(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectHistoryAccessTokenDomain> DataObjectHistory(
            const FString Generation
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> DataObjectName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> DataObjectName
        );

        class GS2DATASTORE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Model::FDataObject>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FDataObjectAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FDataObjectAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObject>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Datastore::Model::FDataObjectPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FDataObjectAccessTokenDomain> FDataObjectAccessTokenDomainPtr;
}
