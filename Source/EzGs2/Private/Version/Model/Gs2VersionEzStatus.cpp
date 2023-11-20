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

#include "Version/Model/Gs2VersionEzStatus.h"

namespace Gs2::UE5::Version::Model
{

    TSharedPtr<FEzStatus> FEzStatus::WithVersionModel(
        const TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModel> VersionModel
    )
    {
        this->VersionModelValue = VersionModel;
        return SharedThis(this);
    }

    TSharedPtr<FEzStatus> FEzStatus::WithCurrentVersion(
        const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> CurrentVersion
    )
    {
        this->CurrentVersionValue = CurrentVersion;
        return SharedThis(this);
    }
    TSharedPtr<Gs2::UE5::Version::Model::FEzVersionModel> FEzStatus::GetVersionModel() const
    {
        return VersionModelValue;
    }
    TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> FEzStatus::GetCurrentVersion() const
    {
        return CurrentVersionValue;
    }

    Gs2::Version::Model::FStatusPtr FEzStatus::ToModel() const
    {
        return MakeShared<Gs2::Version::Model::FStatus>()
            ->WithVersionModel(VersionModelValue == nullptr ? nullptr : VersionModelValue->ToModel())
            ->WithCurrentVersion(CurrentVersionValue == nullptr ? nullptr : CurrentVersionValue->ToModel());
    }

    TSharedPtr<FEzStatus> FEzStatus::FromModel(const Gs2::Version::Model::FStatusPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStatus>()
            ->WithVersionModel(Model->GetVersionModel() != nullptr ? Gs2::UE5::Version::Model::FEzVersionModel::FromModel(Model->GetVersionModel()) : nullptr)
            ->WithCurrentVersion(Model->GetCurrentVersion() != nullptr ? Gs2::UE5::Version::Model::FEzVersion::FromModel(Model->GetCurrentVersion()) : nullptr);
    }
}