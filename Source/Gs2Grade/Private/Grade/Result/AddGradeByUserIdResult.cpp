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

#include "Grade/Result/AddGradeByUserIdResult.h"

namespace Gs2::Grade::Result
{
    FAddGradeByUserIdResult::FAddGradeByUserIdResult():
        ItemValue(nullptr),
        ExperienceNamespaceNameValue(TOptional<FString>()),
        ExperienceStatusValue(nullptr)
    {
    }

    FAddGradeByUserIdResult::FAddGradeByUserIdResult(
        const FAddGradeByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        ExperienceNamespaceNameValue(From.ExperienceNamespaceNameValue),
        ExperienceStatusValue(From.ExperienceStatusValue)
    {
    }

    TSharedPtr<FAddGradeByUserIdResult> FAddGradeByUserIdResult::WithItem(
        const TSharedPtr<Model::FStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAddGradeByUserIdResult> FAddGradeByUserIdResult::WithExperienceNamespaceName(
        const TOptional<FString> ExperienceNamespaceName
    )
    {
        this->ExperienceNamespaceNameValue = ExperienceNamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FAddGradeByUserIdResult> FAddGradeByUserIdResult::WithExperienceStatus(
        const TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatus
    )
    {
        this->ExperienceStatusValue = ExperienceStatus;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStatus> FAddGradeByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FAddGradeByUserIdResult::GetExperienceNamespaceName() const
    {
        return ExperienceNamespaceNameValue;
    }

    TSharedPtr<Gs2::Experience::Model::FStatus> FAddGradeByUserIdResult::GetExperienceStatus() const
    {
        if (!ExperienceStatusValue.IsValid())
        {
            return nullptr;
        }
        return ExperienceStatusValue;
    }

    TSharedPtr<FAddGradeByUserIdResult> FAddGradeByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAddGradeByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithExperienceNamespaceName(Data->HasField(ANSI_TO_TCHAR("experienceNamespaceName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("experienceNamespaceName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExperienceStatus(Data->HasField(ANSI_TO_TCHAR("experienceStatus")) ? [Data]() -> Gs2::Experience::Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("experienceStatus")))
                    {
                        return nullptr;
                    }
                    return Gs2::Experience::Model::FStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("experienceStatus")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FAddGradeByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (ExperienceNamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceNamespaceName", ExperienceNamespaceNameValue.GetValue());
        }
        if (ExperienceStatusValue != nullptr && ExperienceStatusValue.IsValid())
        {
            JsonRootObject->SetObjectField("experienceStatus", ExperienceStatusValue->ToJson());
        }
        return JsonRootObject;
    }
}