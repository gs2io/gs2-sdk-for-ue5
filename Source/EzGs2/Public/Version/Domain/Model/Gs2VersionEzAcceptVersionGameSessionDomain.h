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
#include "Version/Domain/Model/AcceptVersionAccessToken.h"
#include "Version/Model/Gs2VersionEzVersion.h"
#include "Version/Model/Gs2VersionEzVersionModel.h"
#include "Version/Model/Gs2VersionEzAcceptVersion.h"
#include "Version/Model/Gs2VersionEzStatus.h"
#include "Version/Model/Gs2VersionEzTargetVersion.h"
#include "Gs2VersionEzAcceptVersionGameSessionDomain.h"
#include "Version/Domain/Iterator/Gs2VersionEzDescribeAcceptVersionsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Version::Domain::Model
{

    class EZGS2_API FEzAcceptVersionGameSessionDomain final :
        public TSharedFromThis<FEzAcceptVersionGameSessionDomain>
    {
        Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> VersionName() const;

        FEzAcceptVersionGameSessionDomain(
            Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FAcceptTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            TSharedPtr<FEzAcceptVersionGameSessionDomain> Self;

        public:
            explicit FAcceptTask(
                TSharedPtr<FEzAcceptVersionGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
            ) override;
        };
        friend FAcceptTask;

        TSharedPtr<FAsyncTask<FAcceptTask>> Accept(
        );

        class FDeleteTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            TSharedPtr<FEzAcceptVersionGameSessionDomain> Self;

        public:
            explicit FDeleteTask(
                TSharedPtr<FEzAcceptVersionGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzAcceptVersionGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Model::FEzAcceptVersion>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAcceptVersionGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAcceptVersionGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Version::Model::FEzAcceptVersionPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzAcceptVersionGameSessionDomain> FEzAcceptVersionGameSessionDomainPtr;
}
