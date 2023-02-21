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
#include "Version/Model/TargetVersion.h"
#include "Gs2VersionEzVersion.h"

namespace Gs2::UE5::Version::Model
{
	class EZGS2_API FEzTargetVersion final : public TSharedFromThis<FEzTargetVersion>
	{
        TOptional<FString> VersionNameValue;
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> VersionValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;

	public:
        TSharedPtr<FEzTargetVersion> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FEzTargetVersion> WithVersion(const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> Version);
        TSharedPtr<FEzTargetVersion> WithBody(const TOptional<FString> Body);
        TSharedPtr<FEzTargetVersion> WithSignature(const TOptional<FString> Signature);

        TOptional<FString> GetVersionName() const;

        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> GetVersion() const;

        TOptional<FString> GetBody() const;

        TOptional<FString> GetSignature() const;

        Gs2::Version::Model::FTargetVersionPtr ToModel() const;
        static TSharedPtr<FEzTargetVersion> FromModel(Gs2::Version::Model::FTargetVersionPtr Model);
    };
    typedef TSharedPtr<FEzTargetVersion> FEzTargetVersionPtr;
}