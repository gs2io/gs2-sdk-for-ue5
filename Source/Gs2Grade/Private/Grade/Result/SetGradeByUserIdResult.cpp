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

#include "Grade/Result/SetGradeByUserIdResult.h"

namespace Gs2::Grade::Result
{
    FSetGradeByUserIdResult::FSetGradeByUserIdResult():
        ItemValue(nullptr),
        OldValue(nullptr),
        ExperienceNamespaceNameValue(TOptional<FString>()),
        ExperienceStatusValue(nullptr)
    {
    }

    FSetGradeByUserIdResult::FSetGradeByUserIdResult(
        const FSetGradeByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue),
        ExperienceNamespaceNameValue(From.ExperienceNamespaceNameValue),
        ExperienceStatusValue(From.ExperienceStatusValue)
    {
    }

    TSharedPtr<FSetGradeByUserIdResult> FSetGradeByUserIdResult::WithItem(
        const TSharedPtr<Model::FStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetGradeByUserIdResult> FSetGradeByUserIdResult::WithOld(
        const TSharedPtr<Model::FStatus> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<FSetGradeByUserIdResult> FSetGradeByUserIdResult::WithExperienceNamespaceName(
        const TOptional<FString> ExperienceNamespaceName
    )
    {
        this->ExperienceNamespaceNameValue = ExperienceNamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetGradeByUserIdResult> FSetGradeByUserIdResult::WithExperienceStatus(
        const TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatus
    )
    {
        this->ExperienceStatusValue = ExperienceStatus;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStatus> FSetGradeByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FStatus> FSetGradeByUserIdResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TOptional<FString> FSetGradeByUserIdResult::GetExperienceNamespaceName() const
    {
        return ExperienceNamespaceNameValue;
    }

    TSharedPtr<Gs2::Experience::Model::FStatus> FSetGradeByUserIdResult::GetExperienceStatus() const
    {
        if (!ExperienceStatusValue.IsValid())
        {
            return nullptr;
        }
        return ExperienceStatusValue;
    }

    TSharedPtr<FSetGradeByUserIdResult> FSetGradeByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetGradeByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithOld(Data->HasField(ANSI_TO_TCHAR("old")) ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("old")))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("old")));
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

    TSharedPtr<FJsonObject> FSetGradeByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (OldValue != nullptr && OldValue.IsValid())
        {
            JsonRootObject->SetObjectField("old", OldValue->ToJson());
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