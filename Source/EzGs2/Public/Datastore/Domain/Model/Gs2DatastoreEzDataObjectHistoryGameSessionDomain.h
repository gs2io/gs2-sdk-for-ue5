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

#pragma once

#include "CoreMinimal.h"
#include "Datastore/Domain/Model/DataObjectHistoryAccessToken.h"
#include "Datastore/Model/Gs2DatastoreEzDataObject.h"
#include "Datastore/Model/Gs2DatastoreEzDataObjectHistory.h"
#include "Gs2DatastoreEzDataObjectHistoryGameSessionDomain.h"
#include "Datastore/Domain/Iterator/Gs2DatastoreEzDescribeDataObjectHistoriesIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    class EZGS2_API FEzDataObjectHistoryGameSessionDomain final :
        public TSharedFromThis<FEzDataObjectHistoryGameSessionDomain>
    {
        Gs2::Datastore::Domain::Model::FDataObjectHistoryAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> DataObjectName() const;
        TOptional<FString> Generation() const;

        FEzDataObjectHistoryGameSessionDomain(
            Gs2::Datastore::Domain::Model::FDataObjectHistoryAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Model::FEzDataObjectHistory>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzDataObjectHistoryGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzDataObjectHistoryGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzDataObjectHistoryGameSessionDomain> FEzDataObjectHistoryGameSessionDomainPtr;
}
