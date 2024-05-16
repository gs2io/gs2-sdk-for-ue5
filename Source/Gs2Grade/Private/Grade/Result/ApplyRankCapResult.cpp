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

#include "Grade/Result/ApplyRankCapResult.h"

namespace Gs2::Grade::Result
{
    FApplyRankCapResult::FApplyRankCapResult():
        ItemValue(nullptr),
        ExperienceNamespaceNameValue(TOptional<FString>()),
        ExperienceStatusValue(nullptr)
    {
    }

    FApplyRankCapResult::FApplyRankCapResult(
        const FApplyRankCapResult& From
    ):
        ItemValue(From.ItemValue),
        ExperienceNamespaceNameValue(From.ExperienceNamespaceNameValue),
        ExperienceStatusValue(From.ExperienceStatusValue)
    {
    }

    TSharedPtr<FApplyRankCapResult> FApplyRankCapResult::WithItem(
        const TSharedPtr<Model::FStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FApplyRankCapResult> FApplyRankCapResult::WithExperienceNamespaceName(
        const TOptional<FString> ExperienceNamespaceName
    )
    {
        this->ExperienceNamespaceNameValue = ExperienceNamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FApplyRankCapResult> FApplyRankCapResult::WithExperienceStatus(
        const TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatus
    )
    {
        this->ExperienceStatusValue = ExperienceStatus;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStatus> FApplyRankCapResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FApplyRankCapResult::GetExperienceNamespaceName() const
    {
        return ExperienceNamespaceNameValue;
    }

    TSharedPtr<Gs2::Experience::Model::FStatus> FApplyRankCapResult::GetExperienceStatus() const
    {
        if (!ExperienceStatusValue.IsValid())
        {
            return nullptr;
        }
        return ExperienceStatusValue;
    }

    TSharedPtr<FApplyRankCapResult> FApplyRankCapResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FApplyRankCapResult>()
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

    TSharedPtr<FJsonObject> FApplyRankCapResult::ToJson() const
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