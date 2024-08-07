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

#include "SkillTree/Model/NodeModel.h"

namespace Gs2::SkillTree::Model
{
    FNodeModel::FNodeModel():
        NodeModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ReleaseVerifyActionsValue(nullptr),
        ReleaseConsumeActionsValue(nullptr),
        ReturnAcquireActionsValue(nullptr),
        RestrainReturnRateValue(TOptional<float>()),
        PremiseNodeNamesValue(nullptr)
    {
    }

    FNodeModel::FNodeModel(
        const FNodeModel& From
    ):
        NodeModelIdValue(From.NodeModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ReleaseVerifyActionsValue(From.ReleaseVerifyActionsValue),
        ReleaseConsumeActionsValue(From.ReleaseConsumeActionsValue),
        ReturnAcquireActionsValue(From.ReturnAcquireActionsValue),
        RestrainReturnRateValue(From.RestrainReturnRateValue),
        PremiseNodeNamesValue(From.PremiseNodeNamesValue)
    {
    }

    TSharedPtr<FNodeModel> FNodeModel::WithNodeModelId(
        const TOptional<FString> NodeModelId
    )
    {
        this->NodeModelIdValue = NodeModelId;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModel> FNodeModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModel> FNodeModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModel> FNodeModel::WithReleaseVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> ReleaseVerifyActions
    )
    {
        this->ReleaseVerifyActionsValue = ReleaseVerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModel> FNodeModel::WithReleaseConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> ReleaseConsumeActions
    )
    {
        this->ReleaseConsumeActionsValue = ReleaseConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModel> FNodeModel::WithReturnAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> ReturnAcquireActions
    )
    {
        this->ReturnAcquireActionsValue = ReturnAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModel> FNodeModel::WithRestrainReturnRate(
        const TOptional<float> RestrainReturnRate
    )
    {
        this->RestrainReturnRateValue = RestrainReturnRate;
        return SharedThis(this);
    }

    TSharedPtr<FNodeModel> FNodeModel::WithPremiseNodeNames(
        const TSharedPtr<TArray<FString>> PremiseNodeNames
    )
    {
        this->PremiseNodeNamesValue = PremiseNodeNames;
        return SharedThis(this);
    }
    TOptional<FString> FNodeModel::GetNodeModelId() const
    {
        return NodeModelIdValue;
    }
    TOptional<FString> FNodeModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNodeModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FVerifyAction>>> FNodeModel::GetReleaseVerifyActions() const
    {
        return ReleaseVerifyActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FConsumeAction>>> FNodeModel::GetReleaseConsumeActions() const
    {
        return ReleaseConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FAcquireAction>>> FNodeModel::GetReturnAcquireActions() const
    {
        return ReturnAcquireActionsValue;
    }
    TOptional<float> FNodeModel::GetRestrainReturnRate() const
    {
        return RestrainReturnRateValue;
    }

    FString FNodeModel::GetRestrainReturnRateString() const
    {
        if (!RestrainReturnRateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RestrainReturnRateValue.GetValue());
    }
    TSharedPtr<TArray<FString>> FNodeModel::GetPremiseNodeNames() const
    {
        return PremiseNodeNamesValue;
    }

    TOptional<FString> FNodeModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNodeModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNodeModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNodeModel::GetNodeModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):skillTree:(?<namespaceName>.+):model:(?<nodeModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNodeModel> FNodeModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNodeModel>()
            ->WithNodeModelId(Data->HasField(ANSI_TO_TCHAR("nodeModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("nodeModelId"), v))
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
            ->WithReleaseVerifyActions(Data->HasField(ANSI_TO_TCHAR("releaseVerifyActions")) ? [Data]() -> TSharedPtr<TArray<Model::FVerifyActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FVerifyActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("releaseVerifyActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("releaseVerifyActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("releaseVerifyActions")))
                        {
                            v->Add(Model::FVerifyAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FVerifyActionPtr>>())
            ->WithReleaseConsumeActions(Data->HasField(ANSI_TO_TCHAR("releaseConsumeActions")) ? [Data]() -> TSharedPtr<TArray<Model::FConsumeActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FConsumeActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("releaseConsumeActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("releaseConsumeActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("releaseConsumeActions")))
                        {
                            v->Add(Model::FConsumeAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FConsumeActionPtr>>())
            ->WithReturnAcquireActions(Data->HasField(ANSI_TO_TCHAR("returnAcquireActions")) ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FAcquireActionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("returnAcquireActions")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("returnAcquireActions")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("returnAcquireActions")))
                        {
                            v->Add(Model::FAcquireAction::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FAcquireActionPtr>>())
            ->WithRestrainReturnRate(Data->HasField(ANSI_TO_TCHAR("restrainReturnRate")) ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("restrainReturnRate"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithPremiseNodeNames(Data->HasField(ANSI_TO_TCHAR("premiseNodeNames")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("premiseNodeNames")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("premiseNodeNames")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("premiseNodeNames")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FNodeModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NodeModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("nodeModelId", NodeModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ReleaseVerifyActionsValue != nullptr && ReleaseVerifyActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReleaseVerifyActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("releaseVerifyActions", v);
        }
        if (ReleaseConsumeActionsValue != nullptr && ReleaseConsumeActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReleaseConsumeActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("releaseConsumeActions", v);
        }
        if (ReturnAcquireActionsValue != nullptr && ReturnAcquireActionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ReturnAcquireActionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("returnAcquireActions", v);
        }
        if (RestrainReturnRateValue.IsSet())
        {
            JsonRootObject->SetNumberField("restrainReturnRate", RestrainReturnRateValue.GetValue());
        }
        if (PremiseNodeNamesValue != nullptr && PremiseNodeNamesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *PremiseNodeNamesValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("premiseNodeNames", v);
        }
        return JsonRootObject;
    }

    FString FNodeModel::TypeName = "NodeModel";
}