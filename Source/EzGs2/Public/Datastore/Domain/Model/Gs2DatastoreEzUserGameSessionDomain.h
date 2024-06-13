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
#include "Datastore/Domain/Model/UserAccessToken.h"
#include "Datastore/Model/Gs2DatastoreEzDataObject.h"
#include "Datastore/Model/Gs2DatastoreEzDataObjectHistory.h"
#include "Gs2DatastoreEzDataObjectGameSessionDomain.h"
#include "Datastore/Domain/Iterator/Gs2DatastoreEzDescribeDataObjectsIterator.h"
#include "Gs2DatastoreEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Datastore::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> UploadUrl() const;
        TOptional<FString> FileUrl() const;
        TOptional<int64> ContentLength() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Datastore::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FPrepareUploadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FPrepareUploadTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            TOptional<FString> Name;
            TOptional<FString> Scope;
            TOptional<FString> ContentType;
            TOptional<TArray<FString>> AllowUserIds;
            TOptional<bool> UpdateIfExists;

        public:
            explicit FPrepareUploadTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                TOptional<FString> Name = TOptional<FString>(),
                TOptional<FString> Scope = TOptional<FString>(),
                TOptional<FString> ContentType = TOptional<FString>(),
                TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>(),
                TOptional<bool> UpdateIfExists = TOptional<bool>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FPrepareUploadTask;

        TSharedPtr<FAsyncTask<FPrepareUploadTask>> PrepareUpload(
            TOptional<FString> Name = TOptional<FString>(),
            TOptional<FString> Scope = TOptional<FString>(),
            TOptional<FString> ContentType = TOptional<FString>(),
            TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>(),
            TOptional<bool> UpdateIfExists = TOptional<bool>()
        );

        class FPrepareDownloadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FPrepareDownloadTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString DataObjectId;

        public:
            explicit FPrepareDownloadTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString DataObjectId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FPrepareDownloadTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadTask>> PrepareDownload(
            FString DataObjectId
        );

        Gs2::UE5::Datastore::Domain::Iterator::FEzDescribeDataObjectsIteratorPtr DataObjects(
            const TOptional<FString> Status = TOptional<FString>()
        ) const;

        Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomainPtr DataObject(
            const FString DataObjectName
        ) const;

        class FUploadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>,
            public TSharedFromThis<FUploadTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            TArray<uint8> Binary;
            TOptional<FString> Name;
            TOptional<FString> Scope;
            TOptional<FString> ContentType;
            TOptional<TArray<FString>> AllowUserIds;
            TOptional<bool> UpdateIfExists;

        public:
            explicit FUploadTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                TArray<uint8> Binary,
                TOptional<FString> Name = TOptional<FString>(),
                TOptional<FString> Scope = TOptional<FString>(),
                TOptional<FString> ContentType = TOptional<FString>(),
                TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>(),
                TOptional<bool> UpdateIfExists = TOptional<bool>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectGameSessionDomain>> Result
            ) override;
        };
        friend FUploadTask;

        TSharedPtr<FAsyncTask<FUploadTask>> Upload(
            TArray<uint8> Binary,
            TOptional<FString> Name = TOptional<FString>(),
            TOptional<FString> Scope = TOptional<FString>(),
            TOptional<FString> ContentType = TOptional<FString>(),
            TOptional<TArray<FString>> AllowUserIds = TOptional<TArray<FString>>(),
            TOptional<bool> UpdateIfExists = TOptional<bool>()
        );

        class FDownloadTask :
            public Gs2::Core::Util::TGs2Future<TArray<uint8>>,
            public TSharedFromThis<FDownloadTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString DataObjectId;

        public:
            explicit FDownloadTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString DataObjectId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<uint8>>> Result
            ) override;
        };
        friend FDownloadTask;

        TSharedPtr<FAsyncTask<FDownloadTask>> Download(
            FString DataObjectId
        );
    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
