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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Datastore/Domain/Model/DataObjectAccessToken.h"
#include "Datastore/Model/Gs2DatastoreEzDataObject.h"
#include "Datastore/Model/Gs2DatastoreEzDataObjectHistory.h"
#include "Gs2DatastoreEzDataObjectHistoryGameSessionDomain.h"
#include "Datastore/Domain/Iterator/Gs2DatastoreEzDescribeDataObjectHistoriesIterator.h"
#include "Gs2DatastoreEzDataObjectGameSessionDomain.h"
#include "Datastore/Domain/Iterator/Gs2DatastoreEzDescribeDataObjectsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    class EZGS2_API FEzDataObjectGameSessionDomain final :
        public TSharedFromThis<FEzDataObjectGameSessionDomain>
    {
        Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> UploadUrl() const;
        TOptional<FString> FileUrl() const;
        TOptional<int64> ContentLength() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> DataObjectName() const;

        FEzDataObjectGameSessionDomain(
            Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FUpdateDataObjectTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FUpdateDataObjectTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;
            TOptional<FString> Scope;
            TOptional<TArray<FString>> AllowUserIds;

        public:
            explicit FUpdateDataObjectTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self,
                TOptional<FString> Scope = TOptional<FString>(),
                TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateDataObjectTask;

        TSharedPtr<FAsyncTask<FUpdateDataObjectTask>> UpdateDataObject(
            TOptional<FString> Scope = TOptional<FString>(),
            TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>()
        );

        class FPrepareReUploadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FPrepareReUploadTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;
            TOptional<FString> ContentType;

        public:
            explicit FPrepareReUploadTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self,
                TOptional<FString> ContentType = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FPrepareReUploadTask;

        TSharedPtr<FAsyncTask<FPrepareReUploadTask>> PrepareReUpload(
            TOptional<FString> ContentType = TOptional<FString>()
        );

        class FDoneUploadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FDoneUploadTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;

        public:
            explicit FDoneUploadTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FDoneUploadTask;

        TSharedPtr<FAsyncTask<FDoneUploadTask>> DoneUpload(
        );

        class FDeleteDataObjectTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FDeleteDataObjectTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;

        public:
            explicit FDeleteDataObjectTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteDataObjectTask;

        TSharedPtr<FAsyncTask<FDeleteDataObjectTask>> DeleteDataObject(
        );

        class FPrepareDownloadOwnDataTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FPrepareDownloadOwnDataTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;

        public:
            explicit FPrepareDownloadOwnDataTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FPrepareDownloadOwnDataTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadOwnDataTask>> PrepareDownloadOwnData(
        );

        Gs2::UE5::Datastore::Domain::Iterator::FEzDescribeDataObjectHistoriesIteratorPtr DataObjectHistories(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDataObjectHistories(TFunction<void()> Callback);

        void UnsubscribeDataObjectHistories(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Datastore::Domain::Model::FEzDataObjectHistoryGameSessionDomainPtr DataObjectHistory(
            const FString Generation
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Model::FEzDataObject>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObjectPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Datastore::Model::FEzDataObjectPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

        class FReUploadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FReUploadTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;
            TArray<uint8> Binary;
            TOptional<FString> ContentType;

        public:
            explicit FReUploadTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self,
                TArray<uint8> Binary,
                TOptional<FString> ContentType = TOptional<FString>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FReUploadTask;

        TSharedPtr<FAsyncTask<FReUploadTask>> ReUpload(
            TArray<uint8> Binary,
            TOptional<FString> ContentType = TOptional<FString>()
        );

        class FDownloadTask :
            public Gs2::Core::Util::TGs2Future<TArray<uint8>>,
            public TSharedFromThis<FDownloadTask>
        {
            TSharedPtr<FEzDataObjectGameSessionDomain> Self;

        public:
            explicit FDownloadTask(
                TSharedPtr<FEzDataObjectGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<uint8>>> Result
            ) override;
        };
        friend FDownloadTask;

        TSharedPtr<FAsyncTask<FDownloadTask>> Download(
        );
    };
    typedef TSharedPtr<FEzDataObjectGameSessionDomain> FEzDataObjectGameSessionDomainPtr;
}
