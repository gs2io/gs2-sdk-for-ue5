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

#include "Matchmaking/Model/RatingModel.h"

namespace Gs2::Matchmaking::Model
{
    FRatingModel::FRatingModel():
        RatingModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        VolatilityValue(TOptional<int32>())
    {
    }

    FRatingModel::FRatingModel(
        const FRatingModel& From
    ):
        RatingModelIdValue(From.RatingModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        VolatilityValue(From.VolatilityValue)
    {
    }

    TSharedPtr<FRatingModel> FRatingModel::WithRatingModelId(
        const TOptional<FString> RatingModelId
    )
    {
        this->RatingModelIdValue = RatingModelId;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModel> FRatingModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModel> FRatingModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FRatingModel> FRatingModel::WithVolatility(
        const TOptional<int32> Volatility
    )
    {
        this->VolatilityValue = Volatility;
        return SharedThis(this);
    }
    TOptional<FString> FRatingModel::GetRatingModelId() const
    {
        return RatingModelIdValue;
    }
    TOptional<FString> FRatingModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FRatingModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FRatingModel::GetVolatility() const
    {
        return VolatilityValue;
    }

    FString FRatingModel::GetVolatilityString() const
    {
        if (!VolatilityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), VolatilityValue.GetValue());
    }

    TOptional<FString> FRatingModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRatingModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRatingModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRatingModel::GetRatingNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):matchmaking:(?<namespaceName>.+):model:(?<ratingName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRatingModel> FRatingModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRatingModel>()
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
            ->WithVolatility(Data->HasField("volatility") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("volatility", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FRatingModel::ToJson() const
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
        if (VolatilityValue.IsSet())
        {
            JsonRootObject->SetNumberField("volatility", VolatilityValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FRatingModel::TypeName = "RatingModel";
}