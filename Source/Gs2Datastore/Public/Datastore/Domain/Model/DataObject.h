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
#include "Datastore/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectsIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectsByUserIdIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectHistoriesIterator.h"
#include "Datastore/Domain/Iterator/DescribeDataObjectHistoriesByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Datastore::Domain
{
    class FGs2DatastoreDomain;
    typedef TSharedPtr<FGs2DatastoreDomain> FGs2DatastoreDomainPtr;
}

namespace Gs2::Datastore::Domain::Model
{
    class FNamespaceDomain;
    class FDataObjectDomain;
    class FDataObjectAccessTokenDomain;
    class FDataObjectHistoryDomain;
    class FDataObjectHistoryAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2DATASTORE_API FDataObjectDomain:
        public TSharedFromThis<FDataObjectDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Datastore::Domain::FGs2DatastoreDomainPtr Service;
        const Gs2::Datastore::FGs2DatastoreRestClientPtr Client;

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
        TOptional<FString> UserId;
        TOptional<FString> DataObjectName;
    private:

        FString ParentKey;

    public:

        FDataObjectDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Datastore::Domain::FGs2DatastoreDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> DataObjectName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDataObjectDomain(
            const FDataObjectDomain& From
        );

        class GS2DATASTORE_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FDataObjectDomain> Self;
            const Request::FUpdateDataObjectByUserIdRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FDataObjectDomain>& Self,
                const Request::FUpdateDataObjectByUserIdRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateDataObjectByUserIdRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareReUploadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectDomain>,
            public TSharedFromThis<FPrepareReUploadTask>
        {
            const TSharedPtr<FDataObjectDomain> Self;
            const Request::FPrepareReUploadByUserIdRequestPtr Request;
        public:
            explicit FPrepareReUploadTask(
                const TSharedPtr<FDataObjectDomain>& Self,
                const Request::FPrepareReUploadByUserIdRequestPtr Request
            );

            FPrepareReUploadTask(
                const FPrepareReUploadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
            ) override;
        };
        friend FPrepareReUploadTask;

        TSharedPtr<FAsyncTask<FPrepareReUploadTask>> PrepareReUpload(
            Request::FPrepareReUploadByUserIdRequestPtr Request
        );

        class GS2DATASTORE_API FDoneUploadTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectDomain>,
            public TSharedFromThis<FDoneUploadTask>
        {
            const TSharedPtr<FDataObjectDomain> Self;
            const Request::FDoneUploadByUserIdRequestPtr Request;
        public:
            explicit FDoneUploadTask(
                const TSharedPtr<FDataObjectDomain>& Self,
                const Request::FDoneUploadByUserIdRequestPtr Request
            );

            FDoneUploadTask(
                const FDoneUploadTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
            ) override;
        };
        friend FDoneUploadTask;

        TSharedPtr<FAsyncTask<FDoneUploadTask>> DoneUpload(
            Request::FDoneUploadByUserIdRequestPtr Request
        );

        class GS2DATASTORE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FDataObjectDomain> Self;
            const Request::FDeleteDataObjectByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FDataObjectDomain>& Self,
                const Request::FDeleteDataObjectByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteDataObjectByUserIdRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareDownloadByUserIdAndDataObjectNameTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectDomain>,
            public TSharedFromThis<FPrepareDownloadByUserIdAndDataObjectNameTask>
        {
            const TSharedPtr<FDataObjectDomain> Self;
            const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request;
        public:
            explicit FPrepareDownloadByUserIdAndDataObjectNameTask(
                const TSharedPtr<FDataObjectDomain>& Self,
                const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
            );

            FPrepareDownloadByUserIdAndDataObjectNameTask(
                const FPrepareDownloadByUserIdAndDataObjectNameTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
            ) override;
        };
        friend FPrepareDownloadByUserIdAndDataObjectNameTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameTask>> PrepareDownloadByUserIdAndDataObjectName(
            Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
        );

        class GS2DATASTORE_API FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Datastore::Domain::Model::FDataObjectDomain>,
            public TSharedFromThis<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>
        {
            const TSharedPtr<FDataObjectDomain> Self;
            const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request;
        public:
            explicit FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask(
                const TSharedPtr<FDataObjectDomain>& Self,
                const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
            );

            FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask(
                const FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
            ) override;
        };
        friend FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>> PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
            Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
        );

        Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIteratorPtr DataObjectHistories(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDataObjectHistories(
            TFunction<void()> Callback
        );

        void UnsubscribeDataObjectHistories(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain> DataObjectHistory(
            const FString Generation
        );

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
            const TSharedPtr<FDataObjectDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FDataObjectDomain> Self
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

    typedef TSharedPtr<FDataObjectDomain> FDataObjectDomainPtr;
}
