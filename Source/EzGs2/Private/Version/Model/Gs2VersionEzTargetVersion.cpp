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

#include "EzGs2/Public/Version/Model/Gs2VersionEzTargetVersion.h"

namespace Gs2::UE5::Version::Model
{

    TSharedPtr<FEzTargetVersion> FEzTargetVersion::WithVersionName(
        const TOptional<FString> VersionName
    )
    {
        this->VersionNameValue = VersionName;
        return SharedThis(this);
    }

    TSharedPtr<FEzTargetVersion> FEzTargetVersion::WithVersion(
        const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }

    TSharedPtr<FEzTargetVersion> FEzTargetVersion::WithBody(
        const TOptional<FString> Body
    )
    {
        this->BodyValue = Body;
        return SharedThis(this);
    }

    TSharedPtr<FEzTargetVersion> FEzTargetVersion::WithSignature(
        const TOptional<FString> Signature
    )
    {
        this->SignatureValue = Signature;
        return SharedThis(this);
    }
    TOptional<FString> FEzTargetVersion::GetVersionName() const
    {
        return VersionNameValue;
    }
    TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> FEzTargetVersion::GetVersion() const
    {
        return VersionValue;
    }
    TOptional<FString> FEzTargetVersion::GetBody() const
    {
        return BodyValue;
    }
    TOptional<FString> FEzTargetVersion::GetSignature() const
    {
        return SignatureValue;
    }

    Gs2::Version::Model::FTargetVersionPtr FEzTargetVersion::ToModel() const
    {
        return MakeShared<Gs2::Version::Model::FTargetVersion>()
            ->WithVersionName(VersionNameValue)
            ->WithVersion(VersionValue == nullptr ? nullptr : VersionValue->ToModel())
            ->WithBody(BodyValue)
            ->WithSignature(SignatureValue);
    }

    TSharedPtr<FEzTargetVersion> FEzTargetVersion::FromModel(const Gs2::Version::Model::FTargetVersionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzTargetVersion>()
            ->WithVersionName(Model->GetVersionName())
            ->WithVersion(Model->GetVersion() != nullptr ? Gs2::UE5::Version::Model::FEzVersion::FromModel(Model->GetVersion()) : nullptr)
            ->WithBody(Model->GetBody())
            ->WithSignature(Model->GetSignature());
    }
}