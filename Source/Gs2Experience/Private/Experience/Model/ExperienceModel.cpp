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

#include "Experience/Model/ExperienceModel.h"

namespace Gs2::Experience::Model
{
    FExperienceModel::FExperienceModel():
        ExperienceModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultExperienceValue(TOptional<int64>()),
        DefaultRankCapValue(TOptional<int64>()),
        MaxRankCapValue(TOptional<int64>()),
        RankThresholdValue(nullptr)
    {
    }

    FExperienceModel::FExperienceModel(
        const FExperienceModel& From
    ):
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DefaultExperienceValue(From.DefaultExperienceValue),
        DefaultRankCapValue(From.DefaultRankCapValue),
        MaxRankCapValue(From.MaxRankCapValue),
        RankThresholdValue(From.RankThresholdValue)
    {
    }

    TSharedPtr<FExperienceModel> FExperienceModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModel> FExperienceModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModel> FExperienceModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModel> FExperienceModel::WithDefaultExperience(
        const TOptional<int64> DefaultExperience
    )
    {
        this->DefaultExperienceValue = DefaultExperience;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModel> FExperienceModel::WithDefaultRankCap(
        const TOptional<int64> DefaultRankCap
    )
    {
        this->DefaultRankCapValue = DefaultRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModel> FExperienceModel::WithMaxRankCap(
        const TOptional<int64> MaxRankCap
    )
    {
        this->MaxRankCapValue = MaxRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FExperienceModel> FExperienceModel::WithRankThreshold(
        const TSharedPtr<FThreshold> RankThreshold
    )
    {
        this->RankThresholdValue = RankThreshold;
        return SharedThis(this);
    }
    TOptional<FString> FExperienceModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TOptional<FString> FExperienceModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FExperienceModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FExperienceModel::GetDefaultExperience() const
    {
        return DefaultExperienceValue;
    }

    FString FExperienceModel::GetDefaultExperienceString() const
    {
        if (!DefaultExperienceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue());
    }
    TOptional<int64> FExperienceModel::GetDefaultRankCap() const
    {
        return DefaultRankCapValue;
    }

    FString FExperienceModel::GetDefaultRankCapString() const
    {
        if (!DefaultRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue());
    }
    TOptional<int64> FExperienceModel::GetMaxRankCap() const
    {
        return MaxRankCapValue;
    }

    FString FExperienceModel::GetMaxRankCapString() const
    {
        if (!MaxRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue());
    }
    TSharedPtr<FThreshold> FExperienceModel::GetRankThreshold() const
    {
        return RankThresholdValue;
    }

    TOptional<FString> FExperienceModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FExperienceModel::GetExperienceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):experience:(?<namespaceName>.+):model:(?<experienceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FExperienceModel> FExperienceModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FExperienceModel>()
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("experienceModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDefaultExperience(Data->HasField("defaultExperience") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("defaultExperience", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithDefaultRankCap(Data->HasField("defaultRankCap") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("defaultRankCap", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithMaxRankCap(Data->HasField("maxRankCap") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("maxRankCap", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRankThreshold(Data->HasField("rankThreshold") ? [Data]() -> Model::FThresholdPtr
                {
                    if (Data->HasTypedField<EJson::Null>("rankThreshold"))
                    {
                        return nullptr;
                    }
                    return Model::FThreshold::FromJson(Data->GetObjectField("rankThreshold"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FExperienceModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DefaultExperienceValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultExperience", FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue()));
        }
        if (DefaultRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultRankCap", FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue()));
        }
        if (MaxRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField("maxRankCap", FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue()));
        }
        if (RankThresholdValue != nullptr && RankThresholdValue.IsValid())
        {
            JsonRootObject->SetObjectField("rankThreshold", RankThresholdValue->ToJson());
        }
        return JsonRootObject;
    }

    FString FExperienceModel::TypeName = "ExperienceModel";
}