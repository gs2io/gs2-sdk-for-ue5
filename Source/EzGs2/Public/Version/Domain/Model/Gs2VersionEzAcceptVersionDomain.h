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
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Model/Gs2VersionEzVersion.h"
#include "Version/Model/Gs2VersionEzVersionModel.h"
#include "Version/Model/Gs2VersionEzAcceptVersion.h"
#include "Version/Model/Gs2VersionEzStatus.h"
#include "Version/Model/Gs2VersionEzTargetVersion.h"
#include "Gs2VersionEzAcceptVersionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Version::Domain::Model
{

    class EZGS2_API FEzAcceptVersionDomain final :
        public TSharedFromThis<FEzAcceptVersionDomain>
    {
        Gs2::Version::Domain::Model::FAcceptVersionDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> VersionName() const;

        FEzAcceptVersionDomain(
            Gs2::Version::Domain::Model::FAcceptVersionDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Model::FEzAcceptVersion>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAcceptVersionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAcceptVersionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Version::Model::FEzAcceptVersionPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Version::Model::FEzAcceptVersionPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzAcceptVersionDomain> FEzAcceptVersionDomainPtr;
}
