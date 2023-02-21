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

#include "Matchmaking/Model/RatingModelMaster.h"

namespace Gs2::Matchmaking::Model
{
    FRatingModelMaster::FRatingModelMaster():
        RatingModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        VolatilityValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FRatingModelMaster::FRatingModelMaster(
        const FRatingModelMaster& From
    ):
        RatingModelIdValue(From.RatingModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        VolatilityValue(From.VolatilityValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::WithRatingModelId(
        const TOptional<FString> RatingModelId
    )
    {
        this->RatingModelIdValue = RatingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::WithVolatility(
        const TOptional<int32> Volatility
    )
    {
        this->VolatilityValue = Volatility;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FRatingModelMaster::GetRatingModelId() const
    {
        return RatingModelIdValue;
    }
    TOptional<FString> FRatingModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRatingModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FRatingModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<int32> FRatingModelMaster::GetVolatility() const
    {
        return VolatilityValue;
    }

    FString FRatingModelMaster::GetVolatilityString() const
    {
        if (!VolatilityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), VolatilityValue.GetValue());
    }
    TOptional<int64> FRatingModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FRatingModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FRatingModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FRatingModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FRatingModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRatingModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRatingModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRatingModelMaster::GetRatingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRatingModelMaster> FRatingModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRatingModelMaster>()
            ->WithRatingModelId(Data->HasField("ratingModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("ratingModelId", v))
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithVolatility(Data->HasField("volatility") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("volatility", v))
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

    TSharedPtr<FJsonObject> FRatingModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RatingModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("ratingModelId", RatingModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (VolatilityValue.IsSet())
        {
            JsonRootObject->SetNumberField("volatility", VolatilityValue.GetValue());
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

    FString FRatingModelMaster::TypeName = "RatingModelMaster";
}