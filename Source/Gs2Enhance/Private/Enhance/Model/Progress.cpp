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

#include "Enhance/Model/Progress.h"

namespace Gs2::Enhance::Model
{
    FProgress::FProgress():
        ProgressIdValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        PropertyIdValue(TOptional<FString>()),
        ExperienceValueValue(TOptional<int64>()),
        RateValue(TOptional<float>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FProgress::FProgress(
        const FProgress& From
    ):
        ProgressIdValue(From.ProgressIdValue),
        UserIdValue(From.UserIdValue),
        RateNameValue(From.RateNameValue),
        NameValue(From.NameValue),
        PropertyIdValue(From.PropertyIdValue),
        ExperienceValueValue(From.ExperienceValueValue),
        RateValue(From.RateValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FProgress> FProgress::WithProgressId(
        const TOptional<FString> ProgressId
    )
    {
        this->ProgressIdValue = ProgressId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithPropertyId(
        const TOptional<FString> PropertyId
    )
    {
        this->PropertyIdValue = PropertyId;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithExperienceValue(
        const TOptional<int64> ExperienceValue
    )
    {
        this->ExperienceValueValue = ExperienceValue;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FProgress> FProgress::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FProgress::GetProgressId() const
    {
        return ProgressIdValue;
    }
    TOptional<FString> FProgress::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FProgress::GetRateName() const
    {
        return RateNameValue;
    }
    TOptional<FString> FProgress::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FProgress::GetPropertyId() const
    {
        return PropertyIdValue;
    }
    TOptional<int64> FProgress::GetExperienceValue() const
    {
        return ExperienceValueValue;
    }

    FString FProgress::GetExperienceValueString() const
    {
        if (!ExperienceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExperienceValueValue.GetValue());
    }
    TOptional<float> FProgress::GetRate() const
    {
        return RateValue;
    }

    FString FProgress::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }
    TOptional<int64> FProgress::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FProgress::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FProgress::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FProgress::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FProgress::GetRevision() const
    {
        return RevisionValue;
    }

    FString FProgress::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FProgress::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FProgress::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):enhance:(?<namespaceName>.+):user:(?<userId>.+):progress"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FProgress> FProgress::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FProgress>()
            ->WithProgressId(Data->HasField("progressId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("progressId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRateName(Data->HasField("rateName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("rateName", v))
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
            ->WithPropertyId(Data->HasField("propertyId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("propertyId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExperienceValue(Data->HasField("experienceValue") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("experienceValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRate(Data->HasField("rate") ? [Data]() -> TOptional<float>
                {
                    float v;
                    if (Data->TryGetNumberField("rate", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<float>();
                }() : TOptional<float>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FProgress::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ProgressIdValue.IsSet())
        {
            JsonRootObject->SetStringField("progressId", ProgressIdValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (RateNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rateName", RateNameValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (PropertyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyId", PropertyIdValue.GetValue());
        }
        if (ExperienceValueValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceValue", FString::Printf(TEXT("%lld"), ExperienceValueValue.GetValue()));
        }
        if (RateValue.IsSet())
        {
            JsonRootObject->SetNumberField("rate", RateValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FProgress::TypeName = "Progress";
}