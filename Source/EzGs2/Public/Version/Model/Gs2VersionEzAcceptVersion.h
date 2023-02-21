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
#include "Version/Model/AcceptVersion.h"
#include "Gs2VersionEzVersion.h"

namespace Gs2::UE5::Version::Model
{
	class EZGS2_API FEzAcceptVersion final : public TSharedFromThis<FEzAcceptVersion>
	{
        TOptional<FString> VersionNameValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> VersionValue;

	public:
        TSharedPtr<FEzAcceptVersion> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FEzAcceptVersion> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzAcceptVersion> WithVersion(const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> Version);

        TOptional<FString> GetVersionName() const;

        TOptional<FString> GetUserId() const;

        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> GetVersion() const;

        Gs2::Version::Model::FAcceptVersionPtr ToModel() const;
        static TSharedPtr<FEzAcceptVersion> FromModel(Gs2::Version::Model::FAcceptVersionPtr Model);
    };
    typedef TSharedPtr<FEzAcceptVersion> FEzAcceptVersionPtr;
}