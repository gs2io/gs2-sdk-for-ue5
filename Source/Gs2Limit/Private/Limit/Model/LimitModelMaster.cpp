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

#include "Limit/Model/LimitModelMaster.h"

namespace Gs2::Limit::Model
{
    FLimitModelMaster::FLimitModelMaster():
        LimitModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ResetTypeValue(TOptional<FString>()),
        ResetDayOfMonthValue(TOptional<int32>()),
        ResetDayOfWeekValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FLimitModelMaster::FLimitModelMaster(
        const FLimitModelMaster& From
    ):
        LimitModelIdValue(From.LimitModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ResetTypeValue(From.ResetTypeValue),
        ResetDayOfMonthValue(From.ResetDayOfMonthValue),
        ResetDayOfWeekValue(From.ResetDayOfWeekValue),
        ResetHourValue(From.ResetHourValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithLimitModelId(
        const TOptional<FString> LimitModelId
    )
    {
        this->LimitModelIdValue = LimitModelId;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FLimitModelMaster::GetLimitModelId() const
    {
        return LimitModelIdValue;
    }
    TOptional<FString> FLimitModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FLimitModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FLimitModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FLimitModelMaster::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<int32> FLimitModelMaster::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FLimitModelMaster::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }
    TOptional<FString> FLimitModelMaster::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }
    TOptional<int32> FLimitModelMaster::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FLimitModelMaster::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }
    TOptional<int64> FLimitModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FLimitModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FLimitModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FLimitModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FLimitModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):limit:(?<namespaceName>.+):limit:(?<limitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLimitModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):limit:(?<namespaceName>.+):limit:(?<limitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLimitModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):limit:(?<namespaceName>.+):limit:(?<limitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FLimitModelMaster::GetLimitNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):limit:(?<namespaceName>.+):limit:(?<limitName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FLimitModelMaster> FLimitModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLimitModelMaster>()
            ->WithLimitModelId(Data->HasField("limitModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("limitModelId", v))
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
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
            ->WithResetType(Data->HasField("resetType") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("resetType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetDayOfMonth(Data->HasField("resetDayOfMonth") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("resetDayOfMonth", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithResetDayOfWeek(Data->HasField("resetDayOfWeek") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("resetDayOfWeek", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResetHour(Data->HasField("resetHour") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("resetHour", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FLimitModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (LimitModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("limitModelId", LimitModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resetType", ResetTypeValue.GetValue());
        }
        if (ResetDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetDayOfMonth", ResetDayOfMonthValue.GetValue());
        }
        if (ResetDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("resetDayOfWeek", ResetDayOfWeekValue.GetValue());
        }
        if (ResetHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetHour", ResetHourValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FLimitModelMaster::TypeName = "LimitModelMaster";
}