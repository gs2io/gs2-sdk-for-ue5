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
#include "Version/Domain/Model/Checker.h"
#include "Version/Model/Gs2VersionEzVersion.h"
#include "Version/Model/Gs2VersionEzVersionModel.h"
#include "Version/Model/Gs2VersionEzAcceptVersion.h"
#include "Version/Model/Gs2VersionEzStatus.h"
#include "Version/Model/Gs2VersionEzTargetVersion.h"
#include "Gs2VersionEzCheckerDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Version::Domain::Model
{

    class EZGS2_API FEzCheckerDomain final :
        public TSharedFromThis<FEzCheckerDomain>
    {
        Gs2::Version::Domain::Model::FCheckerDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> ProjectToken() const;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> Warnings() const;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> Errors() const;
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzCheckerDomain(
            Gs2::Version::Domain::Model::FCheckerDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

    };
    typedef TSharedPtr<FEzCheckerDomain> FEzCheckerDomainPtr;
}
