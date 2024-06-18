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

#include "Buff/Model/BuffEntryModel.h"

namespace Gs2::Buff::Model
{
    FBuffEntryModel::FBuffEntryModel():
        BuffEntryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ExpressionValue(TOptional<FString>()),
        TargetTypeValue(TOptional<FString>()),
        TargetModelValue(nullptr),
        TargetActionValue(nullptr),
        PriorityValue(TOptional<int32>()),
        ApplyPeriodScheduleEventIdValue(TOptional<FString>())
    {
    }

    FBuffEntryModel::FBuffEntryModel(
        const FBuffEntryModel& From
    ):
        BuffEntryModelIdValue(From.BuffEntryModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ExpressionValue(From.ExpressionValue),
        TargetTypeValue(From.TargetTypeValue),
        TargetModelValue(From.TargetModelValue),
        TargetActionValue(From.TargetActionValue),
        PriorityValue(From.PriorityValue),
        ApplyPeriodScheduleEventIdValue(From.ApplyPeriodScheduleEventIdValue)
    {
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithBuffEntryModelId(
        const TOptional<FString> BuffEntryModelId
    )
    {
        this->BuffEntryModelIdValue = BuffEntryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithExpression(
        const TOptional<FString> Expression
    )
    {
        this->ExpressionValue = Expression;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithTargetType(
        const TOptional<FString> TargetType
    )
    {
        this->TargetTypeValue = TargetType;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithTargetModel(
        const TSharedPtr<FBuffTargetModel> TargetModel
    )
    {
        this->TargetModelValue = TargetModel;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithTargetAction(
        const TSharedPtr<FBuffTargetAction> TargetAction
    )
    {
        this->TargetActionValue = TargetAction;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithPriority(
        const TOptional<int32> Priority
    )
    {
        this->PriorityValue = Priority;
        return SharedThis(this);
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::WithApplyPeriodScheduleEventId(
        const TOptional<FString> ApplyPeriodScheduleEventId
    )
    {
        this->ApplyPeriodScheduleEventIdValue = ApplyPeriodScheduleEventId;
        return SharedThis(this);
    }
    TOptional<FString> FBuffEntryModel::GetBuffEntryModelId() const
    {
        return BuffEntryModelIdValue;
    }
    TOptional<FString> FBuffEntryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FBuffEntryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FBuffEntryModel::GetExpression() const
    {
        return ExpressionValue;
    }
    TOptional<FString> FBuffEntryModel::GetTargetType() const
    {
        return TargetTypeValue;
    }
    TSharedPtr<FBuffTargetModel> FBuffEntryModel::GetTargetModel() const
    {
        return TargetModelValue;
    }
    TSharedPtr<FBuffTargetAction> FBuffEntryModel::GetTargetAction() const
    {
        return TargetActionValue;
    }
    TOptional<int32> FBuffEntryModel::GetPriority() const
    {
        return PriorityValue;
    }

    FString FBuffEntryModel::GetPriorityString() const
    {
        if (!PriorityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), PriorityValue.GetValue());
    }
    TOptional<FString> FBuffEntryModel::GetApplyPeriodScheduleEventId() const
    {
        return ApplyPeriodScheduleEventIdValue;
    }

    TOptional<FString> FBuffEntryModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBuffEntryModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBuffEntryModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBuffEntryModel::GetBuffEntryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):buff:(?<namespaceName>.+):model:(?<buffEntryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FBuffEntryModel> FBuffEntryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBuffEntryModel>()
            ->WithBuffEntryModelId(Data->HasField(ANSI_TO_TCHAR("buffEntryModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("buffEntryModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpression(Data->HasField(ANSI_TO_TCHAR("expression")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("expression"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetType(Data->HasField(ANSI_TO_TCHAR("targetType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetModel(Data->HasField(ANSI_TO_TCHAR("targetModel")) ? [Data]() -> Model::FBuffTargetModelPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetModel")))
                    {
                        return nullptr;
                    }
                    return Model::FBuffTargetModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetModel")));
                 }() : nullptr)
            ->WithTargetAction(Data->HasField(ANSI_TO_TCHAR("targetAction")) ? [Data]() -> Model::FBuffTargetActionPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("targetAction")))
                    {
                        return nullptr;
                    }
                    return Model::FBuffTargetAction::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("targetAction")));
                 }() : nullptr)
            ->WithPriority(Data->HasField(ANSI_TO_TCHAR("priority")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("priority"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithApplyPeriodScheduleEventId(Data->HasField(ANSI_TO_TCHAR("applyPeriodScheduleEventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("applyPeriodScheduleEventId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FBuffEntryModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (BuffEntryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("buffEntryModelId", BuffEntryModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ExpressionValue.IsSet())
        {
            JsonRootObject->SetStringField("expression", ExpressionValue.GetValue());
        }
        if (TargetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("targetType", TargetTypeValue.GetValue());
        }
        if (TargetModelValue != nullptr && TargetModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("targetModel", TargetModelValue->ToJson());
        }
        if (TargetActionValue != nullptr && TargetActionValue.IsValid())
        {
            JsonRootObject->SetObjectField("targetAction", TargetActionValue->ToJson());
        }
        if (PriorityValue.IsSet())
        {
            JsonRootObject->SetNumberField("priority", PriorityValue.GetValue());
        }
        if (ApplyPeriodScheduleEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("applyPeriodScheduleEventId", ApplyPeriodScheduleEventIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FBuffEntryModel::TypeName = "BuffEntryModel";
}