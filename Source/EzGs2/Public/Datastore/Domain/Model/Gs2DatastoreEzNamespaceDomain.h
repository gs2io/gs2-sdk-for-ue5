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
#include "Datastore/Domain/Model/Namespace.h"
#include "Datastore/Model/Gs2DatastoreEzDataObject.h"
#include "Datastore/Model/Gs2DatastoreEzDataObjectHistory.h"
#include "Gs2DatastoreEzUserDomain.h"
#include "Gs2DatastoreEzUserDomain.h"
#include "Gs2DatastoreEzUserGameSessionDomain.h"
#include "Gs2DatastoreEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Datastore::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Datastore::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Datastore::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FRestoreDataObjectTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectDomain>,
            public TSharedFromThis<FRestoreDataObjectTask>
        {
            TSharedPtr<FEzNamespaceDomain> Self;
            FString DataObjectId;

        public:
            explicit FRestoreDataObjectTask(
                TSharedPtr<FEzNamespaceDomain> Self,
                FString DataObjectId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Domain::Model::FEzDataObjectDomain>> Result
            ) override;
        };
        friend FRestoreDataObjectTask;

        TSharedPtr<FAsyncTask<FRestoreDataObjectTask>> RestoreDataObject(
            FString DataObjectId
        );

        Gs2::UE5::Datastore::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Datastore::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
