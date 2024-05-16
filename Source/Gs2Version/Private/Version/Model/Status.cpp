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

#include "Version/Model/Status.h"

namespace Gs2::Version::Model
{
    FStatus::FStatus():
        VersionModelValue(nullptr),
        CurrentVersionValue(nullptr)
    {
    }

    FStatus::FStatus(
        const FStatus& From
    ):
        VersionModelValue(From.VersionModelValue),
        CurrentVersionValue(From.CurrentVersionValue)
    {
    }

    TSharedPtr<FStatus> FStatus::WithVersionModel(
        const TSharedPtr<FVersionModel> VersionModel
    )
    {
        this->VersionModelValue = VersionModel;
        return SharedThis(this);
    }

    TSharedPtr<FStatus> FStatus::WithCurrentVersion(
        const TSharedPtr<FVersion> CurrentVersion
    )
    {
        this->CurrentVersionValue = CurrentVersion;
        return SharedThis(this);
    }
    TSharedPtr<FVersionModel> FStatus::GetVersionModel() const
    {
        return VersionModelValue;
    }
    TSharedPtr<FVersion> FStatus::GetCurrentVersion() const
    {
        return CurrentVersionValue;
    }

    TSharedPtr<FStatus> FStatus::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStatus>()
            ->WithVersionModel(Data->HasField(ANSI_TO_TCHAR("versionModel")) ? [Data]() -> Model::FVersionModelPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("versionModel")))
                    {
                        return nullptr;
                    }
                    return Model::FVersionModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("versionModel")));
                 }() : nullptr)
            ->WithCurrentVersion(Data->HasField(ANSI_TO_TCHAR("currentVersion")) ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("currentVersion")))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("currentVersion")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FStatus::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (VersionModelValue != nullptr && VersionModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("versionModel", VersionModelValue->ToJson());
        }
        if (CurrentVersionValue != nullptr && CurrentVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("currentVersion", CurrentVersionValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FStatus::TypeName = "Status";
}