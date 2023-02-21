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
#include "Datastore/Domain/Model/DataObject.h"
#include "Datastore/Model/Gs2DatastoreEzDataObject.h"
#include "Datastore/Model/Gs2DatastoreEzDataObjectHistory.h"
#include "Gs2DatastoreEzDataObjectHistoryDomain.h"
#include "Gs2DatastoreEzDataObjectDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    class EZGS2_API FEzDataObjectDomain final :
        public TSharedFromThis<FEzDataObjectDomain>
    {
        Gs2::Datastore::Domain::Model::FDataObjectDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> UploadUrl() const;
        TOptional<FString> FileUrl() const;
        TOptional<int64> ContentLength() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> DataObjectName() const;

        FEzDataObjectDomain(
            Gs2::Datastore::Domain::Model::FDataObjectDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FPrepareDownloadByUserIdAndDataObjectNameTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectDomain>,
            public TSharedFromThis<FPrepareDownloadByUserIdAndDataObjectNameTask>
        {
            TSharedPtr<FEzDataObjectDomain> Self;

        public:
            explicit FPrepareDownloadByUserIdAndDataObjectNameTask(
                TSharedPtr<FEzDataObjectDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectDomain>> Result
            ) override;
        };
        friend FPrepareDownloadByUserIdAndDataObjectNameTask;

        TSharedPtr<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameTask>> PrepareDownloadByUserIdAndDataObjectName(
        );

        Gs2::UE5::Datastore::Domain::Model::FEzDataObjectHistoryDomainPtr DataObjectHistory(
            const FString Generation
        ) const;

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Model::FEzDataObject>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzDataObjectDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzDataObjectDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObjectPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        class FDownloadTask :
            public Gs2::Core::Util::TGs2Future<TArray<uint8>>,
            public TSharedFromThis<FDownloadTask>
        {
            TSharedPtr<FEzDataObjectDomain> Self;

        public:
            explicit FDownloadTask(
                TSharedPtr<FEzDataObjectDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<uint8>>> Result
            ) override;
        };
        friend FDownloadTask;

        TSharedPtr<FAsyncTask<FDownloadTask>> Download(
        );
    };
    typedef TSharedPtr<FEzDataObjectDomain> FEzDataObjectDomainPtr;
}
