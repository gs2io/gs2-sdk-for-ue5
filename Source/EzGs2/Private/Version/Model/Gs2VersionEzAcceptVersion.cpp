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

#include "EzGs2/Public/Version/Model/Gs2VersionEzAcceptVersion.h"

namespace Gs2::UE5::Version::Model
{

    TSharedPtr<FEzAcceptVersion> FEzAcceptVersion::WithVersionName(
        const TOptional<FString> VersionName
    )
    {
        this->VersionNameValue = VersionName;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcceptVersion> FEzAcceptVersion::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcceptVersion> FEzAcceptVersion::WithVersion(
        const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> Version
    )
    {
        this->VersionValue = Version;
        return SharedThis(this);
    }
    TOptional<FString> FEzAcceptVersion::GetVersionName() const
    {
        return VersionNameValue;
    }
    TOptional<FString> FEzAcceptVersion::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> FEzAcceptVersion::GetVersion() const
    {
        return VersionValue;
    }

    Gs2::Version::Model::FAcceptVersionPtr FEzAcceptVersion::ToModel() const
    {
        return MakeShared<Gs2::Version::Model::FAcceptVersion>()
            ->WithVersionName(VersionNameValue)
            ->WithUserId(UserIdValue)
            ->WithVersion(VersionValue == nullptr ? nullptr : VersionValue->ToModel());
    }

    TSharedPtr<FEzAcceptVersion> FEzAcceptVersion::FromModel(const Gs2::Version::Model::FAcceptVersionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAcceptVersion>()
            ->WithVersionName(Model->GetVersionName())
            ->WithUserId(Model->GetUserId())
            ->WithVersion(Model->GetVersion() != nullptr ? Gs2::UE5::Version::Model::FEzVersion::FromModel(Model->GetVersion()) : nullptr);
    }
}