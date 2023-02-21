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
#include "Version/Model/Status.h"
#include "Gs2VersionEzVersionModel.h"
#include "Gs2VersionEzVersion.h"

namespace Gs2::UE5::Version::Model
{
	class EZGS2_API FEzStatus final : public TSharedFromThis<FEzStatus>
	{
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModel> VersionModelValue;
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> CurrentVersionValue;

	public:
        TSharedPtr<FEzStatus> WithVersionModel(const TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModel> VersionModel);
        TSharedPtr<FEzStatus> WithCurrentVersion(const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> CurrentVersion);

        TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModel> GetVersionModel() const;

        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> GetCurrentVersion() const;

        Gs2::Version::Model::FStatusPtr ToModel() const;
        static TSharedPtr<FEzStatus> FromModel(Gs2::Version::Model::FStatusPtr Model);
    };
    typedef TSharedPtr<FEzStatus> FEzStatusPtr;
}