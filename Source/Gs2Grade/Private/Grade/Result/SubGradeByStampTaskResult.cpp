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

#include "Grade/Result/SubGradeByStampTaskResult.h"

namespace Gs2::Grade::Result
{
    FSubGradeByStampTaskResult::FSubGradeByStampTaskResult():
        ItemValue(nullptr),
        NewContextStackValue(TOptional<FString>()),
        ExperienceNamespaceNameValue(TOptional<FString>()),
        ExperienceStatusValue(nullptr)
    {
    }

    FSubGradeByStampTaskResult::FSubGradeByStampTaskResult(
        const FSubGradeByStampTaskResult& From
    ):
        ItemValue(From.ItemValue),
        NewContextStackValue(From.NewContextStackValue),
        ExperienceNamespaceNameValue(From.ExperienceNamespaceNameValue),
        ExperienceStatusValue(From.ExperienceStatusValue)
    {
    }

    TSharedPtr<FSubGradeByStampTaskResult> FSubGradeByStampTaskResult::WithItem(
        const TSharedPtr<Model::FStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeByStampTaskResult> FSubGradeByStampTaskResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeByStampTaskResult> FSubGradeByStampTaskResult::WithExperienceNamespaceName(
        const TOptional<FString> ExperienceNamespaceName
    )
    {
        this->ExperienceNamespaceNameValue = ExperienceNamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSubGradeByStampTaskResult> FSubGradeByStampTaskResult::WithExperienceStatus(
        const TSharedPtr<Gs2::Experience::Model::FStatus> ExperienceStatus
    )
    {
        this->ExperienceStatusValue = ExperienceStatus;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStatus> FSubGradeByStampTaskResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TOptional<FString> FSubGradeByStampTaskResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TOptional<FString> FSubGradeByStampTaskResult::GetExperienceNamespaceName() const
    {
        return ExperienceNamespaceNameValue;
    }

    TSharedPtr<Gs2::Experience::Model::FStatus> FSubGradeByStampTaskResult::GetExperienceStatus() const
    {
        if (!ExperienceStatusValue.IsValid())
        {
            return nullptr;
        }
        return ExperienceStatusValue;
    }

    TSharedPtr<FSubGradeByStampTaskResult> FSubGradeByStampTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSubGradeByStampTaskResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FStatus::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithNewContextStack(Data->HasField("newContextStack") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("newContextStack", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExperienceNamespaceName(Data->HasField("experienceNamespaceName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("experienceNamespaceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExperienceStatus(Data->HasField("experienceStatus") ? [Data]() -> Gs2::Experience::Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("experienceStatus"))
                    {
                        return nullptr;
                    }
                    return Gs2::Experience::Model::FStatus::FromJson(Data->GetObjectField("experienceStatus"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSubGradeByStampTaskResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (NewContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("newContextStack", NewContextStackValue.GetValue());
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